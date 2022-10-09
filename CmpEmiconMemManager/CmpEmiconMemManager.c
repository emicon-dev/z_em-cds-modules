/*
 * Функционал работы с %M памятью в NVRAM.
 * Определение буфера между %M и Log. 
 * 
 * Распределение NVRAM:
 * |0 ... %M ... размер из devdesc|... sys_var_area ... из cfg|... Log ... до конца|
 */

#ifndef STATICITF_DEF
	#define STATICITF_DEF	static
#endif


#include <stdbool.h>
#include "CmpStd.h"
#include "CmpItf.h"
#include "CmpEmiconMemManagerDep.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include "CmpIoMgrItf.h"

/*
 * nvram_mem_file_name - файл в который будет работать вместо NVRAM в режиме
 * эмуляции.
 * При определении %M памяти возвращается указатель либо на физическую NVRAM
 * либо в случае эмуляции указатель на память маппированную в файл.
 */

#define MAX_SZ_FILE_NAME	200
static char nvram_mem_file_name[MAX_SZ_FILE_NAME + 1];
static bool _is_emu = false;

/*
 * Различные флаги располагаются с адреса FIRST_BYTE_OF_SETS блоком размером
 * SIZE_OF_SETS. Этот блок надо отдельно обрабатывать при восстановлении 
 * памяти. 
 */

/* NWRAM Memmory params */
const uint32_t CS3_MEM_ADDRESS = 0x2000000;
static uint32_t _cs3_Mmem_size = 0;
static void *_p_NWRAM_mem = NULL;

/* Buffer to store NWRAM before initial zerroing */
static void *_p_mem_buff = NULL;

static mem_buffer sys_var_area = {
	.p = NULL,
	.size = 0
};

static int _fd_cs3;

/* Handle to the event defined by CmpApp */
static RTS_HANDLE _s_hEventAllocArea = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventPrepareReset = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventResetDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventAppPrepareDownload = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventAppDownloadDone = RTS_INVALID_HANDLE;
static RTS_HANDLE _s_hEventConfigStopDone = RTS_INVALID_HANDLE;

static void callback_gateway(EventParam *pEventParam);
static void handler_evt_done_update_configuration(EventParam *pEventParam);
void CmpApp_callback_handler(EventParam *pEventParam);
void em_memory_manager(EVTPARAM_CmpAppArea *pParam);
void em_save_mem(void);
void em_restore_mem(void);

/*
 * Возвращает указатель на NVRAM память размером size.
 */
void *get_nvram_mem(uint32_t size, uint32_t page_mask);

/*
 * Возвращает указатель на память куда отображенен файл имитации NVRAM памяти
 * размером size.
 */
void *get_file_nvram_mem(uint32_t size);
void init_mem_buff(mem_buffer *buff, uint32_t physical_addr, uint32_t size);

USE_STMT


DLL_DECL int CDECL ComponentEntry(INIT_STRUCT *pInitStruct)
{
	pInitStruct->CmpId = COMPONENT_ID;
	pInitStruct->pfExportFunctions = ExportFunctions;
	pInitStruct->pfImportFunctions = ImportFunctions;
	pInitStruct->pfGetVersion = CmpGetVersion;
	pInitStruct->pfHookFunction = HookFunction;

	s_pfCMRegisterAPI = pInitStruct->pfCMRegisterAPI;
	s_pfCMRegisterAPI2 = pInitStruct->pfCMRegisterAPI2;
	s_pfCMGetAPI = pInitStruct->pfCMGetAPI;
	s_pfCMGetAPI2 = pInitStruct->pfCMGetAPI2;
	s_pfCMCallHook = pInitStruct->pfCMCallHook;
	s_pfCMRegisterClass = pInitStruct->pfCMRegisterClass;
	s_pfCMCreateInstance = pInitStruct->pfCMCreateInstance;

	return ERR_OK;
}

/*
 * <description>Publish exported functions to the component manager, to make
 * them available for other components.
 * Use generated macro EXPORT_STMT.</description>
 * <result>ERR_OK or error code in case of error</result>
 */
static int CDECL ExportFunctions(void)
{
	EXPORT_STMT;
	return ERR_OK;
}

/*
 * <description>Import function pointers from other components. Use generated
 * macro IMPORT_STMT.</description>
 * <result>ERR_OK or error code if function name could not be resolved</result>
 */
static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

/*
 * <description>Return the version of our component.</description>
 * <result>Version as defined in dep file</result>
 */
static RTS_UI32 CDECL CmpGetVersion(void)
{
	/* Our component version defined in our Dep file */
	return CMP_VERSION;
}

/*
 * <description>Hook function to get all broadcast hooks of the component
 * manager. All init and exit stuff must be implemented here!</description>
 * <param name="ulHook" type="IN">Kind of hook. See CH_ definitions in CmpItf.h
 * for details.</param> 
 * <param name="ulParam1" type="IN">Hook specific first parameter. See
 * definitions in CmpItf.h for details.</param> 
 * <param name="ulParam2" type="IN">Hook specific second parameter. See
 * definitions in CmpItf.h for details.</param>  
 * <result>Error code</result>
 */

static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook) {
	case CH_INIT_SYSTEM:

		break;
	case CH_INIT:
		break;
	case CH_INIT2:	

		break;

	case CH_INIT3:

		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();


		_s_hEventAllocArea = CAL_EventOpen(EVT_AllocArea, CMPID_CmpApp,
						   NULL);

		_s_hEventPrepareReset = CAL_EventOpen(EVT_PrepareReset,
						      CMPID_CmpApp, NULL);
		_s_hEventResetDone = CAL_EventOpen(EVT_ResetDone,
						   CMPID_CmpApp, NULL);

		_s_hEventAppPrepareDownload = CAL_EventOpen(EVT_PrepareDownload,
							    CMPID_CmpApp, NULL);
		_s_hEventAppDownloadDone = CAL_EventOpen(EVT_DownloadDone,
							 CMPID_CmpApp, NULL);

		_s_hEventConfigStopDone = CAL_EventOpen(
			EVT_DoneUpdateConfiguration, CMPID_CmpIoMgr, NULL);


		CAL_EventRegisterCallbackFunction(_s_hEventAllocArea,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventPrepareReset,
						  callback_gateway, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventResetDone,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventAppPrepareDownload,
						  callback_gateway, 0);
		CAL_EventRegisterCallbackFunction(_s_hEventAppDownloadDone,
						  callback_gateway, 0);

		CAL_EventRegisterCallbackFunction(_s_hEventConfigStopDone,
				handler_evt_done_update_configuration, 0);

		break;

	case CH_INIT_TASKS:
		/*
		 * Called after CH_INIT_SYSTEM_TASKS. All components should
		 * start their tasks.
		 * NOTE: The IEC bootprojects are loaded here!
		 */
		break;

	case CH_INIT_COMM:
		/*
		 * Called after CH_INIT_TASKS. Communication can be started at
		 * this point, because all components are ready and running.
		 */
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		break;
	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		/*
		 * Called before CH_EXIT2 to store data (e.g. retain data).
		 * Unregister from events at shutdown
		 */

		CAL_EventUnregisterCallbackFunction(_s_hEventAllocArea,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventPrepareReset,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventResetDone,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventAppPrepareDownload,
						    callback_gateway);
		CAL_EventUnregisterCallbackFunction(_s_hEventAppDownloadDone,
						    callback_gateway);

		CAL_EventClose(_s_hEventAllocArea);
		CAL_EventClose(_s_hEventPrepareReset);
		CAL_EventClose(_s_hEventResetDone);
		CAL_EventClose(_s_hEventAppPrepareDownload);
		CAL_EventClose(_s_hEventAppDownloadDone);

		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;
	case CH_EXIT_SYSTEM:
		break;
	default:
		break;
	}
	return ERR_OK;
}

#ifndef CPLUSPLUS
	IMPLEMENT_ADDREF
	IMPLEMENT_RELEASE
#endif


 static void callback_gateway(EventParam *pEventParam){

	/* Use pEventParam->CmpIdProvider to identify the component that posts 
	the event. Note that pEventParam->EventId is not unique in the system */
	switch (pEventParam->CmpIdProvider){
	case CMPID_CmpApp:
		CmpApp_callback_handler(pEventParam);
		break;

	default:
		break;
	}
}

void CmpApp_callback_handler(EventParam *pEventParam){

	/* Use pEventParam->EventId to identify the event. */
	if (pEventParam->EventId == EVT_AllocArea &&
			pEventParam->usParamId == EVTPARAMID_CmpAppArea){
		//RTS_RESULT Result;
		EVTPARAM_CmpAppArea *pParam =
			(EVTPARAM_CmpAppArea *)pEventParam->pParameter;

		if (IsArea(pParam->usType, DA_MEMORY) != 0)
			em_memory_manager(pParam);
	}

	if (pEventParam->EventId == EVT_PrepareReset){
		EVTPARAM_CmpApp_Reset *pParam =
			(EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;


		/*
		 * Делаем обнудение по холодному рессету, потому что он не 
		 * перегружает МЭК проект и не приводит к проблеме потери
		 * указателя. По исправлению ошибки переведем на
		 * RTS_RESET_ORIGIN
		 */
		if (pParam->usResetOption == RTS_RESET_COLD && _p_NWRAM_mem)
			memset(_p_NWRAM_mem, 0, _cs3_Mmem_size);
			
		em_save_mem();
	}

	if (pEventParam->EventId == EVT_ResetDone){
		EVTPARAM_CmpApp_Reset *pParam =
			(EVTPARAM_CmpApp_Reset *)pEventParam->pParameter;

		// аналогично переписать на RTS_RESET_ORIGIN
		if (pParam->usResetOption != RTS_RESET_COLD)
			em_restore_mem();
	}

	if (pEventParam->EventId == EVT_PrepareDownload)
		em_save_mem();

	if (pEventParam->EventId == EVT_DownloadDone){
		char *pszName;
		
		EVTPARAM_CmpApp *pParam =
				(EVTPARAM_CmpApp *)pEventParam->pParameter;
		pszName = pParam->pApp->szName;

		em_restore_mem();
	}

}

void em_memory_manager(EVTPARAM_CmpAppArea *pParam){
	
	if (pParam->bAlloc == 1){
		/* Memmory allocation */

		RTS_RESULT res;
		uint32_t page_mask, page_size;
		RTS_I32 sz_sys_var_area;
		uint32_t pa_sys_var_area; // physical addr

		page_size = sysconf(_SC_PAGESIZE);
		page_mask = (page_size - 1);
		_cs3_Mmem_size = ((pParam->ulSize / page_size) * page_size);

		sz_sys_var_area = 0;
		res = CAL_SettgGetIntValue(COMPONENT_NAME, "SysVarAreaSize",
			     &sz_sys_var_area, 0, CMPSETTINGS_CACHED);
		if (res != ERR_OK)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO,
				ERR_FAILED, 0, "Error of reading SysVarAreaSize from cfg files!");

		if (_is_emu) {
			_p_NWRAM_mem = get_file_nvram_mem(_cs3_Mmem_size);
			pa_sys_var_area = _cs3_Mmem_size;
		} else {
			_p_NWRAM_mem = get_nvram_mem(_cs3_Mmem_size, page_mask);
			pa_sys_var_area = CS3_MEM_ADDRESS + _cs3_Mmem_size;
		}

		if (sz_sys_var_area > 0)
			init_mem_buff(&sys_var_area, pa_sys_var_area,
				      sz_sys_var_area);
	
		if(_p_NWRAM_mem == MAP_FAILED) {
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
				ERR_FAILED, 0, 
				"Error: Mapping of NWRAM for %M failed! %s",
				strerror(errno)
			);

			_p_NWRAM_mem = 0;
		} else {
			// settings RTS pointer of %M:
			pParam->pArea = (RTS_UI8*)_p_NWRAM_mem;
			em_save_mem();
		}
	} else {
		/* Memmory dealocation: */
		int res;

		res = munmap(pParam->pArea, _cs3_Mmem_size);
		if (res < 0)
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
				ERR_FAILED, 0, 
				"Error: munmap NWRAM failed. %s",
				strerror(errno)
			);
		
		close(_fd_cs3);
	}
}

void em_save_mem(void)
{
	if (!_p_NWRAM_mem)
		return;

	if (_p_mem_buff){
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: Buffer for %M is not empty!");
		free(_p_mem_buff);
		_p_mem_buff = NULL;
	}

	_p_mem_buff = malloc(_cs3_Mmem_size);
	if(!_p_mem_buff)
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: malloc for %M to save from zeroing failed!");
	else
		memcpy(_p_mem_buff, _p_NWRAM_mem, _cs3_Mmem_size);

}

void em_restore_mem(void)
{
	if(!_p_mem_buff && !_p_NWRAM_mem){
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Error: pointers to restored memory is wrong!");
	} else{

		RTS_UI32 state;
		
		
		memcpy(_p_NWRAM_mem, _p_mem_buff, _cs3_Mmem_size);
	

		free(_p_mem_buff);
		_p_mem_buff = NULL;
		
	}
}


static void handler_evt_done_update_configuration(EventParam *pEventParam)
{
	// if (pEventParam->usParamId == EVTPARAMID_CmpIoMgr
	//     && pEventParam->EventId == EVT_DoneUpdateConfiguration){
	// 	// CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0,
	// 		// "*** EVT_DoneUpdateConfiguration received ***");
	// }
}


uint32_t CDECL CmpEmiconMemManager_get_cs3_allocated_mem_size(void)
{
	return _cs3_Mmem_size;
}

int16_t CDECL CmpEmiconMemManager_mem_to_file(long int l_byte, long int b_byte)
{
	int fd;
	int64_t res;
	mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;

	if (l_byte > b_byte || l_byte < 0 || b_byte > _cs3_Mmem_size) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
				"Fail - Violation of memory boundaries!");
		return -3;
	}
	

	fd = open("/home/plc/mem_dump", O_CREAT | O_WRONLY | O_TRUNC, mode);
	if (fd < 0)
		return -1;

	res = write(fd, &l_byte, sizeof(l_byte));
	if (res < 0)
		return -2;

	res = write(fd, &b_byte, sizeof(b_byte));
	if (res < 0)
		return -2;

	if (l_byte == 0 && b_byte == 0) {
		res = write(fd, _p_NWRAM_mem, _cs3_Mmem_size);
		if (res < 0)
			return -2;
	} else {
		res = write(fd, _p_NWRAM_mem + l_byte, b_byte - l_byte + 1);
		if (res < 0)
			return -2;

	}
	close(fd);

	return 0;
}

int16_t CDECL CmpEmiconMemManager_file_to_mem(void)
{
	int fd;
	struct stat st;
	char *file_name = "/home/plc/mem_dump";
	char *gpio16_file_name = "/sys/class/gpio/gpio16/";
	int64_t res;
	long int l_byte;
	long int b_byte;
	bool gpio_value;

	stat(file_name, &st);
	if (st.st_size - sizeof(long int) * 2 > _cs3_Mmem_size)
		return -2;

	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return -1;

	res = read(fd, &l_byte, sizeof(l_byte));
	if (res < 0)
		return -3;

	res = read(fd, &b_byte, sizeof(b_byte));
	if (res < 0)
		return -3;

	/*
		Перед копированием в память необходимо считать и запомнить
		состояние GPIO_16. Затем установить состояние GPIO_16 в 1.
		После этого копировать содержимое файла в адресуемую память. 
		После окончания копирования вернуть состояние GPIO_16, в то,
		которое было до начала копирования. (ТЗ)
	*/

	// 1. проверить активизацию gpio16
	if(access(gpio16_file_name, F_OK) != 0) {
		// gpio16 не существует - активируем
		CAL_CmpEmiconSys_gpio_export(16);
		CAL_CmpEmiconSys_gpio_set_direction(16, "out");
	}

	gpio_value = CAL_CmpEmiconSys_gpio_get_value(16);
	CAL_CmpEmiconSys_gpio_set_value(16, 1);

	if (l_byte == 0 && b_byte == 0) {
		res = read(fd, _p_NWRAM_mem, _cs3_Mmem_size);
		if (res < 0)
			return -3;
	} else {
		res = read(fd, _p_NWRAM_mem + l_byte, b_byte - l_byte + 1);
	}

	close(fd);
	CAL_CmpEmiconSys_gpio_set_value(16, gpio_value);
	return 0;
}

void *get_nvram_mem(uint32_t size, uint32_t page_mask)
{
	void *p_mem;

	_fd_cs3 = open("/dev/mem", O_RDWR | O_SYNC);
	p_mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, _fd_cs3,
		     (CS3_MEM_ADDRESS & ~page_mask));

	return p_mem;
}

void *get_file_nvram_mem(uint32_t size)
{
	void *p_mem;
	struct stat sb;
	RTS_I32 nvram_sz = 0;
	char buffer[1024] = {0};
	RTS_RESULT res;
	int max_size_file_name = MAX_SZ_FILE_NAME;
	char str[200];

	/*
	 * Считываем из настроек rts размер всей NVRAM для дальнейшего
	 * создания файла имитации NVRAM.
	 */
	if (CAL_SettgGetIntValue(COMPONENT_NAME, "NVRAMSize", &nvram_sz, 0,
				CMPSETTINGS_CACHED) != ERR_OK) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			   "Error of reading NVRAMSize from cfg files!");

		return MAP_FAILED;
	}

	res = CAL_SettgGetStringValue("Emulation", "nvram_mem_file_name",
			nvram_mem_file_name, &max_size_file_name, "", 0);

	if (res != ERR_OK || strlen(nvram_mem_file_name) == 0) {
		sprintf(str, "Error: Emulation mode is detected but no file name for memory emulation is set in runtime cfg!");
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0,
			str);

		return MAP_FAILED;
	}

	_fd_cs3 = open(nvram_mem_file_name, O_RDWR | O_CREAT, 
		       S_IRUSR | S_IRGRP | S_IROTH);

	/*
	 * Определяем размер файла симуляции, и при меньшем размере чем 
	 * _cs3_Mmem_size дополняем его нулями. При большем размере
	 * обрезать не следует - это позволит экспериментировать с меньшим
	 * выделением памяти NVRAM из МЭК без потерь данных предыдущего
	 * большего размера.
	 */
	if (fstat(_fd_cs3, &sb) == -1)
		return MAP_FAILED;

	if (sb.st_size < nvram_sz)
		for (int i = 0; i < nvram_sz / sizeof(buffer); i++)
			write(_fd_cs3, &buffer, sizeof(buffer));

	p_mem = mmap(0, _cs3_Mmem_size, PROT_READ | PROT_WRITE,
		     MAP_SHARED, _fd_cs3, 0);

	return p_mem;
}


void init_mem_buff(mem_buffer *buff, uint32_t physical_addr, uint32_t size)
{

	uint32_t page_mask, page_size;
	void *p_mem;
	uint32_t pg_size; // размер памяти кратный размеру страницы (page_size)

	if (size == 0)
		return;

	page_size = sysconf(_SC_PAGESIZE);
	page_mask = (page_size - 1);

	pg_size = ((size / page_size) * page_size);

	p_mem = mmap(0, pg_size, PROT_READ | PROT_WRITE, MAP_SHARED, _fd_cs3,
		physical_addr & ~page_mask);

	buff->p = p_mem;
	buff->size = pg_size;
	CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO,
		ERR_FAILED, 0, "sys_var_area init. addr %X, size %d",
		buff->p, buff->size);
}


void CDECL get_sys_var_area(mem_buffer *buff)
{
	*buff = sys_var_area;
}