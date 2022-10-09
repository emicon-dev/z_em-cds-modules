/*
 * Модуль реализует кольцевой буфер записи лога.
 *
 * ВНИМАНИЕ!
 * Модуль строго зависим от модуля CmpEmiconMemManager. CmpEmiconMemManager
 * должен подключатся в конфигурации рантайма строго с большим порядковым
 * номером.
 *
 * Память для ведения записи модуль выделяет из области nvram. 
 * Физическая память nvram отображается в виртуальное пространство размером
 * кратным размеру страницы. При этом используется только тот размер, который
 * указан в конфигурационном файле. Поэтому рекомендуется указывать размер
 * памяти кратным странице памяти (4Кб). 
 * Пример параметров конфигурационного файла:
 *
 *	[CmpEmiconLog]
 *	BufferSize=4096
 *
 * Первые 14 байт выделенной памяти используется для хранения технических
 * данных состояния буфера. Остальной размер отводится под записи лога.
 *
 * Принцип работы:
 * Модуль разработан для записи трех видов сообщений разной длины. Сообщения
 * могут быть записаны в любой последовательности в любом количестве.
 * При достижении конца буфера, сообщения записываются с начала буфера, затирая
 * наиболее старые записи. Данные записываются последовательно и без пропуска
 * байт в конце буфера. Другими словами, сообщение, которое полностью не влезает
 * в конец буфера, записывается до конца буфера и переноситься на начало буфера.
 * 
 */

#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconLogDep.h"

#include "stdint.h"
#include "errno.h"
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "emiconlog.h"
#include "emiconLogParser.c"

/*
 * Указатели на параметры буфера (данные инициализации). Эти данные лежат в
 * голове буфера.
 */
typedef struct struct_log_init {
	uint16_t * init_mark;                       // Признак инициализированного буфера
	uint32_t * offset_first_record;				// Смещение в байтах от головы первой записи, нужно для вычисления указателей
	uint32_t * offset_end_of_records;			// Смещение в байтах от головы последней записи
	uint32_t * log_mem_size;                    // Общий размер буфера лога
} struct_log_init;
struct_log_init log_init_info;

typedef struct struct_buff_pointers {
	// Указатели на начало и коенец буфера лог. Исключает данные инициализации.
	uint8_t* log_area;
	uint8_t* log_area_end;

	// Указатели первого и последнего байтов записи при старте рассчитываются смещением
	// от головы на log_init_info.offset_first_record, и log_init_info.offset_end_of_records соответвенно
 
	uint8_t* first_record;		// начало первой записи
	uint8_t* end_records;		// последний байт последней записи

} struct_buff_pointers;
struct_buff_pointers buff_pointers;

typedef struct struct_log_nvram_mem {
	size_t sz;					// Размер буфера считывается из конфигурации. 
	int fd;						// Дескрипшин файла мапирования памяти
	uint32_t log_mem_address;	// адрес системы лога - рассчитывается автоматически
	size_t allocated_mem_size;	//Действительный размер выделенной памяти под весь Лог включая инициализацию.
	void* map;					// Указатель на мапированный блок памяти Лога
} struct_log_nvram_mem;
struct_log_nvram_mem log_nvram_mem;

static RTS_HANDLE _s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventStopDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventPrepareStart = RTS_INVALID_HANDLE;

static json_t const *rules_list = 0;
static json_t const *ranges_rules_list = 0;

#define SEVERITY_ID(val) (val & 0b11100000) >> 5
#define EVENT_ID(val) val & 0b00011111

/*
 * Создает запись в логе собственного системного события.
 */
void create_own_sys_event(uint32_t evt);

int init_logger(void);
int set_init_offsets(void);
size_t size_of_free_space(void);
int write_buffer(uint8_t *p_data, size_t size);
int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size);
int release_space(size_t size);
int in_array(uint8_t *array, size_t size, uint8_t look_for);
void get_actual_time(date_and_time *data);
void actual_time_to_CP56Time(uint8_t *data);

uint16_t reverse_uint16 (uint16_t s);

int read_sys_log(uint8_t *frame, char *str, own_event_frame *evt_frame);
int read_sys_log_parsed(uint8_t *frame, char *str);
int read_ts_log(uint8_t *frame, char *str);
int read_ti_log(uint8_t *frame, char *str);

uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset);
int get_type_of_frame(uint8_t *frame);
int buffer_to_file(void);
bool is_buffer_accessable(void);
int read_cfg_param(uint32_t* sz_log_mem, uint32_t* sz_nvram, char* nvram_mem_file_name);
int get_log_nvram_mem(struct_log_nvram_mem* data, uint32_t sz_M, uint32_t sz_log_mem, uint32_t sys_var_area_size, char* nvram_mem_file_name);

// функция для регистрации обработчиков событий
void register_events_handler(void);

static void handler_evt_download_done(EventParam *pEventParam);
static void handler_evt_stop_done(EventParam *pEventParam);
static void handler_evt_prepare_start(EventParam *pEventParam);

void CDECL CDECL_EXT get_next_log_item(get_next_log_item_struct *p)
{

	int type_of_frame;
	size_t offset = 0;
	
	static uint8_t* frame_to_read = NULL;
	uint8_t* frame_end;

	if (!log_init_done){
		sprintf(p->log_str, "Error: The buffer is not initialized!\n");
		p->get_next_log_item = 0;
		return;
	}

	if (buff_pointers.first_record == buff_pointers.end_records) {
		sprintf(p->log_str, "EOF");
		p->get_next_log_item = 0;
		return;
	}

	if (p->get_first || !frame_to_read)
		frame_to_read = buff_pointers.first_record;

	type_of_frame = get_type_of_frame(frame_to_read);

	if (type_of_frame < 0){
		p->get_next_log_item = type_of_frame;
		return;
	}

	switch (type_of_frame) {
	case FRAME_TYPE_OWN_EVENT:
		read_sys_log(frame_to_read, p->log_str, NULL);
		offset = SIZE_OF_OWN_EVENT;		
	break;

	case FRAME_TYPE_TS:
		if (0 == read_ts_log(frame_to_read, p->log_str))
			offset = SIZE_OF_TS;
	break;

	case FRAME_TYPE_TI:
		if (0 == read_ti_log(frame_to_read, p->log_str))
			offset = SIZE_OF_TI;
	break;
	}

	frame_end = shift_pointer_along_buffer(frame_to_read, offset - 1);


	if (frame_end == buff_pointers.end_records){
		p->get_next_log_item = 0;	// записей больше нет.
	} else {
		frame_to_read = shift_pointer_along_buffer(frame_to_read, offset);
		p->get_next_log_item = 1;	// означает - есть еще записи.
	}

	return;
}


USE_STMT

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI		IN	Pointer to component mangager function to get a api function
 *		pfCallHook		IN	Pointer to component mangager function to call a hook function
 * </param> 
 * <result>ERR_OK if component could be initialized, else error code.</result>
 */
DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;
	pInitStruct->pfCreateInstance = NULL;
	pInitStruct->pfDeleteInstance = NULL;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;
	return ERR_OK;
}

/**
 * <description>Publish exported functions to the component manager, to make them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Import function pointers from other components. Use generated macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/**
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}

#endif

/**
 * <description>Hook function to get all broadcast hooks of the component manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)
{

	switch (ulHook){
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();
		register_events_handler();

		log_nvram_mem.allocated_mem_size = 0;
		log_nvram_mem.map = NULL;

		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;

	case CH_EXIT3: 
		if (CHK_EventUnregisterCallbackFunction)
			CAL_EventUnregisterCallbackFunction(_s_hEventAppDownloadDone, handler_evt_download_done);
		if (CHK_EventClose)
			CAL_EventClose(_s_hEventAppDownloadDone);

		if (log_nvram_mem.map)
			munmap(log_nvram_mem.map, log_nvram_mem.allocated_mem_size);
		break;
	
	default:
		break;
	}
	return ERR_OK;
}

static void handler_evt_download_done(EventParam *pEventParam)
{

	/* Use pEventParam->CmpIdProvider to identify the component that posts 
	the event. Note that pEventParam->EventId is not unique in the system */
	switch (pEventParam->CmpIdProvider){
	case CMPID_CmpApp:
		init_logger();
		break;

	default:
		break;
	}
}

static void handler_evt_stop_done(EventParam *pEventParam)
{

	if (pEventParam->CmpIdProvider != CMPID_CmpApp)
		return;

	create_own_sys_event(OWN_EVENT_ID_STOP);

}

static void handler_evt_prepare_start(EventParam *pEventParam)
{

	if (pEventParam->CmpIdProvider != CMPID_CmpApp)
		return;

	create_own_sys_event(OWN_EVENT_ID_START);
}

void create_own_sys_event(uint32_t evt)
{

	write_sys_log_struct param = {
		.bySeverity = SEVERITY_INFO,
		.byClassId = 0,
		.byEvent = evt,
		.dwArgs = evt
	};
	write_sys_log(&param);
}

int read_cfg_param(uint32_t* sz_log_mem, uint32_t* sz_nvram, char* nvram_mem_file_name)
{

	RTS_RESULT res;
	RTS_I32 iValue = 0;
	char str[200];

	// Считываем размер буфера лога
	CAL_SettgGetIntValue(COMPONENT_NAME, "BufferSize", &iValue, 0, CMPSETTINGS_CACHED);
	
	if (iValue == 0) {
		sprintf(str, "Error: No buffer size found in runtime configuration file!");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, str);

		return ERR_FAILED;
	}
	*sz_log_mem = iValue;
	iValue = 0;

	// Считываем размер всей NVRAM
	CAL_SettgGetIntValue("CmpEmiconMemManager", "NVRAMSize", &iValue, 0, CMPSETTINGS_CACHED);

	if (iValue == 0) {
		sprintf(str, "Error: No size of NVRAM found in runtime configuration file!");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, str);

		return ERR_FAILED;
	}
	*sz_nvram = iValue;

	// Считываем имя файла, куда будет эмулироваться nvram в режиме эмуляции
	int max_size_file_name = MAX_SZ_FILE_NAME;
	if (_is_emu) {
		res = CAL_SettgGetStringValue("Emulation", "nvram_mem_file_name", nvram_mem_file_name, &max_size_file_name, "", 0);

		if (res != ERR_OK || strlen(nvram_mem_file_name) == 0) {
			sprintf(str, "Error: Emulation mode is detected but no file name for memory emulation is set in runtime cfg!");
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, str);

			return ERR_FAILED;
		}
	}

	return ERR_OK;
}

int get_log_nvram_mem(struct_log_nvram_mem* data, uint32_t sz_M, uint32_t sz_log_mem, uint32_t sys_var_area_size, char* nvram_mem_file_name)
{

	uint32_t page_mask, page_size;

	page_size = sysconf(_SC_PAGESIZE);
	page_mask = ~(page_size - 1);

	data->allocated_mem_size = (((sz_log_mem / page_size)) * page_size);

	if (_is_emu) {
		data->log_mem_address = sz_M + sys_var_area_size;
		data->fd = open(nvram_mem_file_name, O_RDWR | O_CREAT,
			S_IRUSR | S_IRGRP | S_IROTH | O_SYNC);
		data->map = mmap(0, data->allocated_mem_size,
			PROT_READ | PROT_WRITE, MAP_SHARED,
			data->fd, data->log_mem_address & page_mask);
	}
	else {
		data->fd = open("/dev/mem", O_RDWR | O_SYNC);
		data->log_mem_address = NVRAM_CS3_MEM_ADDRESS + sz_M + sys_var_area_size;
		data->map = mmap(NULL, data->allocated_mem_size,
			PROT_READ | PROT_WRITE, MAP_SHARED, data->fd,
			(data->log_mem_address & page_mask));
	}

	if (data->map == MAP_FAILED) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "Error: Memory mapping filed!");
		return ERR_FAILED;
	}
	data->sz = sz_log_mem - 14;

	return ERR_OK;
}

int init_logger(void)
{

	int fd;
	int nbytes;
	uint32_t sz_M;
	uint32_t sz_NVRAM = 0;
	uint32_t sz_log_mem = 0;	
	char nvram_mem_file_name[MAX_SZ_FILE_NAME + 1];

	if (read_cfg_param(&sz_log_mem, &sz_NVRAM, nvram_mem_file_name) == ERR_FAILED)
		return ERR_FAILED;

	// Считываем у EmiconMemManager размер %M. Она уже выровнена по 4к.
	sz_M = CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size();

	// Чтение размера области системных переменных
	mem_buffer sys_var_area;
	CAL_get_sys_var_area(&sys_var_area);

	if (sz_M + sz_log_mem + sys_var_area.size  > sz_NVRAM) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0, "Error: Not enough size of NVRAM!");
		return ERR_FAILED;
	}

	if (get_log_nvram_mem(&log_nvram_mem, sz_M, sz_log_mem, sys_var_area.size, nvram_mem_file_name) != ERR_OK)
		return ERR_FAILED;

	// Расчет указателей головной структуры лога.
	// TODO:  Тут на до бы избавиться от цифр в коде.
	log_init_info.init_mark = (uint16_t*)log_nvram_mem.map;									// маркер инициализации лежит первым
	log_init_info.offset_first_record = (uint32_t *)((uint8_t *)log_nvram_mem.map + 2);		// значения адреса первой записи лежит сразу за маркером,
																							// тоесть смещением от головы на размер маркера ==2
	log_init_info.offset_end_of_records = (uint32_t *)((uint8_t *)log_nvram_mem.map + 6);	// значение адреса последней записи лежит сразу за адресом первой
	log_init_info.log_mem_size = (uint32_t *)((uint8_t *)log_nvram_mem.map + 10);			// размер памяти под лог

	// указатель на начало области записи расчитываем смещением на размер 
	// структуры инициализации от головы всей области, выделенной на Лог.
	buff_pointers.log_area = (uint8_t *)log_init_info.init_mark + 2+4+4+4;

	// указатель конца на последний байт буфера, а не байт за ним!
	buff_pointers.log_area_end = (uint8_t *)log_init_info.init_mark + sz_log_mem - 1;

	if (*log_init_info.init_mark != LOG_INIT_MARK || *log_init_info.log_mem_size != sz_log_mem) {
		memset((uint8_t *)log_init_info.init_mark, NONE, sz_log_mem);
		buff_pointers.first_record = buff_pointers.end_records = buff_pointers.log_area;
		set_init_offsets();
		*log_init_info.log_mem_size = sz_log_mem;
		*log_init_info.init_mark = LOG_INIT_MARK;

		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Init %d bytes for log at 0x%X, mark 0x%X",
			log_nvram_mem.allocated_mem_size, log_init_info.init_mark, *log_init_info.init_mark);
	} else {
		buff_pointers.first_record = buff_pointers.log_area + *log_init_info.offset_first_record;
		buff_pointers.end_records = buff_pointers.log_area + *log_init_info.offset_end_of_records;
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Log buffer found");
	}
		
	log_init_done = true;
	return ERR_OK;
}

int set_init_offsets(void)
{

	*log_init_info.offset_first_record = buff_pointers.first_record - buff_pointers.log_area;
	*log_init_info.offset_end_of_records = buff_pointers.end_records - buff_pointers.log_area;
	return ERR_OK;
}

/*
 * Очищает буфер логера, и записывает сообщение об очитске первым сообщением.
 * Физически буфер не стирается. Переносятся указатели на начало.
 */
void CDECL CDECL_EXT clr_sys_log(clr_sys_log_struct *p)
{

	if (!log_init_done){
		p->clr_sys_log = 1;
		return;
	}
	
	buff_pointers.first_record = buff_pointers.end_records = buff_pointers.log_area;

	set_init_offsets();

	*buff_pointers.first_record = NONE;

	create_own_sys_event(OWN_EVENT_ID_CLR);
	
	p->clr_sys_log = ERR_OK;
}

void CDECL CDECL_EXT create_log_files(create_log_files_struct *p)
{

	 if (!log_init_done){
 		p->create_log_files = -1;
 		return;
 	}

	uint8_t *my_p_first_record;
	uint8_t *my_p_end_of_frame;
	int type_of_frame;
	int i;
	size_t offset;
	bool end_of_records;

	char date_str[100];
	char file_name_str[100];
	char log_str[1000];

	int fd;
	int max_num_records;

	date_and_time dt_file_creation;
	get_actual_time(&dt_file_creation);

	sprintf(date_str, "%d-%02d-%02d_%02d-%02d-%02d-%03d",
		dt_file_creation.year,
		dt_file_creation.month,
		dt_file_creation.day,
		dt_file_creation.hour,
		dt_file_creation.minutes,
		dt_file_creation.seconds,
		dt_file_creation.msec);

	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
	
	my_p_first_record = buff_pointers.first_record;
	
	end_of_records = false;
	i = 0;
	max_num_records = *log_init_info.log_mem_size / SIZE_OF_OWN_EVENT;

	parse_rules_read();

	do {
		type_of_frame = get_type_of_frame(my_p_first_record);

		// передаем ошибку определения типа вызывающему
		if (type_of_frame < 0){
			p->create_log_files = -2;
			return;
		}

		if (i > max_num_records){
			// считанных записей привышает лимит буфера
			// означает нарушение структуры буфера. Может быть если все байты
			// инициализировать с первым битом == 1
			p->create_log_files = -3;
			return;
		}

		i++;
		
		switch (type_of_frame) {
		case FRAME_TYPE_OWN_EVENT:
			if (EXIT_SUCCESS == read_sys_log_parsed(my_p_first_record, log_str)){
				sprintf(file_name_str, "%sEVT/e_%s.txt",
					_log_folder, date_str);
			
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);
				write(fd, log_str, strlen(log_str));
				close(fd);
			}
			
			offset = SIZE_OF_OWN_EVENT;
			break;
		

		case FRAME_TYPE_TS:
			if (EXIT_SUCCESS == read_ts_log(my_p_first_record,
							log_str)){
				sprintf(file_name_str,
					"%sTD/t%d_%s.txt", _log_folder,
					*my_p_first_record, date_str);
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);

				write(fd, log_str, strlen(log_str));
				close(fd);
			}

			offset = SIZE_OF_TS;
			break;

		case FRAME_TYPE_TI:
			if (EXIT_SUCCESS == read_ti_log(my_p_first_record,
							log_str)) {
				sprintf(file_name_str,
					"%sTA/t%d_%s.txt", _log_folder,
					*my_p_first_record & MASK_ALL_MARK,
					date_str);
				fd = open(file_name_str, O_CREAT | O_WRONLY
					| O_APPEND, mode);

				write(fd, log_str, strlen(log_str));
				close(fd);
			}

			offset = SIZE_OF_TI;
			break;
		}

		my_p_end_of_frame = shift_pointer_along_buffer(
			my_p_first_record, offset - 1);
		
		if (my_p_end_of_frame == buff_pointers.end_records)
			end_of_records = true;
		else
			my_p_first_record = shift_pointer_along_buffer(
				my_p_first_record, offset);
			
	} while (!end_of_records);


	p->create_log_files = i;
}

/*
 * Записывает собственное сообщение, переданное в параметре.
 * Функция вормирует own_event_frame кадр записи, где 
 * первый 1 байт определяет подкласс собственного события. Старший бит этого
 * этого байта всегда устанавливается в 1 - признак собственного сообщения.
 * Последующие 4 байта содержат код сообщения (поле value).
 * Последние 7 байт - текущее время в формате CP56Time2a.
 */
void CDECL CDECL_EXT write_sys_log(write_sys_log_struct *p)
{

	int res;
	own_event_frame frame;

	// принудительно устанавливаем старший бит в 1
	uint8_t class_id = p->byClassId | MARK_SYS_LOG;
	frame.class_id = class_id;
	frame.args = p->dwArgs;

	frame.severity_event = p->bySeverity << 5; // severity имеет знаение в 3х битах. Сдвигаем их в начало байта.
	frame.severity_event = frame.severity_event | p->byEvent; // добавляем в байт значащие биты event.

	actual_time_to_CP56Time(frame.datetime);
	res = write_buffer((uint8_t *)&frame, SIZE_OF_OWN_EVENT);
	if (res < 0)
		p->write_sys_log = res;
	p->write_sys_log = ERR_OK;
	
}

void CDECL CDECL_EXT write_ti_log(write_ti_log_struct *p)
{

	uint8_t data[SIZE_OF_TI];
	int res;
	uint8_t class_id;

	class_id = p->byClassId;

	class_id &= ~MARK_SYS_LOG;
	class_id |= MARK_TI_LOG; 

	data[0] = class_id;
	memcpy(&data[1], p->pbyData, SIZE_OF_TI - 1);	

	res = write_buffer((uint8_t *)data, SIZE_OF_TI);
	if (res < 0)
		p->write_ti_log = res;

	p->write_ti_log = ERR_OK;
	
}

void CDECL CDECL_EXT write_ts_log(write_ts_log_struct *p)
{

	uint8_t data[SIZE_OF_TS];
	int res;
	uint8_t class_id;

	class_id = p->byClassId;

	class_id &= ~MARK_SYS_LOG;
	class_id &= ~MARK_TI_LOG;
	
	data[0] = p->byClassId;
	memcpy(&data[1], p->pbyData, SIZE_OF_TS - 1);	
	res = write_buffer((uint8_t *)data, SIZE_OF_TS);
	if (res < 0)
		p->write_ts_log = res;

	p->write_ts_log = ERR_OK;
	
}

size_t size_of_free_space(void)
{
	/* 
	 * Ситуация когда указатель начала и конца совпадают может быть в одном
	 * случае:
	 * 	1) Буфер полностью чист, в этом случае значение по указателям 
		будет равным NONE.
	 */
	if (buff_pointers.first_record == buff_pointers.end_records)
		return log_nvram_mem.sz;

	/* 
	 * Если указатель начала меньше конца, то размер свободного пространства
	 * определяем вычитаением отрезка от начала до конца из общего размера
	 * буфера. 
	 *
	 * Иначе - указатель конца прошел по кругу и идет за указателем начала.
	 * В этом случае свободное пространство находится между указателями.
	 */

	if (buff_pointers.first_record < buff_pointers.end_records)
		return log_nvram_mem.sz - (buff_pointers.end_records + 1 - buff_pointers.first_record);
	else
		return buff_pointers.first_record - buff_pointers.end_records - 1;

}

/* 
 * Проверка семафора. 
 * Если буфер не занят, *log_init_info.init_mark должен быть LOG_INIT_MARK
 */
bool is_buffer_accessable(void)
{
	int trial = 0;
	
	while(*log_init_info.init_mark != LOG_INIT_MARK && trial < 3){
		trial++;
		usleep (100);
	}
	if (trial >= 3)
		return false;
	
	return true; 
}

int write_buffer(uint8_t *p_data, size_t size)
{

	size_t sz_free_space;
	size_t sz_free_end;
	char str[200];
	
	if (!log_init_done)
		return ERR_FAILED;

	if (!is_buffer_accessable()){
		sprintf(str, "Test init_mark:  0x%X", *log_init_info.init_mark);
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_ERROR, ERR_FAILED, 0,
			   str);
		return ERR_FAILED;
	}


	*log_init_info.init_mark = LOG_INIT_MARK_BUSY;

	if (size > log_nvram_mem.sz)
		return -ENOMEM;

	sz_free_space = size_of_free_space();

	if (sz_free_space < size)
		release_space(size - sz_free_space);

	if (buff_pointers.end_records + size <= buff_pointers.log_area_end) {
		if (buff_pointers.first_record == buff_pointers.end_records){
			memcpy(buff_pointers.end_records, p_data, size);
			buff_pointers.end_records += size - 1;
			set_init_offsets();
		}
		else {
			memcpy(buff_pointers.end_records + 1, p_data, size);
			buff_pointers.end_records += size;
			set_init_offsets();
		}

	} else {
		sz_free_end = buff_pointers.log_area_end - buff_pointers.end_records;
		if (sz_free_end == 0) {
			// указатель конца последней записи в последнем байте
			// буфера - начинаем запись с головы буфера
			memcpy(buff_pointers.log_area, p_data, size);
			buff_pointers.end_records = buff_pointers.log_area + size - 1;
			set_init_offsets();
		} else {
			// разбиваем запись на две части. Дозаполняем хвост
			// и продолжаем от головы
			memcpy(buff_pointers.end_records + 1, p_data, sz_free_end);
			memcpy(buff_pointers.log_area, p_data + sz_free_end, size -
				sz_free_end);
			buff_pointers.end_records = buff_pointers.log_area + size - sz_free_end - 1;
			set_init_offsets();
		}

	}

	*log_init_info.init_mark = LOG_INIT_MARK;



	return ERR_OK;
}

int read_buffer(uint8_t *p_data, uint8_t *p_first_byte, size_t size)
{
	size_t bytes;

	if (!log_init_done)
		return ERR_FAILED;

	if (!is_buffer_accessable())
		return ERR_FAILED;
	*log_init_info.init_mark = LOG_INIT_MARK_BUSY;

	if (size > log_nvram_mem.sz)
		size = log_nvram_mem.sz;

	if (p_first_byte + size <= buff_pointers.log_area_end) {
		memcpy(p_data, p_first_byte, size);
	} else {
		// считываем хвост и продолжаем от головы
		bytes = buff_pointers.log_area_end - p_first_byte + 1;
		memcpy(p_data, p_first_byte, bytes);
		memcpy(p_data + bytes, buff_pointers.log_area, size - bytes);
	}
	
	*log_init_info.init_mark = LOG_INIT_MARK;
	return ERR_OK;
}

/*
 * Освобождает место в буфере для size байт. 
 * Освобождение происходит путем переноса указателя первой записи на длину
 * фрейма. Указатель первой записи всегда указывает на первый байт фрейма, где
 * указан класс (тип) фрейма. Длина фрейма расчитывается исходя из типа фрейма:
 *	Фрейм собственного сигнала всегда имеет старший бит == 1,
 *	TI  имеет значения определенные в CLASS_OF_TI.
 * Таким образом, все значение со старшим битом == 0 и не входящие в CLASS_OF_TI
 * относим к TS типу.
 */
int release_space(size_t size)
{

	size_t offset;
	int32_t rest_size;

	rest_size = size;
	do {
		if (*buff_pointers.first_record & MARK_SYS_LOG)
			offset = SIZE_OF_OWN_EVENT;
		else
			if (*buff_pointers.first_record & MARK_TI_LOG)
				offset = SIZE_OF_TI;
			else 
				offset = SIZE_OF_TS;

		buff_pointers.first_record = shift_pointer_along_buffer(buff_pointers.first_record,
							     offset);
		set_init_offsets();

		rest_size -= offset; 
	} while (rest_size > 0);

	return 0;
}

int in_array(uint8_t *array, size_t size, uint8_t look_for)
{
	int i;

	for (i = 0; i < size; i++)
		if (array[i] == look_for)
		return 1;
	return 0;
}

/*
 * Считывает текущее время с точностью до милисекунд
 */
void get_actual_time(date_and_time *dt)
{
	struct timeval tv;
	struct tm *tm;

	gettimeofday(&tv, NULL);
	tm = localtime(&tv.tv_sec);

	// Add 1900 to get the right year value
	// read the manual page for localtime()
	dt->year = tm->tm_year + 1900;
	// Months are 0 based in struct tm
	dt->month = tm->tm_mon + 1;
	dt->day_of_week = tm->tm_wday;
	dt->day = tm->tm_mday;
	dt->hour = tm->tm_hour;
	dt->minutes = tm->tm_min;
	dt->seconds = tm->tm_sec;
	dt->msec = (int) (tv.tv_usec / 1000);
}

/*
 * Считывает текущее время с точностью до милисекунд и укладывает в формате
 * CP56Time2a по указателю, переданному в праметре.
 */
void actual_time_to_CP56Time(uint8_t *data)
{
	date_and_time dt;
	get_actual_time(&dt);
	time_to_CP56Time2a(&dt, data);
}


uint16_t reverse_uint16 (uint16_t s)
{
	uint8_t c1, c2;

	if (is_bigendian()) {
		return s;
	} else {
		c1 = s & 255;
		c2 = (s >> 8) & 255;

		return (c1 << 8) + c2;
	}
}

/*
 * Считывает кадр собтвеных сообщений из памяти
 */
int read_sys_log(uint8_t *frame, char *str, own_event_frame *evt_frame)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_OWN_EVENT)
		return ERR_FAILED;

	own_event_frame my_frame;

	read_buffer((uint8_t*)&my_frame, frame, SIZE_OF_OWN_EVENT);

	my_frame.class_id &=  ~MARK_SYS_LOG;

	if (evt_frame != NULL)
		memcpy(evt_frame, &my_frame, sizeof(own_event_frame));
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%03d\t Severity=%d\t Class=%03d\t Event=%02d\t Args=0x%08X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		(my_frame.severity_event & 0b11100000) >> 5,
		my_frame.class_id,
		my_frame.severity_event & 0b00011111,
		my_frame.args
	);

	return ERR_OK;
}

int read_sys_log_parsed(uint8_t *frame, char *str)
{

	char str_parse[1000];
	int res;
	own_event_frame my_frame;
	struct_log_record log_record;
	
	read_sys_log(frame, str, &my_frame);
	log_record.class_id = my_frame.class_id;
	log_record.args.val = my_frame.args;
	log_record.event_id = EVENT_ID(my_frame.severity_event);
	log_record.severity = SEVERITY_ID(my_frame.severity_event);

	str_parse[0] = '\0';
	parse_log(&log_record, str_parse);

	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%03d\t%s\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		str_parse
	);



	return EXIT_SUCCESS;
}

/*
 * Считывает кадр ts сообщений из памяти
 */
int read_ts_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TS)
		return ERR_FAILED;

	ts_frame my_frame;
	read_buffer((uint8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	// убираем разметочные два старших бита
	my_frame.class_id &= MASK_ALL_MARK;

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%03d  Type: 0x%02X  Address: 0x%02X%02X%02X  Value: 0x%02X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,
		my_frame.class_id,
		my_frame.address[2],
		my_frame.address[1],
		my_frame.address[0],
		my_frame.value
		
	);

	return ERR_OK;
}

/*
 * Считывает кадр ti сообщений из памяти
 */
int read_ti_log(uint8_t *frame, char *str)
{
	int type_of_frame;

	type_of_frame = get_type_of_frame(frame);
	if (type_of_frame != FRAME_TYPE_TI)
		return ERR_FAILED;

	ti_frame my_frame;
	read_buffer((uint8_t*)&my_frame, frame, sizeof(my_frame));
	
	date_and_time dt;
	CP56Time2a_to_time(my_frame.datetime, &dt);

	// убираем разметочные два старших бита
	my_frame.class_id &= MASK_ALL_MARK;

	sprintf(str, "%d-%02d-%02d %02d:%02d:%02d.%03d  Type: 0x%02X  Address: 0x%02X%02X%02X  Value: 0x%02X%02X%02X%02X  Quality: 0x%02X\n", 
		dt.year,
		dt.month,
		dt.day,
		dt.hour,
		dt.minutes,
		dt.seconds,
		dt.msec,

		// по ТЗ требуется при выводе подменять значение 0 на 64.
		my_frame.class_id ? my_frame.class_id : 64,

		my_frame.address[2],
		my_frame.address[1],
		my_frame.address[0],

		my_frame.value[3],
		my_frame.value[2],
		my_frame.value[1],
		my_frame.value[0],
		
		my_frame.quality
	);

	return ERR_OK;
}

/*
 * возвращает указатель смещенный от p_begin на offset байт по буферу с учетом 
 * цикличности.
 */

uint8_t* shift_pointer_along_buffer(uint8_t *p_begin, size_t offset)
{
	uint8_t *my_p;
	
	my_p = p_begin + offset;
	if (my_p > buff_pointers.log_area_end)
		my_p = buff_pointers.log_area + (my_p - buff_pointers.log_area_end - 1);

	return my_p;
}

/*
 * Возвращает тип фрейма по первому байту
 */
int get_type_of_frame(uint8_t *frame)
{

	if (*frame & MARK_SYS_LOG)
			return FRAME_TYPE_OWN_EVENT;
	
	if (*frame & MARK_TI_LOG)
		return FRAME_TYPE_TI;
	else
		return FRAME_TYPE_TS;

	return -1; // тип не найден
}

/*
 * Регистрация обработчиков событий
 */
void register_events_handler(void)
{
	if (CHK_EventOpen) {
		_s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp, NULL);
		_s_hEventStopDone = CAL_EventOpen(EVT_StopDone, CMPID_CmpApp, NULL);
		_s_hEventPrepareStart = CAL_EventOpen(EVT_PrepareStart, CMPID_CmpApp, NULL);
	}

	if (CHK_EventRegisterCallbackFunction) {
		CAL_EventRegisterCallbackFunction(_s_hEventAppDownloadDone, handler_evt_download_done, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventStopDone, handler_evt_stop_done, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventPrepareStart, handler_evt_prepare_start, 0);
	}
}
