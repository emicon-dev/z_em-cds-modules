/*
 *	Создание событий на передний фронт GPIO с 50 по 53 и 56.
 *	GPIO 56 - это кнопка B на панели ЦПУ-47.
 *	GPIO 50-53 - сигналы слотов 0-3.
 *	На создаваемые события можно определять обработчики как в Си,
 *	так и в МЭК.
 *
 *	Принцип работы: В цикле читаются gpio, регистрируется передний
 *  фронт, генерируется событие.
 *
 *	Обработчики привязываются к:
 *	EVT_B_BUTTON_PRESSED
 *	EVT_GPIO_50
 *	EVT_GPIO_51
 *	EVT_GPIO_52
 *	EVT_GPIO_53
 * 
 *	ВНИМАНИЕ! GPIO имеет инверсную логику! Передним фронтом
 *  считаем переход из 1 в 0. В тексте программы определяется
 * 	define NOT_ACTIVE_GPIO и ACTIVE_GPIO
*/ 

#include <stdbool.h>
#include "CmpStd.h"
#include "CmpEmiconEventsControlDep.h"
#include <unistd.h>
#include <fcntl.h>

#define EVTPARAMID_CmpEmiconEventsControl	0x0001
#define EVTVERSION_CmpEmiconEventsControl	0x0001

#define EVT_B_BUTTON_PRESSED MAKE_EVENTID(EVTCLASS_INFO, 1)
#define EVT_GPIO_50 MAKE_EVENTID(EVTCLASS_INFO, 2)
#define EVT_GPIO_51 MAKE_EVENTID(EVTCLASS_INFO, 3)
#define EVT_GPIO_52 MAKE_EVENTID(EVTCLASS_INFO, 4)
#define EVT_GPIO_53 MAKE_EVENTID(EVTCLASS_INFO, 5)

static RTS_HANDLE _h_B_button = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_50 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_51 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_52 = RTS_INVALID_HANDLE;
static RTS_HANDLE _h_gpio_53 = RTS_INVALID_HANDLE;

USE_STMT
// GPIO имеет инверсную логику
#define NOT_ACTIVE_GPIO true
#define ACTIVE_GPIO false

typedef struct gpio_control {
	uint8_t n;
	bool old_satate;
	bool enabled;
} gpio_control;

gpio_control _B_button = {
	.n = 56, 		// кнопка B
	.old_satate = NOT_ACTIVE_GPIO,
	.enabled = false,
};

gpio_control _gpio_50 = {
	.n = 50,
	.old_satate = NOT_ACTIVE_GPIO,
	.enabled = false,
};

gpio_control _gpio_51 = {
	.n = 51,
	.old_satate = NOT_ACTIVE_GPIO,
	.enabled = false,
};

gpio_control _gpio_52 = {
	.n = 52,
	.old_satate = NOT_ACTIVE_GPIO,
	.enabled = false,
};
gpio_control _gpio_53 = {
	.n = 53,
	.old_satate = NOT_ACTIVE_GPIO,
	.enabled = false,
};

EventParam _tEventParam = {
	.pParameter = NULL,
	.usParamId = EVTPARAMID_CmpEmiconEventsControl,
	.usVersion = EVTVERSION_CmpEmiconEventsControl,
	.CmpIdProvider = CMPID_CmpEmiconEventsControl,
};
void enable_gpio(gpio_control *gpio);
bool r_trig_gpio(gpio_control *gpio); //детекция переднего фронта

static RTS_RESULT CDECL CreateEvents(void)
{

	_h_B_button = CAL_EventCreate2(EVT_B_BUTTON_PRESSED, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	_h_gpio_50 = CAL_EventCreate2(EVT_GPIO_50, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	_h_gpio_51 = CAL_EventCreate2(EVT_GPIO_51, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	_h_gpio_52 = CAL_EventCreate2(EVT_GPIO_52, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);
	_h_gpio_53 = CAL_EventCreate2(EVT_GPIO_53, COMPONENT_ID,
					EVENT_CALLBACKS_NO_LIMIT, NULL);

	return ERR_OK;
}


/**
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
 */
static int CDECL ExportFunctions(void)
{
	/* Macro to export functions */
	EXPORT_STMT;
	return ERR_OK;
}

/**
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

/**
 */
static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1,
				     RTS_UINTPTR ulParam2)
{
	int res;

	switch (ulHook) {
	case CH_INIT:
		break;
	case CH_INIT2:
		break;
	case CH_INIT3:
		CreateEvents();

		break;
	case CH_INIT_TASKS:
		break;
	case CH_INIT_COMM:
		break;
	case CH_INIT_FINISHED:
		break;

	/* Cyclic */
	case CH_COMM_CYCLE:
		
		if (r_trig_gpio(&_B_button)) {
			_tEventParam.EventId = EVT_B_BUTTON_PRESSED;
			res = CAL_EventPost(_h_B_button, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_50)) {
			_tEventParam.EventId = EVT_GPIO_50;
			res = CAL_EventPost(_h_gpio_50, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_51)) {
			_tEventParam.EventId = EVT_GPIO_51;
			res = CAL_EventPost(_h_gpio_51, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_52)) {
			_tEventParam.EventId = EVT_GPIO_52;
			res = CAL_EventPost(_h_gpio_52, &_tEventParam);
		}
		if (r_trig_gpio(&_gpio_53)) {
			_tEventParam.EventId = EVT_GPIO_53;
			res = CAL_EventPost(_h_gpio_53, &_tEventParam);
		}

		break;


	case CH_EXIT_COMM:
		break;
	case CH_EXIT_TASKS:
		break;
	case CH_EXIT3:
		CAL_EventClose(_h_B_button);
		CAL_EventClose(_h_gpio_50);
		CAL_EventClose(_h_gpio_51);
		CAL_EventClose(_h_gpio_52);
		CAL_EventClose(_h_gpio_53);

		CAL_EventDelete(_h_B_button);
		CAL_EventDelete(_h_gpio_50);
		CAL_EventDelete(_h_gpio_51);
		CAL_EventDelete(_h_gpio_52);
		CAL_EventDelete(_h_gpio_53);
		break;
	case CH_EXIT2:
		break;
	case CH_EXIT:
		EXIT_STMT;
		break;

	}

	return ERR_OK;
}

void enable_gpio(gpio_control *gpio)
{

	if (gpio->enabled)
		return;

	if (CHK_CmpEmiconSys_gpio_export)
		CAL_CmpEmiconSys_gpio_export(gpio->n);
	else
		return;

	CAL_CmpEmiconSys_gpio_set_direction(gpio->n, "in");
	gpio->enabled = true;
	gpio->old_satate = NOT_ACTIVE_GPIO;
}

bool r_trig_gpio(gpio_control *gpio)
{

	bool gpio_val;
	bool ret = false;

	if (!gpio->enabled) {
		enable_gpio(gpio);
		ret = false;
	}

	gpio_val = CAL_CmpEmiconSys_gpio_get_value(gpio->n);

	if (gpio_val == ACTIVE_GPIO && gpio->old_satate == NOT_ACTIVE_GPIO)
		ret = true;
	else
		ret = false;

	gpio->old_satate = gpio_val;

	return ret;
}