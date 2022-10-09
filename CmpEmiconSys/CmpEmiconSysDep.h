/***********************************************************************
 * DO NOT MODIFY!
 * This is a generated file. Do not modify it's contents directly
 ***********************************************************************/

/**
 *  <name>Component Template</name>
 *  <description> 
 *  An example on how to implement a component.
 *  This component does no usefull work and it exports no functions
 *  which are intended to be used for anything. Use at your own risk.
 *  </description>
 *  <copyright>
 *  (c) 2003-2016 3S-Smart Software Solutions
 *  </copyright>
 */
#ifndef _CMPEMICONSYSDEP_H_
#define _CMPEMICONSYSDEP_H_

#define COMPONENT_NAME "CmpEmiconSys" COMPONENT_NAME_POSTFIX
#define COMPONENT_ID    ADDVENDORID(CMP_VENDORID, CMPID_CmpEmiconSys)
#define COMPONENT_NAME_UNQUOTED CmpEmiconSys






#define CMP_VERSION         UINT32_C(0x03051114)
#define CMP_VERSION_STRING "3.5.17.20"
#define CMP_VERSION_RC      3,5,17,20

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
#define CMP_VENDORID       0x0001

#ifndef WIN32_RESOURCES

#include "CmpLogItf.h"
#include "CMUtilsItf.h"				

#define CMPID_CmpEmiconSys		0x2100								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconSys	ADDVENDORID(CMP_VENDORID, 0x2100)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconSys		ADDVENDORID(CMP_VENDORID, 0x2100)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */


/*Obsolete include: CMUtilsItf.m4*/


#include "SysFileItf.h"


#include "CmpSettingsItf.h"


#include "CmpAppItf.h"


#include "CmpEmiconEmuItf.h"


#include "CmpEmiconMemManagerItf.h"








/**
 * \file CmpEmiconSysItf.h
 */
#include "CmpEmiconSysItf.h"







        







     







     


        





      





      



#ifdef CPLUSPLUS
    #define INIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT initResult;\
        if (pICmpLog == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpLog, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpLog = (ICmpLog *)pIBase->QueryInterface(pIBase, ITFID_ICmpLog, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICMUtils == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCMUtils, &initResult); \
            if (pIBase != NULL) \
            { \
                pICMUtils = (ICMUtils *)pIBase->QueryInterface(pIBase, ITFID_ICMUtils, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
        if (pICmpEmiconMemManager == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEmiconMemManager, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEmiconMemManager = (ICmpEmiconMemManager *)pIBase->QueryInterface(pIBase, ITFID_ICmpEmiconMemManager, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpEmiconEmu == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpEmiconEmu, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpEmiconEmu = (ICmpEmiconEmu *)pIBase->QueryInterface(pIBase, ITFID_ICmpEmiconEmu, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpApp == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpApp, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpApp = (ICmpApp *)pIBase->QueryInterface(pIBase, ITFID_ICmpApp, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pICmpSettings == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CCmpSettings, &initResult); \
            if (pIBase != NULL) \
            { \
                pICmpSettings = (ICmpSettings *)pIBase->QueryInterface(pIBase, ITFID_ICmpSettings, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          if (pISysFile == NULL && s_pfCMCreateInstance != NULL) \
        { \
            pIBase = (IBase *)s_pfCMCreateInstance(CLASSID_CSysFile, &initResult); \
            if (pIBase != NULL) \
            { \
                pISysFile = (ISysFile *)pIBase->QueryInterface(pIBase, ITFID_ISysFile, &initResult); \
                pIBase->Release(pIBase); \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		   \
    }
    #define INIT_LOCALS_STMT \
    {\
        pICmpLog = NULL; \
        pICMUtils = NULL; \
        pICmpEmiconMemManager = NULL; \
          pICmpEmiconEmu = NULL; \
          pICmpApp = NULL; \
          pICmpSettings = NULL; \
          pISysFile = NULL; \
          /*Obsolete include CMUtils*/ \
		   \
    }
    #define EXIT_STMT \
    {\
        IBase *pIBase;\
        RTS_RESULT exitResult;\
        if (pICmpLog != NULL) \
        { \
            pIBase = (IBase *)pICmpLog->QueryInterface(pICmpLog, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpLog = NULL; \
            } \
        } \
        if (pICMUtils != NULL) \
        { \
            pIBase = (IBase *)pICMUtils->QueryInterface(pICMUtils, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICMUtils = NULL; \
            } \
        } \
        if (pICmpEmiconMemManager != NULL) \
        { \
            pIBase = (IBase *)pICmpEmiconMemManager->QueryInterface(pICmpEmiconMemManager, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEmiconMemManager = NULL; \
            } \
        } \
          if (pICmpEmiconEmu != NULL) \
        { \
            pIBase = (IBase *)pICmpEmiconEmu->QueryInterface(pICmpEmiconEmu, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpEmiconEmu = NULL; \
            } \
        } \
          if (pICmpApp != NULL) \
        { \
            pIBase = (IBase *)pICmpApp->QueryInterface(pICmpApp, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpApp = NULL; \
            } \
        } \
          if (pICmpSettings != NULL) \
        { \
            pIBase = (IBase *)pICmpSettings->QueryInterface(pICmpSettings, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pICmpSettings = NULL; \
            } \
        } \
          if (pISysFile != NULL) \
        { \
            pIBase = (IBase *)pISysFile->QueryInterface(pISysFile, ITFID_IBase, &exitResult); \
            if (pIBase != NULL) \
            { \
                 pIBase->Release(pIBase); \
                 if (pIBase->Release(pIBase) == 0) /* The object will be deleted here! */ \
                    pISysFile = NULL; \
            } \
        } \
          /*Obsolete include CMUtils*/ \
		   \
    }
#else
    #define INIT_STMT
    #define INIT_LOCALS_STMT
    #define EXIT_STMT
#endif



#if defined(STATIC_LINK)
    #define IMPORT_STMT
#else
    #define IMPORT_STMT \
    {\
        RTS_RESULT importResult = ERR_OK;\
        RTS_RESULT TempResult = ERR_OK;\
        INIT_STMT   \
        TempResult = GET_LogAdd(CM_IMPORT_OPTIONAL_FUNCTION); \
        TempResult = GET_CMUtlMemCpy(CM_IMPORT_OPTIONAL_FUNCTION); \
        if (ERR_OK == importResult ) TempResult = GET_CmpEmiconEmu_is_emu(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileWrite(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileRead(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileClose(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_SysFileOpen(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) TempResult = GET_get_sys_var_area(CM_IMPORT_OPTIONAL_FUNCTION);\
          if (ERR_OK == importResult ) importResult = GET_EventUnregisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventRegisterCallbackFunction(0);\
          if (ERR_OK == importResult ) importResult = GET_EventPost(0);\
          if (ERR_OK == importResult ) importResult = GET_EventClose(0);\
          if (ERR_OK == importResult ) importResult = GET_EventOpen(0);\
          if (ERR_OK == importResult ) importResult = GET_SettgGetStringValue(0);\
          if (ERR_OK == importResult ) importResult = GET_CMUtlSafeStrCpy(0);\
          if (ERR_OK == importResult ) importResult = GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(0);\
           \
        /* To make LINT happy */\
        TempResult = TempResult;\
        if (ERR_OK != importResult) return importResult;\
    }
#endif



#ifndef CMPEMICONSYS_DISABLE_EXTREF
#define EXPORT_EXTREF_STMT \
                  { (RTS_VOID_FCTPTR)syssync, "syssync", 0xDC1119C9, 0x03051114 },\
          { (RTS_VOID_FCTPTR)set_watchdog, "set_watchdog", 0x9CA67B6B, 0x03051114 },\
          { (RTS_VOID_FCTPTR)set_inhibit, "set_inhibit", 0xAFE8BB40, 0x03051114 },\
          { (RTS_VOID_FCTPTR)is_emu, "is_emu", 0x7320DC54, 0x03051114 },\
          { (RTS_VOID_FCTPTR)gpiosetvalue, "gpiosetvalue", 0x6F55F30C, 0x03051114 },\
          { (RTS_VOID_FCTPTR)gpiosetdirection, "gpiosetdirection", 0x30BD8EA7, 0x03051114 },\
          { (RTS_VOID_FCTPTR)gpiogetvalue, "gpiogetvalue", 0xC95BC6EF, 0x03051114 },\
          { (RTS_VOID_FCTPTR)gpioexport, "gpioexport", 0xF49480CA, 0x03051114 },\
          { (RTS_VOID_FCTPTR)getrequesttoreserve, "getrequesttoreserve", 0x1464D92A, 0x03051114 },\
          { (RTS_VOID_FCTPTR)get_size_of_sys_area, "get_size_of_sys_area", 0x60094181, 0x03051114 },\
          { (RTS_VOID_FCTPTR)get_ptr_to_sys_area, "get_ptr_to_sys_area", 0x459659D7, 0x03051114 },\
          { (RTS_VOID_FCTPTR)get_ptr_to_sock_arr, "get_ptr_to_sock_arr", 0x7F4ADBA2, 0x03051114 },\
          { (RTS_VOID_FCTPTR)get_ptr_to_slot0, "get_ptr_to_slot0", 0xE6CB94A0, 0x03051114 },\
          { (RTS_VOID_FCTPTR)get_ptr_to_dpm, "get_ptr_to_dpm", 0x7C8941E2, 0x03051114 },\
          { (RTS_VOID_FCTPTR)clr_inhibit, "clr_inhibit", 0x0D052147, 0x03051114 },\
          
#else
#define EXPORT_EXTREF_STMT
#endif
#ifndef CMPEMICONSYS_DISABLE_EXTREF2
#define EXPORT_EXTREF2_STMT \
                                                
#else
#define EXPORT_EXTREF2_STMT
#endif
#if !defined(CMPEMICONSYS_DISABLE_CMPITF) && !defined(STATIC_LINK) && !defined(CPLUSPLUS) && !defined(CPLUSPLUS_ONLY)
#define EXPORT_CMPITF_STMT \
    {\
        { (RTS_VOID_FCTPTR)CmpEmiconSys_clr_inhibit, "CmpEmiconSys_clr_inhibit", 0, 0 },\
          { (RTS_VOID_FCTPTR)CmpEmiconSys_gpio_set_value, "CmpEmiconSys_gpio_set_value", 0, 0 },\
          { (RTS_VOID_FCTPTR)CmpEmiconSys_gpio_get_value, "CmpEmiconSys_gpio_get_value", 0, 0 },\
          { (RTS_VOID_FCTPTR)CmpEmiconSys_gpio_set_direction, "CmpEmiconSys_gpio_set_direction", 0, 0 },\
          { (RTS_VOID_FCTPTR)CmpEmiconSys_gpio_export, "CmpEmiconSys_gpio_export", 0, 0 },\
                                        \
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#else
#define EXPORT_CMPITF_STMT \
    {\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    }
#endif
#define EXPORT_CPP_STMT


#if defined(STATIC_LINK)
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#else
    #define EXPORT_STMT\
    {\
        RTS_RESULT ExpResult;\
        if (NULL == s_pfCMRegisterAPI)\
            return ERR_NOTINITIALIZED;\
        ExpResult = s_pfCMRegisterAPI(s_ExternalsTable, 0, 1, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
        ExpResult = s_pfCMRegisterAPI(s_ItfTable, 0, 0, COMPONENT_ID);\
        if (ERR_OK != ExpResult)\
            return ExpResult;\
    }
#endif

#define USE_STMT \
    /*lint -save --e{528} --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    static const CMP_EXT_FUNCTION_REF s_ExternalsTable[] =\
    {\
        EXPORT_EXTREF_STMT\
        EXPORT_EXTREF2_STMT\
        { ((RTS_VOID_FCTPTR)(void *)0), "", 0, 0 }\
    };\
    static const CMP_EXT_FUNCTION_REF s_ItfTable[] = EXPORT_CMPITF_STMT; \
    /*lint -restore */  \
    static int CDECL ExportFunctions(void); \
    static int CDECL ImportFunctions(void); \
    static IBase* CDECL CreateInstance(CLASSID cid, RTS_RESULT *pResult); \
    static RTS_RESULT CDECL DeleteInstance(IBase *pIBase); \
    static RTS_UI32 CDECL CmpGetVersion(void); \
    static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2); \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	/*obsolete entry ITF_CMUtils*/      \
	ITF_SysFile     \
	ITF_CmpSettings     \
	ITF_CmpApp     \
	ITF_CmpEmiconEmu     \
	ITF_CmpEmiconMemManager      \
    USE_CmpEmiconMemManager_get_cs3_allocated_mem_size      \
    USE_CMUtlSafeStrCpy      \
    USE_SettgGetStringValue      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventPost      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_get_sys_var_area      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileRead      \
    USE_SysFileWrite      \
    USE_CmpEmiconEmu_is_emu     
#define USEIMPORT_STMT \
    /*lint -save --e{551} */ \
    static volatile PF_REGISTER_API s_pfCMRegisterAPI; \
    static volatile PF_REGISTER_API2 s_pfCMRegisterAPI2; \
    static volatile PF_GET_API s_pfCMGetAPI; \
    static volatile PF_GET_API2 s_pfCMGetAPI2; \
    static volatile PF_REGISTER_CLASS s_pfCMRegisterClass; \
    static volatile PF_CREATEINSTANCE s_pfCMCreateInstance; \
    static volatile PF_CALL_HOOK s_pfCMCallHook; \
    /*lint -restore */  \
    ITF_CmpLog   \
    ITF_CMUtils  \
    USE_CMUtlMemCpy  \
    USE_LogAdd \
	/*obsolete entry ITF_CMUtils*/     \
	ITF_SysFile    \
	ITF_CmpSettings    \
	ITF_CmpApp    \
	ITF_CmpEmiconEmu    \
	ITF_CmpEmiconMemManager     \
    USE_CmpEmiconMemManager_get_cs3_allocated_mem_size      \
    USE_CMUtlSafeStrCpy      \
    USE_SettgGetStringValue      \
    USE_EventOpen      \
    USE_EventClose      \
    USE_EventPost      \
    USE_EventRegisterCallbackFunction      \
    USE_EventUnregisterCallbackFunction      \
    USE_get_sys_var_area      \
    USE_SysFileOpen      \
    USE_SysFileClose      \
    USE_SysFileRead      \
    USE_SysFileWrite      \
    USE_CmpEmiconEmu_is_emu     
#define USEEXTERN_STMT \
    EXT_CMUtlMemCpy  \
    EXT_LogAdd \
	/*obsolete entry EXTITF_CMUtils*/     \
	EXTITF_SysFile    \
	EXTITF_CmpSettings    \
	EXTITF_CmpApp    \
	EXTITF_CmpEmiconEmu    \
	EXTITF_CmpEmiconMemManager     \
    EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size  \
    EXT_CMUtlSafeStrCpy  \
    EXT_SettgGetStringValue  \
    EXT_EventOpen  \
    EXT_EventClose  \
    EXT_EventPost  \
    EXT_EventRegisterCallbackFunction  \
    EXT_EventUnregisterCallbackFunction  \
    EXT_get_sys_var_area  \
    EXT_SysFileOpen  \
    EXT_SysFileClose  \
    EXT_SysFileRead  \
    EXT_SysFileWrite  \
    EXT_CmpEmiconEmu_is_emu 
#ifndef COMPONENT_NAME
    #error COMPONENT_NAME is not defined. This prevents the component from being linked statically. Use SET_COMPONENT_NAME(<name_of_your_component>) to set the name of the component in your .m4 component description.
#endif




#if defined(STATIC_LINK) || defined(MIXED_LINK) || defined(DYNAMIC_LINK) || defined(CPLUSPLUS_STATIC_LINK)
    #define ComponentEntry CmpEmiconSys__Entry
#endif


#ifdef CPLUSPLUS

class CCmpEmiconSys : public IEmiconSys_3 
{
    public:
        CCmpEmiconSys() : hCmpEmiconSys(RTS_INVALID_HANDLE), iRefCount(0)
        {
        }
        virtual ~CCmpEmiconSys()
        {
        }
        virtual unsigned long AddRef(IBase *pIBase = NULL)
        {
            iRefCount++;
            return iRefCount;
        }
        virtual unsigned long Release(IBase *pIBase = NULL)
        {
            iRefCount--;
            if (iRefCount == 0)
            {
                delete this;
                return 0;
            }
            return iRefCount;
        }

        
        virtual void* QueryInterface(IBase *pIBase, ITFID iid, RTS_RESULT *pResult)
        {
            void *pItf;
            if (iid == ITFID_IBase)
                pItf = dynamic_cast<IBase *>((IEmiconSys_3 *)this);            
            else if (iid == ITFID_IEmiconSys_3)
                pItf = dynamic_cast<IEmiconSys_3 *>(this); 
            else
            {
                if (pResult != NULL)
                    *pResult = ERR_NOTIMPLEMENTED;
                return NULL;
            }
            if (pResult != (RTS_RESULT *)1)
                (reinterpret_cast<IBase *>(pItf))->AddRef();
            if (pResult != NULL && pResult != (RTS_RESULT *)1)
                *pResult = ERR_OK;
            return pItf;
        }
        virtual bool CDECL ICmpEmiconSys_gpio_export(uint8_t n);
        virtual bool CDECL ICmpEmiconSys_gpio_set_direction(uint8_t n, char *direction);
        virtual bool CDECL ICmpEmiconSys_gpio_get_value(uint8_t n);
        virtual bool CDECL ICmpEmiconSys_gpio_set_value(uint8_t n, uint8_t val);
        virtual void CDECL ICmpEmiconSys_clr_inhibit(void);

    public:
        RTS_HANDLE hCmpEmiconSys;
        int iRefCount;
};

#endif /*CPLUSPLUS*/
#ifdef RTS_COMPACT_MICRO
/* CmpEmiconSys Declarations for uRTS */
/* This header is included only to have the CMP_EXT_FUNCTION_REF type definition. */
/* In final version this type could be moved to CmpItf.h, if we will use */
/* the same structure for representing an export entry. */
#include <_OptionalIncludes/Profiles/uRTS/CMMicro.h>

/* Undefine these macros if they were previously defined */

#ifdef USE_HOOK_FUNCTION
#undef USE_HOOK_FUNCTION
#endif

#ifdef USE_CMEXPORTFUNCTIONS
#undef USE_CMEXPORTFUNCTIONS
#endif

#ifdef USE_EXPORT_EXTREF
#undef USE_EXPORT_EXTREF
#endif

#ifdef USE_EXPORT_CMPITF
#undef USE_EXPORT_CMPITF
#endif

#ifdef USE_ENTRY_LINKAGE
#undef USE_ENTRY_LINKAGE
#endif

#ifdef IMPLEMENT_EXPORT_FUNCTIONS
#undef IMPLEMENT_EXPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_IMPORT_FUNCTIONS
#undef IMPLEMENT_IMPORT_FUNCTIONS
#endif

#ifdef IMPLEMENT_GETVERSION_FUNCTIONS
#undef IMPLEMENT_GETVERSION_FUNCTIONS
#endif

#ifdef EXPORT_STMT
#undef EXPORT_STMT
#endif

#ifdef USEEXTERN_STMT
#undef USEEXTERN_STMT
#endif

#ifdef USE_STMT
#undef USE_STMT
#endif

#ifdef USEIMPORT_STMT
#undef USEIMPORT_STMT
#endif

/* This wrapper is only required in uRTS */
#define USE_HOOK_FUNCTION	RTS_RESULT CmpEmiconSys_HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2)\
{\
	return HookFunction(ulHook, ulParam1, ulParam2);\
}

/******************************************************************************/
/* No s_pfCMExportFunctions in uRTS */
#define USE_CMEXPORTFUNCTIONS

/* Exports table to IEC */
#define USE_EXPORT_EXTREF const CMP_EXT_FUNCTION_REF CmpEmiconSys_ExternalsTable[] = \
	{\
		EXPORT_EXTREF_STMT\
		EXPORT_EXTREF2_STMT\
		{ ((RTS_VOID_FCTPTR)(void *)0), "", 0 }\
	};

/* No component interface exports in uRTS */
#define USE_EXPORT_CMPITF

/* No dynamic linkage in uRTS */
#define USE_ENTRY_LINKAGE

/* No ExportFunctions() routine in uRTS */
#define IMPLEMENT_EXPORT_FUNCTIONS

/* No ImportFunctions() routine in uRTS */
#define IMPLEMENT_IMPORT_FUNCTIONS

/* No CmpGetVersion() routine in uRTS */
#define IMPLEMENT_GETVERSION_FUNCTIONS

/* No usage of externals from the component secondary C-modules in uRTS */
#define USEEXTERN_STMT

/* No need for export calling to the Component Manager in uRTS */
#define EXPORT_STMT

/* No need for importing from secondary C-modules */
#define USEIMPORT_STMT

/* Instantiation macro for a root component C-module */
#define USE_STMT\
	static RTS_RESULT CDECL HookFunction(RTS_UI32 ulHook, RTS_UINTPTR ulParam1, RTS_UINTPTR ulParam2);\
		USE_EXPORT_EXTREF;\
		USE_EXPORT_CMPITF;\
		USE_HOOK_FUNCTION;\
		USE_CMEXPORTFUNCTIONS;\


/******************************************************************************/
#endif

#endif /*WIN32_RESOURCES*/
#endif /*_DEP_H_*/
