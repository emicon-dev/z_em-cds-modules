/*
 * Компонент определяет режим эмуляции ПЛК и предоставляет интерфейс для
 * определения режима другим компонентам.
 * Режим эмуляции определяется по наличию переменной окружения EMU.
 * Режим эмуляции определяется по имени EMULATOR_HOSTNAME. Поэтому не рекомендуется
 * эмулятору менять имя хоста (например через IDE CODESYS).
 */

#include <stdbool.h>
#include <sys/unistd.h>
#include <fcntl.h>
#include "CmpStd.h"
#include "CmpEmiconEmuDep.h"

#define EMULATOR_HOSTNAME "ememu"

static bool emulation_mode;

int determine_emulation_mode (void);

USE_STMT

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

static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

static int CDECL ImportFunctions(void)
{
	/* Macro to import functions */
	IMPORT_STMT;
	return ERR_OK;
}

static RTS_UI32 CDECL CmpGetVersion(void)
{
	return CMP_VERSION;
}


static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		determine_emulation_mode();
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

	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
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

bool CDECL CmpEmiconEmu_is_emu(void)
{
	return emulation_mode;
}

int determine_emulation_mode(void)
{

	int fd;
	char str[3];

	char hostname[128];
	gethostname(hostname, sizeof hostname);

	if (strstr(hostname, EMULATOR_HOSTNAME) != NULL) {
		emulation_mode = true;
		if (CHK_LogAdd)
				CAL_LogAdd(STD_LOGGER, COMPONENT_ID, LOG_INFO, ERR_OK, 0, "Emulation mode activated");
	} else {
		emulation_mode = false;
	}

	fd = open("/tmp/ememu", O_WRONLY | O_CREAT);
	if (fd != 0){
		sprintf(str,"%d\n", emulation_mode);
		write(fd, str, strlen(str));
		close(fd);
	}

	return 0;
};
