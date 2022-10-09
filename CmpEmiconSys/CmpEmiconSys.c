/**
 * <name>CmpEmiconSys</name>
 * <description> 
 *  Компонент инициализирует память по чипселектам 1 и 2,
 *  реализует функционал inhibit и watchdog сигналов.
 *
 * В режиме эмуляции сигнал inhibit передается системной
 * командой ping не чаще 1 раза в секунду. Это ограничение следует
 * из минимального времени ожидания ответа команды ping в этой сборке ОС.
 * Если посылать чаще при отсутвии отвечающего ЦПУ, то генерирование
 * процессов ping будет чаще, чем они будут успевать заканчиваться.
 * Отсюда следует другое ограничение - это время снятия сигнала inhibit
 * на резервном ЦПУ - 2 секунды. За это время хоть одна команда пинга должна
 * пройти.
 * Этот функционал был внедрен для тестирования некоторых функций вкладки 
 * EmiconSettings в режиме эмуляции связанных с inhibit.
 *   
 * Для тестов других целей, следует учитывать долгое время снятия сигнала inhibit.
 * Функция clr_inhibit в режиме эмуляции не работает.
 * 
 * При смене ролей основной/резервный смены IP не происходит. Поэтому ЦПУ должны
 * знать IP своей пары. Этот IP задается в CODESYSControl.cfg в секции Emulation
 * Пример:
 * [Emulation]
 * emu_ip_second_cpu=192.168.67.3
 * 
 */
#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconSysDep.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/time.h> 
#include <fcntl.h>
#include <time.h>

const char *MEM_FILE_NAME[] = {
	"cs1_mem",
	"cs2_mem",
};

static int _fd_cs[2];
static bool _is_emu = false;

#define CS_NUM_MAX 2
#define CS1 1
#define CS2 2

#define SetInhibitAddr 0x40000
#define ClrInhibitAddr 0x70000

#define GPIO_ACTIVE 0
#define GPIO_NOTACTIVE 1

#define GPIO_INHIBIT 49
#define MAX_SIZE_IP_ADDR_STR 17
#define INHIBIT_LIFETIME 500 // ms после которого inhibit сбрасывается автоматически
#define INHIBIT_LIFETIME_EMU 2000

// минимальны период в мс посылки пинга-инхибита в режиме эмуляции. Вызовы чаще
// этого значения будут игнорироваться. это значение должно быть меньше INHIBIT_LIFETIME_EMU
// более детальное описание см inhibit_emulation()
#define MIN_PING_PERIOD 750 //1411 

// папка для создания информационных файлов рантаймом
#define PROC_FOLDER "/tmp/CDS"
#define FILE_APP_STATE "appstate"
#define FILE_CMD_SET_TO_RESERVE "set_to_reserve"

// Роли CPU по сигналу inhibit
#define INHIBIT_CPU_RESERV 0
#define INHIBIT_CPU_MAIN 1
#define INHIBIT_CPU_NOT_DEF 3


// ip второго эмулируемого цпу. Нужно для посылки inhibit.
// указывается в cfg в секции [Emulation]
static char str_emu_ip_second_cpu[MAX_SIZE_IP_ADDR_STR]; 

const uint32_t mem_address[CS_NUM_MAX] = {0x4000000, 0x3000000}; 
const uint32_t mem_size[CS_NUM_MAX] = {ClrInhibitAddr+1, 0x20000};

uint32_t alloc_mem_size[CS_NUM_MAX], page_mask, page_size;
void *mem_pointer[CS_NUM_MAX], *virt_addr[CS_NUM_MAX];
int fd_mem;
int ret;
uint32_t SockArr[256];

int fd_fifo;

unsigned long inhibit_send_time_ms = 0;
unsigned long g_curent_time_ms;
unsigned long g_max_time_ms = 0;
struct timeval g_tv;

static RTS_HANDLE hEvtStateChanged = RTS_INVALID_HANDLE;
static RTS_HANDLE hEvtAppDownloadDone = RTS_INVALID_HANDLE;
static void app_state_changed_handler(EventParam *pEventParam);

int memory_init (unsigned char cs_num);
int memory_unmap (unsigned char cs_num);

void CloseAllSocket(void);
void InitAllSocket(void);
void inhibit_emulation(void);
void write_inhibit_to_file(int val, bool force);
void inhibit_control(void);
unsigned long getTickMS();

int watchdog_enabled = 0;

USE_STMT

#ifndef RTS_COMPACT_MICRO

/**
 * <description>Entry function of the component. Called at startup for each component. Used to exchange function pointers with the component manager.</description>
 * <param name="pInitStruct" type="IN">Pointer to structure with:
 *		pfExportFunctions	OUT Pointer to function that exports component functions
 *		pfImportFunctions	OUT Pointer to function that imports functions from other components
 *		pfGetVersion		OUT Pointer to function to get component version
 *		pfRegisterAPI		IN	Pointer to component mangager function to register a api function
 *		pfGetAPI			IN	Pointer to component mangager function to get a api function
 *		pfCallHook			IN	Pointer to component mangager function to call a hook function
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

	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2: {

		int fd;
		struct stat st = {0};
		char str[256];

		if (stat(PROC_FOLDER, &st) == -1) {
			printf("Create folder %s", PROC_FOLDER);
    		mkdir(PROC_FOLDER, 0777);
		} else {
			printf("Folder %s exists", PROC_FOLDER);
		}

    	sprintf(str, "%s/%s", PROC_FOLDER, FILE_APP_STATE);
    	fd = open(str, O_WRONLY | O_CREAT);
    	if (fd > 0) {
    		write(fd, "0\n", 2);
    		close(fd);
    	}
		break;
	}
	case CH_INIT3:
		if (CHK_CmpEmiconEmu_is_emu)
			_is_emu = CAL_CmpEmiconEmu_is_emu();

		hEvtStateChanged = CAL_EventOpen(EVT_StateChanged, CMPID_CmpApp, NULL);
		CAL_EventRegisterCallbackFunction(hEvtStateChanged, app_state_changed_handler, 0);
		hEvtAppDownloadDone = CAL_EventOpen(EVT_DownloadDone, CMPID_CmpApp, NULL);
		CAL_EventRegisterCallbackFunction(hEvtAppDownloadDone, app_state_changed_handler, 0);

		if (_is_emu) {
			system("rm -rf fifo");
			system("mkfifo fifo");
			system("tcpdump ip proto \\\\icmp -s 1 -l -p -tt -U | awk '{ print $1 }' > fifo &");
			fd_fifo = open("fifo", O_RDONLY);
			int flags = fcntl(fd_fifo, F_GETFL, 0);
			fcntl(fd_fifo, F_SETFL, flags | O_NONBLOCK);

			CmpEmiconSys_gpio_export(GPIO_INHIBIT);
			CmpEmiconSys_gpio_set_direction(GPIO_INHIBIT, "out");
			CmpEmiconSys_gpio_set_value(GPIO_INHIBIT, GPIO_ACTIVE); // 0- отключенный инхибит, но это активный gpio

			int max_size_ip_addr_str = MAX_SIZE_IP_ADDR_STR;
			RTS_RESULT res = CAL_SettgGetStringValue("Emulation", "emu_ip_second_cpu",
			str_emu_ip_second_cpu, &max_size_ip_addr_str, "", 0);
			if (res != ERR_OK || strlen(str_emu_ip_second_cpu) == 0) {
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0,"No IP of second CPU found in runtime cfg. Inhibit sending will be skipped.");
			}
		}
		memory_init(CS1);
		memory_init(CS2);
		InitAllSocket();
		write_inhibit_to_file(INHIBIT_CPU_NOT_DEF, true);

		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:

		g_curent_time_ms = getTickMS();

		if (_is_emu)
			inhibit_emulation();

		inhibit_control();

		break;

	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		memory_unmap(CS1);
		memory_unmap(CS2);
		CloseAllSocket();
		write_inhibit_to_file(INHIBIT_CPU_NOT_DEF, true);

		CAL_EventUnregisterCallbackFunction(hEvtStateChanged, app_state_changed_handler);
		CAL_EventClose(hEvtStateChanged);
		CAL_EventUnregisterCallbackFunction(hEvtAppDownloadDone, app_state_changed_handler);
		CAL_EventClose(hEvtAppDownloadDone);
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:

		EXIT_STMT;
		break;
	default:
		break;
	}

	return ERR_OK;
}


int memory_init (unsigned char cs_num) {

	unsigned char i;
	struct stat sb;
	char buffer[1024] = {0};
	int j;

	if ((cs_num < 1) || (cs_num > CS_NUM_MAX))
		return -1;
	else
		i = cs_num - 1;

	page_size = sysconf(_SC_PAGESIZE);
	alloc_mem_size[i] = (((mem_size[i] / page_size) + 1) * page_size);

	if (!_is_emu) {
		page_mask = (page_size - 1);
		fd_mem = open("/dev/mem", O_RDWR | O_SYNC);
		mem_pointer[i] = mmap(NULL,
					alloc_mem_size[i],
					PROT_READ | PROT_WRITE,
					MAP_SHARED,
					fd_mem,
					(mem_address[i] & ~page_mask)
				 );
		if(mem_pointer[i] == MAP_FAILED) { 
			fflush(stdout);
			return -1;
		};
		
		virt_addr[i] = (mem_pointer[i] + (mem_address[i] & page_mask));

	} else {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Emulation mode detected!");

		_fd_cs[i] = open(MEM_FILE_NAME[i], O_RDWR | O_CREAT,
				 S_IRUSR | S_IRGRP | S_IROTH);
		if (fstat(_fd_cs[i], &sb) == -1){
			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
			ERR_FAILED, 0, 
			"Failed: fstat CS: %s",
			strerror(errno));
			return -1;
		}

		if (sb.st_size < alloc_mem_size[i]) {
			for (j = 0; j < alloc_mem_size[i]/sizeof(buffer); j++)
				write(_fd_cs[i], &buffer, sizeof(buffer));

			CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Fail CS sim is written to: %d", alloc_mem_size[i]);
		}

		virt_addr[i] = mmap(0, alloc_mem_size[i], PROT_READ | PROT_WRITE,
		     		    MAP_SHARED, _fd_cs[i], 0);

	}

	fflush(stdout);
	return 0;
}

int memory_unmap (unsigned char cs_num) {
    if((cs_num < 1) || (cs_num > CS_NUM_MAX)) return -1;
	
	if(munmap(mem_pointer[cs_num-1], alloc_mem_size[cs_num-1]) == -1)
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Memory dealloc failed: CS%d", cs_num);
	else
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_FAILED, 0, 
			"Memory deallocated: CS%d", cs_num);

	close(fd_mem);

	return 0;
}


void CDECL CDECL_EXT set_inhibit(set_inhibit_struct *p)
{

	/* Запись в регистр 40000Н любого числа освежает INHIBIT
	 * Поддержку сигнала INHIBIT следует производить не реже 10 мс
	 */

	static char str_cmd[50];

	write_inhibit_to_file(INHIBIT_CPU_MAIN, false);

	if (!_is_emu) {
		*((unsigned char *)virt_addr[0] + SetInhibitAddr) = 1;
		inhibit_send_time_ms = g_curent_time_ms;
	} else {
		// в режиме эмуляции посылаем пинг. Но пинг не следует посылать часто,
		// поэтому искуственно тут ограничиваем посылку не чаще чем раз в 1000 мс.

		if (strlen(str_cmd) == 0 && strlen(str_emu_ip_second_cpu))
			sprintf(str_cmd, "ping %s -c1 -W1 > /dev/null &", str_emu_ip_second_cpu);

		if (g_curent_time_ms - inhibit_send_time_ms > MIN_PING_PERIOD){
			if (strlen(str_cmd) > 0)
				system(str_cmd);
			inhibit_send_time_ms = g_curent_time_ms;
		}
	}

}

void CDECL CDECL_EXT clr_inhibit(clr_inhibit_struct *p)
{
	*((unsigned char *)virt_addr[0] + ClrInhibitAddr) = 1;
	inhibit_send_time_ms = 0;
	write_inhibit_to_file(INHIBIT_CPU_RESERV, false);
}

void CDECL CDECL_EXT set_watchdog(set_watchdog_struct *p)
{
	/*
		Активация циклом 1.6 секунды в регистр 50000Н
	*/
	int output_fd;
	char str[4];
	if (!watchdog_enabled) {

		CmpEmiconSys_gpio_export(96);
		CmpEmiconSys_gpio_set_direction(96, "out");
		CmpEmiconSys_gpio_set_value(96, 0);

		watchdog_enabled = TRUE;
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, 
			"Watchdog is activated");

	}

	*((unsigned char *)virt_addr[0] + 0x50000) = 1;
	
}


// Возвращает указатель на нулевой слот
void CDECL CDECL_EXT get_ptr_to_slot0(get_ptr_to_slot0_struct *p)
{

	if (virt_addr[0] != NULL) {
		p->Get_ptr_to_slot0 = (unsigned char*)(virt_addr[0]);
	} else {
		p->Get_ptr_to_slot0 = 0;
	}
}

// возвращает указатель на ДПМ
void CDECL CDECL_EXT get_ptr_to_dpm(get_ptr_to_dpm_struct *p)
{

	if (virt_addr[1] != NULL) {
		p->Get_ptr_to_DPM = (unsigned short*)(virt_addr[1]);
	} else {
		p->Get_ptr_to_DPM = 0;
	}
}

void CDECL CDECL_EXT get_ptr_to_sock_arr(get_ptr_to_sock_arr_struct *p)
{

	p->Get_ptr_to_sock_arr = SockArr;
}

void CloseAllSocket(void)
{

	int i;

	for (i=0; i<256; i++) {
		if (SockArr[i]) {
			close(SockArr[i]);
			SockArr[i]=0;
		}
	}
}

void InitAllSocket(void)
{

	int i;

	for (i=0; i<256; i++) SockArr[i]=0;
}

void CDECL CDECL_EXT syssync(syssync_struct *p)
{

	system("sync");
}

void CDECL CDECL_EXT get_ptr_to_sys_area(get_ptr_to_sys_area_struct *p)
{

	mem_buffer buff;

	CAL_get_sys_var_area(&buff);
	p->get_ptr_to_sys_area = buff.p;
}

void CDECL CDECL_EXT get_size_of_sys_area(get_size_of_sys_area_struct *p)
{

	mem_buffer buff;

	CAL_get_sys_var_area(&buff);
	p->get_size_of_sys_area = buff.size;
}


void CDECL CDECL_EXT is_emu(is_emu_struct *p)
{

	p->is_emu = _is_emu;
}



bool CDECL CmpEmiconSys_gpio_export(uint8_t n)
{

	int fd;
	char str[40];

	if (_is_emu) {
		sprintf(str, "/tmp/gpio%d.emu", n);
		if (access(str, F_OK ) != 0) {
   			sprintf(str, "echo 1 > /tmp/gpio%d.emu", n);
			system(str);
		}

		return true;
	}

	sprintf(str, "%d", n);
	fd = open("/sys/class/gpio/export", O_WRONLY);
	write(fd, str, strlen(str));
	close(fd);

	return true;
}

bool CDECL CmpEmiconSys_gpio_set_direction(uint8_t n, char *direction)
{

	int fd;
	char str[35];

	if (_is_emu) {
		CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, 
			ERR_FAILED, 0, 
			"Emulation: Set direction GPIO_%d to \"%s\"", n, direction);
		return true;
	}

	sprintf(str, "/sys/class/gpio/gpio%d/direction", n);
	fd = open(str, O_WRONLY);
	write(fd, direction, strlen(direction));
	close(fd);
	return true;
}

bool CDECL CmpEmiconSys_gpio_get_value(uint8_t n)
{

	int fd;
	char str[35];

	if (_is_emu)
		sprintf(str, "/tmp/gpio%d.emu", n);
	else
		sprintf(str, "/sys/class/gpio/gpio%d/value", n);

	fd = open(str, O_RDONLY);
	if(fd != 0) {
		sprintf(str,"%d", 1);
		// Если с read пойдет чтото не так, то в str останеться 1
		// что соотвевует НЕ активному gpio
		read(fd, str, 1);
		close(fd);
	}

	//48 = ascii 0, 49 = ascii 1
	return str[0] == 49;
}

bool CDECL CmpEmiconSys_gpio_set_value(uint8_t n, uint8_t val)
{

	int fd;
	char str[35];

	if (_is_emu)
		sprintf(str, "/tmp/gpio%d.emu", n);
	else
		sprintf(str, "/sys/class/gpio/gpio%d/value", n);

	fd = open(str, O_WRONLY);
	if(fd != 0) {
		sprintf(str, "%d", val);
		write(fd, str, strlen(str));
		close(fd);
	}

	return true;
}

void CDECL CDECL_EXT gpioexport(gpioexport_struct *p)
{

	p->gpioExport = CmpEmiconSys_gpio_export(p->n);
}

void CDECL CDECL_EXT gpiogetvalue(gpiogetvalue_struct *p)
{

	p->gpioGetValue = CmpEmiconSys_gpio_get_value(p->n);
}

void CDECL CDECL_EXT gpiosetdirection(gpiosetdirection_struct *p)
{

	if (p->direction)
		p->gpioSetDirection = CmpEmiconSys_gpio_set_direction(p->n, "in");
	else
		p->gpioSetDirection = CmpEmiconSys_gpio_set_direction(p->n, "out");
}

void CDECL CDECL_EXT gpiosetvalue(gpiosetvalue_struct *p)
{
	p->gpioSetValue = CmpEmiconSys_gpio_set_value(p->n, p->val);
}

void CDECL CmpEmiconSys_clr_inhibit(void)
{
	clr_inhibit(NULL);
}

void inhibit_emulation(void)
{

	/* Реальный ихибит работает так: 
	 * Функция set_inhibit по определенному адресу пишет любые данные. Это приводит
	 * к сбросу таймера, контролирующего инхибит. Если запись по адресу не
	 * производится более 10 мс (по другим данным более 500 мс), то сигнал инхибит
	 * снимается. Физически сигнал инхибит представляет собой установку определенного
	 * gpio на втором ЦПУ. Этот gpio считывается вторым ЦПУ для определения сотояния
	 * первого ЦПУ.
	 * В режиме эмуляции инхибит заменяется на ping по сети. Сигнал ping посылается
	 * функцией set_inhibit. В этой функции считывается пакет ping и фиксируется
	 * время. Если время между ping менее 500 мс, устанавливаем (собственный) gpio
	 * в логическую 1. В эмуляции перегружать ping сеть не желательно, поэтому выбираем
	 * больший интервал посылок. Таким образом отличие от реального процесса в том, что
	 * не gpio передается от другого ЦПУ, а процесс обновления таймера. Сам же таймер
	 * установит собственный gpio, который на этом же ЦПУ будет считываться
	 * (в эмуляции это позволляется) для анализа.
	 */

	static unsigned long recive_time_point_ms = 0;
	char str1[100];
	int num;
	int fd;
	static bool state = false;

	num = read(fd_fifo, str1, 99); // не блокирующая

	// после посылки ping-inhibit второй цпу ответит на пинг. Отвечает он серией пакетов
	// который растягивается во времени в среднем около 250 мс, но бывает и до MIN_PING_PERIOD.
	// Значение MIN_PING_PERIOD  было установлено эксперементально - это максимальное время прихода
	// ответных сигналов. Время это зависит от загрузки сети.
	// Ответ на пинг будет считан тут, и его нужно игнорировать. Для этого анализируем время посылки инхибита.
	// посылки инхибита. Считаем, что этот ЦПУ не шлет больше инхибит, если время посылки не
	// обновлялось более MIN_PING_PERIOD мс и полученные сигналы это не ответ от второго ЦПУ,
	// а его пинг в эту сторону, который нужно регистрировать.

	if (num > 0 && g_curent_time_ms - inhibit_send_time_ms > MIN_PING_PERIOD) {
			recive_time_point_ms = g_curent_time_ms;
			if (!state) {
				CmpEmiconSys_gpio_set_value(GPIO_INHIBIT, GPIO_NOTACTIVE); // включаем инхибит
				state = true;
			}
	}

	// выключаем инхибит если время от последнего сигнала более INHIBIT_LIFETIME_EMU
	if (state && g_curent_time_ms - recive_time_point_ms >= INHIBIT_LIFETIME_EMU) {
		CmpEmiconSys_gpio_set_value(GPIO_INHIBIT, GPIO_ACTIVE);
		state = false;
	}


}


/*
 * write_inhibit_to_file записывает значение val в информационный
 * файл inhibit. 
 * Если значене val не менялось с предыдущего вызова, то запись в файл
 * игнорируется при флаге force == false. При флаге force == true 
 * запись производиться без условий изменения val.
 */
void write_inhibit_to_file(int val, bool force)
{

	int fd_inhibit;
	static int old_val;
	char str[50];

	if (!force && old_val == val)
		return;

	sprintf(str, "%s/inhibit", PROC_FOLDER);
	fd_inhibit = open(str, O_WRONLY | O_CREAT);
	if (fd_inhibit > 0) {
		sprintf(str, "%d\n", val);
		write(fd_inhibit, str, strlen(str));
		close(fd_inhibit);
	}

	old_val = val;

}

/* 
 * inhibit_control проверяет разницу времени (dt) между текущим временем
 * и временем последней посылки сигнала инхибит. Если dt больше времени
 * жизни аппаратного инхибита (dt_limit), то функция вызывает функцию записи
 * в информационный файл inhibit значение 0.
 */
void inhibit_control(void)
{

	unsigned long dt_limit = _is_emu ? INHIBIT_LIFETIME_EMU : INHIBIT_LIFETIME;
	unsigned long dt = g_curent_time_ms - inhibit_send_time_ms;

	if (dt >= dt_limit)
			write_inhibit_to_file(INHIBIT_CPU_RESERV, false);

}


void CDECL CDECL_EXT getrequesttoreserve(getrequesttoreserve_struct *p)
{

	char str[5] = "0\n";
	char file_path[50];
	int fd;
	int num = 0;
	int res = -1;

	sprintf(file_path, "%s/%s", PROC_FOLDER, FILE_CMD_SET_TO_RESERVE);
	fd = open(file_path,  O_RDONLY| O_CREAT);
	if (fd > 0) {
		res = 0;
		num = read(fd, str, 1);
		close(fd);

		if (num > 0) 
			res = atoi(str);

		if (res != 0 || num == 0) {
			sprintf(str, "%d\n", 0);
			fd = open(file_path, O_WRONLY);
			write(fd, str, strlen(str));
			close(fd);
		}
	
	}

	p->getRequestToReserve = res;
	return;
}

unsigned long getTickMS()
{

	struct timespec ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);

	return ts.tv_sec * 1000 + lround(ts.tv_nsec / 1e6);
}

 static void app_state_changed_handler(EventParam *pEventParam)
 {

 	int fd;
 	char str[50];

	/* Use pEventParam->CmpIdProvider to identify the component that posts 
	the event. Note that pEventParam->EventId is not unique in the system */
	if (pEventParam->CmpIdProvider != CMPID_CmpApp){
		return;
	}

	sprintf(str, "%s/%s", PROC_FOLDER, FILE_APP_STATE);
	fd = open(str, O_WRONLY | O_CREAT);
	if (fd <= 0)
		return;

	if (pEventParam->EventId == EVT_StateChanged){
		EVTPARAM_CmpApp_StateChanged *pParam = (EVTPARAM_CmpApp_StateChanged *)pEventParam->pParameter;
		sprintf(str, "%d\n", pParam->pApp->ulState);
		write(fd, str, strlen(str));
	}

	if (pEventParam->EventId == EVT_DownloadDone){
		sprintf(str, "%lu\n", AS_STOP);
		write(fd, str, strlen(str));
	}
	close(fd);

}