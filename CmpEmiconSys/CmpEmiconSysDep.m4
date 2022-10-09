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
SET_COMPONENT_NAME(`CmpEmiconSys')
COMPONENT_SOURCES(`CmpEmiconSys.c')

COMPONENT_VERSION(`0x03051114')

/* NOTE: REPLACE 0x0001 BY YOUR VENDORID */
COMPONENT_VENDORID(`0x0001')				

#define CMPID_CmpEmiconSys		0x2100								/* NOTE: START HERE WITH YOUR COMPONENTIDS (see CmpItf.h */
#define CLASSID_CCmpEmiconSys	ADDVENDORID(CMP_VENDORID, 0x2100)	/* NOTE: START HERE WITH YOUR CLASSIDS (see CmpItf.h */
#define ITFID_ICmpEmiconSys		ADDVENDORID(CMP_VENDORID, 0x2100)	/* NOTE: START HERE WITH YOUR INTERFACEIDS (see CmpItf.h */

CATEGORY(`Templates')

USE_ITF(`CMUtilsItf.m4')
USE_ITF(`SysFileItf.m4')
USE_ITF(`CmpSettingsItf.m4')
USE_ITF(`CmpAppItf.m4')
USE_ITF(`CmpEmiconEmuItf.m4')
USE_ITF(`CmpEmiconMemManagerItf.m4')

IMPLEMENT_ITF(`CmpEmiconSysItf.m4')

REQUIRED_IMPORTS(
CmpEmiconMemManager_get_cs3_allocated_mem_size,
CMUtlSafeStrCpy,
SettgGetStringValue,
EventOpen,
EventClose,
EventPost,
EventRegisterCallbackFunction,
EventUnregisterCallbackFunction)

OPTIONAL_IMPORTS(
get_sys_var_area,
SysFileOpen,
SysFileClose,
SysFileRead,
SysFileWrite,
CmpEmiconEmu_is_emu)
