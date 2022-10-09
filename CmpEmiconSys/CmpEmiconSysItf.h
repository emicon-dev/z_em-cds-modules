 /**
 * <interfacename>EmiconSys_3</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */


	
	
#ifndef _EMICONSYS_3ITF_H_
#define _EMICONSYS_3ITF_H_

#include "CmpStd.h"

 

 




/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used.  */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 * clr_inhibit
 * </description>
 * <element name="clr_inhibit" type=OUT></element>
*/
typedef struct tagclr_inhibit_struct
{
	RTS_IEC_BOOL clr_inhibit;
} clr_inhibit_struct;

void CDECL CDECL_EXT clr_inhibit(clr_inhibit_struct *p);
typedef void (CDECL CDECL_EXT* PFCLR_INHIBIT_IEC) (clr_inhibit_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CLR_INHIBIT_NOTIMPLEMENTED)
	#define USE_clr_inhibit
	#define EXT_clr_inhibit
	#define GET_clr_inhibit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_clr_inhibit(p0) 
	#define CHK_clr_inhibit  FALSE
	#define EXP_clr_inhibit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_clr_inhibit
	#define EXT_clr_inhibit
	#define GET_clr_inhibit(fl)  CAL_CMGETAPI( "clr_inhibit" ) 
	#define CAL_clr_inhibit  clr_inhibit
	#define CHK_clr_inhibit  TRUE
	#define EXP_clr_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_inhibit", (RTS_UINTPTR)clr_inhibit, 1, 0x0D052147, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_clr_inhibit
	#define EXT_clr_inhibit
	#define GET_clr_inhibit(fl)  CAL_CMGETAPI( "clr_inhibit" ) 
	#define CAL_clr_inhibit  clr_inhibit
	#define CHK_clr_inhibit  TRUE
	#define EXP_clr_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_inhibit", (RTS_UINTPTR)clr_inhibit, 1, 0x0D052147, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3clr_inhibit
	#define EXT_EmiconSys_3clr_inhibit
	#define GET_EmiconSys_3clr_inhibit  ERR_OK
	#define CAL_EmiconSys_3clr_inhibit  clr_inhibit
	#define CHK_EmiconSys_3clr_inhibit  TRUE
	#define EXP_EmiconSys_3clr_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_inhibit", (RTS_UINTPTR)clr_inhibit, 1, 0x0D052147, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_clr_inhibit
	#define EXT_clr_inhibit
	#define GET_clr_inhibit(fl)  CAL_CMGETAPI( "clr_inhibit" ) 
	#define CAL_clr_inhibit  clr_inhibit
	#define CHK_clr_inhibit  TRUE
	#define EXP_clr_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_inhibit", (RTS_UINTPTR)clr_inhibit, 1, 0x0D052147, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_clr_inhibit  PFCLR_INHIBIT_IEC pfclr_inhibit;
	#define EXT_clr_inhibit  extern PFCLR_INHIBIT_IEC pfclr_inhibit;
	#define GET_clr_inhibit(fl)  s_pfCMGetAPI2( "clr_inhibit", (RTS_VOID_FCTPTR *)&pfclr_inhibit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x0D052147, 0x03051114)
	#define CAL_clr_inhibit  pfclr_inhibit
	#define CHK_clr_inhibit  (pfclr_inhibit != NULL)
	#define EXP_clr_inhibit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"clr_inhibit", (RTS_UINTPTR)clr_inhibit, 1, 0x0D052147, 0x03051114) 
#endif


/**
 * <description>
 * get_ptr_to_dpm
 * </description>
 * <element name="Get_ptr_to_DPM" type=OUT></element>
*/
typedef struct tagget_ptr_to_dpm_struct
{
	RTS_IEC_WORD *Get_ptr_to_DPM;
} get_ptr_to_dpm_struct;

void CDECL CDECL_EXT get_ptr_to_dpm(get_ptr_to_dpm_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_DPM_IEC) (get_ptr_to_dpm_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GET_PTR_TO_DPM_NOTIMPLEMENTED)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_dpm(p0) 
	#define CHK_get_ptr_to_dpm  FALSE
	#define EXP_get_ptr_to_dpm  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3get_ptr_to_dpm
	#define EXT_EmiconSys_3get_ptr_to_dpm
	#define GET_EmiconSys_3get_ptr_to_dpm  ERR_OK
	#define CAL_EmiconSys_3get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_EmiconSys_3get_ptr_to_dpm  TRUE
	#define EXP_EmiconSys_3get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_dpm
	#define EXT_get_ptr_to_dpm
	#define GET_get_ptr_to_dpm(fl)  CAL_CMGETAPI( "get_ptr_to_dpm" ) 
	#define CAL_get_ptr_to_dpm  get_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  TRUE
	#define EXP_get_ptr_to_dpm  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_dpm  PFGET_PTR_TO_DPM_IEC pfget_ptr_to_dpm;
	#define EXT_get_ptr_to_dpm  extern PFGET_PTR_TO_DPM_IEC pfget_ptr_to_dpm;
	#define GET_get_ptr_to_dpm(fl)  s_pfCMGetAPI2( "get_ptr_to_dpm", (RTS_VOID_FCTPTR *)&pfget_ptr_to_dpm, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7C8941E2, 0x03051114)
	#define CAL_get_ptr_to_dpm  pfget_ptr_to_dpm
	#define CHK_get_ptr_to_dpm  (pfget_ptr_to_dpm != NULL)
	#define EXP_get_ptr_to_dpm   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_dpm", (RTS_UINTPTR)get_ptr_to_dpm, 1, 0x7C8941E2, 0x03051114) 
#endif


/**
 * <description>
 * get_ptr_to_slot0
 * </description>
 * <element name="Get_ptr_to_slot0" type=OUT></element>
*/
typedef struct tagget_ptr_to_slot0_struct
{
	RTS_IEC_BYTE *Get_ptr_to_slot0;
} get_ptr_to_slot0_struct;

void CDECL CDECL_EXT get_ptr_to_slot0(get_ptr_to_slot0_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_SLOT0_IEC) (get_ptr_to_slot0_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GET_PTR_TO_SLOT0_NOTIMPLEMENTED)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_slot0(p0) 
	#define CHK_get_ptr_to_slot0  FALSE
	#define EXP_get_ptr_to_slot0  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3get_ptr_to_slot0
	#define EXT_EmiconSys_3get_ptr_to_slot0
	#define GET_EmiconSys_3get_ptr_to_slot0  ERR_OK
	#define CAL_EmiconSys_3get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_EmiconSys_3get_ptr_to_slot0  TRUE
	#define EXP_EmiconSys_3get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_slot0
	#define EXT_get_ptr_to_slot0
	#define GET_get_ptr_to_slot0(fl)  CAL_CMGETAPI( "get_ptr_to_slot0" ) 
	#define CAL_get_ptr_to_slot0  get_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  TRUE
	#define EXP_get_ptr_to_slot0  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_slot0  PFGET_PTR_TO_SLOT0_IEC pfget_ptr_to_slot0;
	#define EXT_get_ptr_to_slot0  extern PFGET_PTR_TO_SLOT0_IEC pfget_ptr_to_slot0;
	#define GET_get_ptr_to_slot0(fl)  s_pfCMGetAPI2( "get_ptr_to_slot0", (RTS_VOID_FCTPTR *)&pfget_ptr_to_slot0, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xE6CB94A0, 0x03051114)
	#define CAL_get_ptr_to_slot0  pfget_ptr_to_slot0
	#define CHK_get_ptr_to_slot0  (pfget_ptr_to_slot0 != NULL)
	#define EXP_get_ptr_to_slot0   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_slot0", (RTS_UINTPTR)get_ptr_to_slot0, 1, 0xE6CB94A0, 0x03051114) 
#endif


/**
 * <description>
 * get_ptr_to_sock_arr
 * </description>
 * <element name="Get_ptr_to_sock_arr" type=OUT></element>
*/
typedef struct tagget_ptr_to_sock_arr_struct
{
	RTS_IEC_UDINT *Get_ptr_to_sock_arr;
} get_ptr_to_sock_arr_struct;

void CDECL CDECL_EXT get_ptr_to_sock_arr(get_ptr_to_sock_arr_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_SOCK_ARR_IEC) (get_ptr_to_sock_arr_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GET_PTR_TO_SOCK_ARR_NOTIMPLEMENTED)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_sock_arr(p0) 
	#define CHK_get_ptr_to_sock_arr  FALSE
	#define EXP_get_ptr_to_sock_arr  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3get_ptr_to_sock_arr
	#define EXT_EmiconSys_3get_ptr_to_sock_arr
	#define GET_EmiconSys_3get_ptr_to_sock_arr  ERR_OK
	#define CAL_EmiconSys_3get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_EmiconSys_3get_ptr_to_sock_arr  TRUE
	#define EXP_EmiconSys_3get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_sock_arr
	#define EXT_get_ptr_to_sock_arr
	#define GET_get_ptr_to_sock_arr(fl)  CAL_CMGETAPI( "get_ptr_to_sock_arr" ) 
	#define CAL_get_ptr_to_sock_arr  get_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  TRUE
	#define EXP_get_ptr_to_sock_arr  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_sock_arr  PFGET_PTR_TO_SOCK_ARR_IEC pfget_ptr_to_sock_arr;
	#define EXT_get_ptr_to_sock_arr  extern PFGET_PTR_TO_SOCK_ARR_IEC pfget_ptr_to_sock_arr;
	#define GET_get_ptr_to_sock_arr(fl)  s_pfCMGetAPI2( "get_ptr_to_sock_arr", (RTS_VOID_FCTPTR *)&pfget_ptr_to_sock_arr, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7F4ADBA2, 0x03051114)
	#define CAL_get_ptr_to_sock_arr  pfget_ptr_to_sock_arr
	#define CHK_get_ptr_to_sock_arr  (pfget_ptr_to_sock_arr != NULL)
	#define EXP_get_ptr_to_sock_arr   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sock_arr", (RTS_UINTPTR)get_ptr_to_sock_arr, 1, 0x7F4ADBA2, 0x03051114) 
#endif


/**
 * <description>
 * get_ptr_to_sys_area
 * </description>
 * <element name="get_ptr_to_sys_area" type=OUT></element>
*/
typedef struct tagget_ptr_to_sys_area_struct
{
	RTS_IEC_BYTE *get_ptr_to_sys_area;
} get_ptr_to_sys_area_struct;

void CDECL CDECL_EXT get_ptr_to_sys_area(get_ptr_to_sys_area_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_PTR_TO_SYS_AREA_IEC) (get_ptr_to_sys_area_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GET_PTR_TO_SYS_AREA_NOTIMPLEMENTED)
	#define USE_get_ptr_to_sys_area
	#define EXT_get_ptr_to_sys_area
	#define GET_get_ptr_to_sys_area(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_ptr_to_sys_area(p0) 
	#define CHK_get_ptr_to_sys_area  FALSE
	#define EXP_get_ptr_to_sys_area  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_ptr_to_sys_area
	#define EXT_get_ptr_to_sys_area
	#define GET_get_ptr_to_sys_area(fl)  CAL_CMGETAPI( "get_ptr_to_sys_area" ) 
	#define CAL_get_ptr_to_sys_area  get_ptr_to_sys_area
	#define CHK_get_ptr_to_sys_area  TRUE
	#define EXP_get_ptr_to_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sys_area", (RTS_UINTPTR)get_ptr_to_sys_area, 1, 0x459659D7, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_get_ptr_to_sys_area
	#define EXT_get_ptr_to_sys_area
	#define GET_get_ptr_to_sys_area(fl)  CAL_CMGETAPI( "get_ptr_to_sys_area" ) 
	#define CAL_get_ptr_to_sys_area  get_ptr_to_sys_area
	#define CHK_get_ptr_to_sys_area  TRUE
	#define EXP_get_ptr_to_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sys_area", (RTS_UINTPTR)get_ptr_to_sys_area, 1, 0x459659D7, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3get_ptr_to_sys_area
	#define EXT_EmiconSys_3get_ptr_to_sys_area
	#define GET_EmiconSys_3get_ptr_to_sys_area  ERR_OK
	#define CAL_EmiconSys_3get_ptr_to_sys_area  get_ptr_to_sys_area
	#define CHK_EmiconSys_3get_ptr_to_sys_area  TRUE
	#define EXP_EmiconSys_3get_ptr_to_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sys_area", (RTS_UINTPTR)get_ptr_to_sys_area, 1, 0x459659D7, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_get_ptr_to_sys_area
	#define EXT_get_ptr_to_sys_area
	#define GET_get_ptr_to_sys_area(fl)  CAL_CMGETAPI( "get_ptr_to_sys_area" ) 
	#define CAL_get_ptr_to_sys_area  get_ptr_to_sys_area
	#define CHK_get_ptr_to_sys_area  TRUE
	#define EXP_get_ptr_to_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sys_area", (RTS_UINTPTR)get_ptr_to_sys_area, 1, 0x459659D7, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_get_ptr_to_sys_area  PFGET_PTR_TO_SYS_AREA_IEC pfget_ptr_to_sys_area;
	#define EXT_get_ptr_to_sys_area  extern PFGET_PTR_TO_SYS_AREA_IEC pfget_ptr_to_sys_area;
	#define GET_get_ptr_to_sys_area(fl)  s_pfCMGetAPI2( "get_ptr_to_sys_area", (RTS_VOID_FCTPTR *)&pfget_ptr_to_sys_area, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x459659D7, 0x03051114)
	#define CAL_get_ptr_to_sys_area  pfget_ptr_to_sys_area
	#define CHK_get_ptr_to_sys_area  (pfget_ptr_to_sys_area != NULL)
	#define EXP_get_ptr_to_sys_area   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_ptr_to_sys_area", (RTS_UINTPTR)get_ptr_to_sys_area, 1, 0x459659D7, 0x03051114) 
#endif


/**
 * <description>
 * get_size_of_sys_area
 * </description>
 * <element name="get_size_of_sys_area" type=OUT></element>
*/
typedef struct tagget_size_of_sys_area_struct
{
	RTS_IEC_UDINT get_size_of_sys_area;
} get_size_of_sys_area_struct;

void CDECL CDECL_EXT get_size_of_sys_area(get_size_of_sys_area_struct *p);
typedef void (CDECL CDECL_EXT* PFGET_SIZE_OF_SYS_AREA_IEC) (get_size_of_sys_area_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GET_SIZE_OF_SYS_AREA_NOTIMPLEMENTED)
	#define USE_get_size_of_sys_area
	#define EXT_get_size_of_sys_area
	#define GET_get_size_of_sys_area(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_size_of_sys_area(p0) 
	#define CHK_get_size_of_sys_area  FALSE
	#define EXP_get_size_of_sys_area  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_size_of_sys_area
	#define EXT_get_size_of_sys_area
	#define GET_get_size_of_sys_area(fl)  CAL_CMGETAPI( "get_size_of_sys_area" ) 
	#define CAL_get_size_of_sys_area  get_size_of_sys_area
	#define CHK_get_size_of_sys_area  TRUE
	#define EXP_get_size_of_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_size_of_sys_area", (RTS_UINTPTR)get_size_of_sys_area, 1, 0x60094181, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_get_size_of_sys_area
	#define EXT_get_size_of_sys_area
	#define GET_get_size_of_sys_area(fl)  CAL_CMGETAPI( "get_size_of_sys_area" ) 
	#define CAL_get_size_of_sys_area  get_size_of_sys_area
	#define CHK_get_size_of_sys_area  TRUE
	#define EXP_get_size_of_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_size_of_sys_area", (RTS_UINTPTR)get_size_of_sys_area, 1, 0x60094181, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3get_size_of_sys_area
	#define EXT_EmiconSys_3get_size_of_sys_area
	#define GET_EmiconSys_3get_size_of_sys_area  ERR_OK
	#define CAL_EmiconSys_3get_size_of_sys_area  get_size_of_sys_area
	#define CHK_EmiconSys_3get_size_of_sys_area  TRUE
	#define EXP_EmiconSys_3get_size_of_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_size_of_sys_area", (RTS_UINTPTR)get_size_of_sys_area, 1, 0x60094181, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_get_size_of_sys_area
	#define EXT_get_size_of_sys_area
	#define GET_get_size_of_sys_area(fl)  CAL_CMGETAPI( "get_size_of_sys_area" ) 
	#define CAL_get_size_of_sys_area  get_size_of_sys_area
	#define CHK_get_size_of_sys_area  TRUE
	#define EXP_get_size_of_sys_area  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_size_of_sys_area", (RTS_UINTPTR)get_size_of_sys_area, 1, 0x60094181, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_get_size_of_sys_area  PFGET_SIZE_OF_SYS_AREA_IEC pfget_size_of_sys_area;
	#define EXT_get_size_of_sys_area  extern PFGET_SIZE_OF_SYS_AREA_IEC pfget_size_of_sys_area;
	#define GET_get_size_of_sys_area(fl)  s_pfCMGetAPI2( "get_size_of_sys_area", (RTS_VOID_FCTPTR *)&pfget_size_of_sys_area, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x60094181, 0x03051114)
	#define CAL_get_size_of_sys_area  pfget_size_of_sys_area
	#define CHK_get_size_of_sys_area  (pfget_size_of_sys_area != NULL)
	#define EXP_get_size_of_sys_area   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"get_size_of_sys_area", (RTS_UINTPTR)get_size_of_sys_area, 1, 0x60094181, 0x03051114) 
#endif


/**
 * <description>
 * getrequesttoreserve
 * </description>
 * <element name="getRequestToReserve" type=OUT></element>
*/
typedef struct taggetrequesttoreserve_struct
{
	RTS_IEC_INT getRequestToReserve;
} getrequesttoreserve_struct;

void CDECL CDECL_EXT getrequesttoreserve(getrequesttoreserve_struct *p);
typedef void (CDECL CDECL_EXT* PFGETREQUESTTORESERVE_IEC) (getrequesttoreserve_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GETREQUESTTORESERVE_NOTIMPLEMENTED)
	#define USE_getrequesttoreserve
	#define EXT_getrequesttoreserve
	#define GET_getrequesttoreserve(fl)  ERR_NOTIMPLEMENTED
	#define CAL_getrequesttoreserve(p0) 
	#define CHK_getrequesttoreserve  FALSE
	#define EXP_getrequesttoreserve  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_getrequesttoreserve
	#define EXT_getrequesttoreserve
	#define GET_getrequesttoreserve(fl)  CAL_CMGETAPI( "getrequesttoreserve" ) 
	#define CAL_getrequesttoreserve  getrequesttoreserve
	#define CHK_getrequesttoreserve  TRUE
	#define EXP_getrequesttoreserve  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getrequesttoreserve", (RTS_UINTPTR)getrequesttoreserve, 1, 0x1464D92A, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_getrequesttoreserve
	#define EXT_getrequesttoreserve
	#define GET_getrequesttoreserve(fl)  CAL_CMGETAPI( "getrequesttoreserve" ) 
	#define CAL_getrequesttoreserve  getrequesttoreserve
	#define CHK_getrequesttoreserve  TRUE
	#define EXP_getrequesttoreserve  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getrequesttoreserve", (RTS_UINTPTR)getrequesttoreserve, 1, 0x1464D92A, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3getrequesttoreserve
	#define EXT_EmiconSys_3getrequesttoreserve
	#define GET_EmiconSys_3getrequesttoreserve  ERR_OK
	#define CAL_EmiconSys_3getrequesttoreserve  getrequesttoreserve
	#define CHK_EmiconSys_3getrequesttoreserve  TRUE
	#define EXP_EmiconSys_3getrequesttoreserve  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getrequesttoreserve", (RTS_UINTPTR)getrequesttoreserve, 1, 0x1464D92A, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_getrequesttoreserve
	#define EXT_getrequesttoreserve
	#define GET_getrequesttoreserve(fl)  CAL_CMGETAPI( "getrequesttoreserve" ) 
	#define CAL_getrequesttoreserve  getrequesttoreserve
	#define CHK_getrequesttoreserve  TRUE
	#define EXP_getrequesttoreserve  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getrequesttoreserve", (RTS_UINTPTR)getrequesttoreserve, 1, 0x1464D92A, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_getrequesttoreserve  PFGETREQUESTTORESERVE_IEC pfgetrequesttoreserve;
	#define EXT_getrequesttoreserve  extern PFGETREQUESTTORESERVE_IEC pfgetrequesttoreserve;
	#define GET_getrequesttoreserve(fl)  s_pfCMGetAPI2( "getrequesttoreserve", (RTS_VOID_FCTPTR *)&pfgetrequesttoreserve, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x1464D92A, 0x03051114)
	#define CAL_getrequesttoreserve  pfgetrequesttoreserve
	#define CHK_getrequesttoreserve  (pfgetrequesttoreserve != NULL)
	#define EXP_getrequesttoreserve   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"getrequesttoreserve", (RTS_UINTPTR)getrequesttoreserve, 1, 0x1464D92A, 0x03051114) 
#endif


/**
 * <description>
 * gpioexport
 * </description>
 * <element name="gpioExport" type=OUT></element>
 * <element name="n" type=IN></element>
*/
typedef struct taggpioexport_struct
{
	RTS_IEC_BYTE n;
	RTS_IEC_BOOL gpioExport;
} gpioexport_struct;

void CDECL CDECL_EXT gpioexport(gpioexport_struct *p);
typedef void (CDECL CDECL_EXT* PFGPIOEXPORT_IEC) (gpioexport_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GPIOEXPORT_NOTIMPLEMENTED)
	#define USE_gpioexport
	#define EXT_gpioexport
	#define GET_gpioexport(fl)  ERR_NOTIMPLEMENTED
	#define CAL_gpioexport(p0) 
	#define CHK_gpioexport  FALSE
	#define EXP_gpioexport  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_gpioexport
	#define EXT_gpioexport
	#define GET_gpioexport(fl)  CAL_CMGETAPI( "gpioexport" ) 
	#define CAL_gpioexport  gpioexport
	#define CHK_gpioexport  TRUE
	#define EXP_gpioexport  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpioexport", (RTS_UINTPTR)gpioexport, 1, 0xF49480CA, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_gpioexport
	#define EXT_gpioexport
	#define GET_gpioexport(fl)  CAL_CMGETAPI( "gpioexport" ) 
	#define CAL_gpioexport  gpioexport
	#define CHK_gpioexport  TRUE
	#define EXP_gpioexport  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpioexport", (RTS_UINTPTR)gpioexport, 1, 0xF49480CA, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3gpioexport
	#define EXT_EmiconSys_3gpioexport
	#define GET_EmiconSys_3gpioexport  ERR_OK
	#define CAL_EmiconSys_3gpioexport  gpioexport
	#define CHK_EmiconSys_3gpioexport  TRUE
	#define EXP_EmiconSys_3gpioexport  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpioexport", (RTS_UINTPTR)gpioexport, 1, 0xF49480CA, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_gpioexport
	#define EXT_gpioexport
	#define GET_gpioexport(fl)  CAL_CMGETAPI( "gpioexport" ) 
	#define CAL_gpioexport  gpioexport
	#define CHK_gpioexport  TRUE
	#define EXP_gpioexport  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpioexport", (RTS_UINTPTR)gpioexport, 1, 0xF49480CA, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_gpioexport  PFGPIOEXPORT_IEC pfgpioexport;
	#define EXT_gpioexport  extern PFGPIOEXPORT_IEC pfgpioexport;
	#define GET_gpioexport(fl)  s_pfCMGetAPI2( "gpioexport", (RTS_VOID_FCTPTR *)&pfgpioexport, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xF49480CA, 0x03051114)
	#define CAL_gpioexport  pfgpioexport
	#define CHK_gpioexport  (pfgpioexport != NULL)
	#define EXP_gpioexport   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpioexport", (RTS_UINTPTR)gpioexport, 1, 0xF49480CA, 0x03051114) 
#endif


/**
 * <description>
 * gpiogetvalue
 * </description>
 * <element name="gpioGetValue" type=OUT></element>
 * <element name="n" type=IN></element>
*/
typedef struct taggpiogetvalue_struct
{
	RTS_IEC_BYTE n;
	RTS_IEC_BOOL gpioGetValue;
} gpiogetvalue_struct;

void CDECL CDECL_EXT gpiogetvalue(gpiogetvalue_struct *p);
typedef void (CDECL CDECL_EXT* PFGPIOGETVALUE_IEC) (gpiogetvalue_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GPIOGETVALUE_NOTIMPLEMENTED)
	#define USE_gpiogetvalue
	#define EXT_gpiogetvalue
	#define GET_gpiogetvalue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_gpiogetvalue(p0) 
	#define CHK_gpiogetvalue  FALSE
	#define EXP_gpiogetvalue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_gpiogetvalue
	#define EXT_gpiogetvalue
	#define GET_gpiogetvalue(fl)  CAL_CMGETAPI( "gpiogetvalue" ) 
	#define CAL_gpiogetvalue  gpiogetvalue
	#define CHK_gpiogetvalue  TRUE
	#define EXP_gpiogetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiogetvalue", (RTS_UINTPTR)gpiogetvalue, 1, 0xC95BC6EF, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_gpiogetvalue
	#define EXT_gpiogetvalue
	#define GET_gpiogetvalue(fl)  CAL_CMGETAPI( "gpiogetvalue" ) 
	#define CAL_gpiogetvalue  gpiogetvalue
	#define CHK_gpiogetvalue  TRUE
	#define EXP_gpiogetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiogetvalue", (RTS_UINTPTR)gpiogetvalue, 1, 0xC95BC6EF, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3gpiogetvalue
	#define EXT_EmiconSys_3gpiogetvalue
	#define GET_EmiconSys_3gpiogetvalue  ERR_OK
	#define CAL_EmiconSys_3gpiogetvalue  gpiogetvalue
	#define CHK_EmiconSys_3gpiogetvalue  TRUE
	#define EXP_EmiconSys_3gpiogetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiogetvalue", (RTS_UINTPTR)gpiogetvalue, 1, 0xC95BC6EF, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_gpiogetvalue
	#define EXT_gpiogetvalue
	#define GET_gpiogetvalue(fl)  CAL_CMGETAPI( "gpiogetvalue" ) 
	#define CAL_gpiogetvalue  gpiogetvalue
	#define CHK_gpiogetvalue  TRUE
	#define EXP_gpiogetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiogetvalue", (RTS_UINTPTR)gpiogetvalue, 1, 0xC95BC6EF, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_gpiogetvalue  PFGPIOGETVALUE_IEC pfgpiogetvalue;
	#define EXT_gpiogetvalue  extern PFGPIOGETVALUE_IEC pfgpiogetvalue;
	#define GET_gpiogetvalue(fl)  s_pfCMGetAPI2( "gpiogetvalue", (RTS_VOID_FCTPTR *)&pfgpiogetvalue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xC95BC6EF, 0x03051114)
	#define CAL_gpiogetvalue  pfgpiogetvalue
	#define CHK_gpiogetvalue  (pfgpiogetvalue != NULL)
	#define EXP_gpiogetvalue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiogetvalue", (RTS_UINTPTR)gpiogetvalue, 1, 0xC95BC6EF, 0x03051114) 
#endif


/**
 * <description>
 * gpiosetdirection
 * </description>
 * <element name="gpioSetDirection" type=OUT></element>
 * <element name="n" type=IN></element>
 * <element name="direction" type=IN>FALSE (0) - output, TRUE (1) - input;</element>
*/
typedef struct taggpiosetdirection_struct
{
	RTS_IEC_BYTE n;
	RTS_IEC_BOOL direction;
	RTS_IEC_BOOL gpioSetDirection;
} gpiosetdirection_struct;

void CDECL CDECL_EXT gpiosetdirection(gpiosetdirection_struct *p);
typedef void (CDECL CDECL_EXT* PFGPIOSETDIRECTION_IEC) (gpiosetdirection_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GPIOSETDIRECTION_NOTIMPLEMENTED)
	#define USE_gpiosetdirection
	#define EXT_gpiosetdirection
	#define GET_gpiosetdirection(fl)  ERR_NOTIMPLEMENTED
	#define CAL_gpiosetdirection(p0) 
	#define CHK_gpiosetdirection  FALSE
	#define EXP_gpiosetdirection  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_gpiosetdirection
	#define EXT_gpiosetdirection
	#define GET_gpiosetdirection(fl)  CAL_CMGETAPI( "gpiosetdirection" ) 
	#define CAL_gpiosetdirection  gpiosetdirection
	#define CHK_gpiosetdirection  TRUE
	#define EXP_gpiosetdirection  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetdirection", (RTS_UINTPTR)gpiosetdirection, 1, 0x30BD8EA7, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_gpiosetdirection
	#define EXT_gpiosetdirection
	#define GET_gpiosetdirection(fl)  CAL_CMGETAPI( "gpiosetdirection" ) 
	#define CAL_gpiosetdirection  gpiosetdirection
	#define CHK_gpiosetdirection  TRUE
	#define EXP_gpiosetdirection  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetdirection", (RTS_UINTPTR)gpiosetdirection, 1, 0x30BD8EA7, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3gpiosetdirection
	#define EXT_EmiconSys_3gpiosetdirection
	#define GET_EmiconSys_3gpiosetdirection  ERR_OK
	#define CAL_EmiconSys_3gpiosetdirection  gpiosetdirection
	#define CHK_EmiconSys_3gpiosetdirection  TRUE
	#define EXP_EmiconSys_3gpiosetdirection  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetdirection", (RTS_UINTPTR)gpiosetdirection, 1, 0x30BD8EA7, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_gpiosetdirection
	#define EXT_gpiosetdirection
	#define GET_gpiosetdirection(fl)  CAL_CMGETAPI( "gpiosetdirection" ) 
	#define CAL_gpiosetdirection  gpiosetdirection
	#define CHK_gpiosetdirection  TRUE
	#define EXP_gpiosetdirection  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetdirection", (RTS_UINTPTR)gpiosetdirection, 1, 0x30BD8EA7, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_gpiosetdirection  PFGPIOSETDIRECTION_IEC pfgpiosetdirection;
	#define EXT_gpiosetdirection  extern PFGPIOSETDIRECTION_IEC pfgpiosetdirection;
	#define GET_gpiosetdirection(fl)  s_pfCMGetAPI2( "gpiosetdirection", (RTS_VOID_FCTPTR *)&pfgpiosetdirection, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x30BD8EA7, 0x03051114)
	#define CAL_gpiosetdirection  pfgpiosetdirection
	#define CHK_gpiosetdirection  (pfgpiosetdirection != NULL)
	#define EXP_gpiosetdirection   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetdirection", (RTS_UINTPTR)gpiosetdirection, 1, 0x30BD8EA7, 0x03051114) 
#endif


/**
 * <description>
 * gpiosetvalue
 * </description>
 * <element name="gpioSetValue" type=OUT></element>
 * <element name="n" type=IN></element>
 * <element name="val" type=IN></element>
*/
typedef struct taggpiosetvalue_struct
{
	RTS_IEC_BYTE n;
	RTS_IEC_BOOL val;
	RTS_IEC_BOOL gpioSetValue;
} gpiosetvalue_struct;

void CDECL CDECL_EXT gpiosetvalue(gpiosetvalue_struct *p);
typedef void (CDECL CDECL_EXT* PFGPIOSETVALUE_IEC) (gpiosetvalue_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(GPIOSETVALUE_NOTIMPLEMENTED)
	#define USE_gpiosetvalue
	#define EXT_gpiosetvalue
	#define GET_gpiosetvalue(fl)  ERR_NOTIMPLEMENTED
	#define CAL_gpiosetvalue(p0) 
	#define CHK_gpiosetvalue  FALSE
	#define EXP_gpiosetvalue  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_gpiosetvalue
	#define EXT_gpiosetvalue
	#define GET_gpiosetvalue(fl)  CAL_CMGETAPI( "gpiosetvalue" ) 
	#define CAL_gpiosetvalue  gpiosetvalue
	#define CHK_gpiosetvalue  TRUE
	#define EXP_gpiosetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetvalue", (RTS_UINTPTR)gpiosetvalue, 1, 0x6F55F30C, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_gpiosetvalue
	#define EXT_gpiosetvalue
	#define GET_gpiosetvalue(fl)  CAL_CMGETAPI( "gpiosetvalue" ) 
	#define CAL_gpiosetvalue  gpiosetvalue
	#define CHK_gpiosetvalue  TRUE
	#define EXP_gpiosetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetvalue", (RTS_UINTPTR)gpiosetvalue, 1, 0x6F55F30C, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3gpiosetvalue
	#define EXT_EmiconSys_3gpiosetvalue
	#define GET_EmiconSys_3gpiosetvalue  ERR_OK
	#define CAL_EmiconSys_3gpiosetvalue  gpiosetvalue
	#define CHK_EmiconSys_3gpiosetvalue  TRUE
	#define EXP_EmiconSys_3gpiosetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetvalue", (RTS_UINTPTR)gpiosetvalue, 1, 0x6F55F30C, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_gpiosetvalue
	#define EXT_gpiosetvalue
	#define GET_gpiosetvalue(fl)  CAL_CMGETAPI( "gpiosetvalue" ) 
	#define CAL_gpiosetvalue  gpiosetvalue
	#define CHK_gpiosetvalue  TRUE
	#define EXP_gpiosetvalue  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetvalue", (RTS_UINTPTR)gpiosetvalue, 1, 0x6F55F30C, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_gpiosetvalue  PFGPIOSETVALUE_IEC pfgpiosetvalue;
	#define EXT_gpiosetvalue  extern PFGPIOSETVALUE_IEC pfgpiosetvalue;
	#define GET_gpiosetvalue(fl)  s_pfCMGetAPI2( "gpiosetvalue", (RTS_VOID_FCTPTR *)&pfgpiosetvalue, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x6F55F30C, 0x03051114)
	#define CAL_gpiosetvalue  pfgpiosetvalue
	#define CHK_gpiosetvalue  (pfgpiosetvalue != NULL)
	#define EXP_gpiosetvalue   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"gpiosetvalue", (RTS_UINTPTR)gpiosetvalue, 1, 0x6F55F30C, 0x03051114) 
#endif


/**
 * <description>
 * is_emu
 * </description>
 * <element name="is_emu" type=OUT></element>
*/
typedef struct tagis_emu_struct
{
	RTS_IEC_BOOL is_emu;
} is_emu_struct;

void CDECL CDECL_EXT is_emu(is_emu_struct *p);
typedef void (CDECL CDECL_EXT* PFIS_EMU_IEC) (is_emu_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(IS_EMU_NOTIMPLEMENTED)
	#define USE_is_emu
	#define EXT_is_emu
	#define GET_is_emu(fl)  ERR_NOTIMPLEMENTED
	#define CAL_is_emu(p0) 
	#define CHK_is_emu  FALSE
	#define EXP_is_emu  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_is_emu
	#define EXT_is_emu
	#define GET_is_emu(fl)  CAL_CMGETAPI( "is_emu" ) 
	#define CAL_is_emu  is_emu
	#define CHK_is_emu  TRUE
	#define EXP_is_emu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_emu", (RTS_UINTPTR)is_emu, 1, 0x7320DC54, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_is_emu
	#define EXT_is_emu
	#define GET_is_emu(fl)  CAL_CMGETAPI( "is_emu" ) 
	#define CAL_is_emu  is_emu
	#define CHK_is_emu  TRUE
	#define EXP_is_emu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_emu", (RTS_UINTPTR)is_emu, 1, 0x7320DC54, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3is_emu
	#define EXT_EmiconSys_3is_emu
	#define GET_EmiconSys_3is_emu  ERR_OK
	#define CAL_EmiconSys_3is_emu  is_emu
	#define CHK_EmiconSys_3is_emu  TRUE
	#define EXP_EmiconSys_3is_emu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_emu", (RTS_UINTPTR)is_emu, 1, 0x7320DC54, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_is_emu
	#define EXT_is_emu
	#define GET_is_emu(fl)  CAL_CMGETAPI( "is_emu" ) 
	#define CAL_is_emu  is_emu
	#define CHK_is_emu  TRUE
	#define EXP_is_emu  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_emu", (RTS_UINTPTR)is_emu, 1, 0x7320DC54, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_is_emu  PFIS_EMU_IEC pfis_emu;
	#define EXT_is_emu  extern PFIS_EMU_IEC pfis_emu;
	#define GET_is_emu(fl)  s_pfCMGetAPI2( "is_emu", (RTS_VOID_FCTPTR *)&pfis_emu, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x7320DC54, 0x03051114)
	#define CAL_is_emu  pfis_emu
	#define CHK_is_emu  (pfis_emu != NULL)
	#define EXP_is_emu   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"is_emu", (RTS_UINTPTR)is_emu, 1, 0x7320DC54, 0x03051114) 
#endif


/**
 * <description>
 * set_inhibit
 * </description>
 * <element name="set_inhibit" type=OUT></element>
*/
typedef struct tagset_inhibit_struct
{
	RTS_IEC_INT set_inhibit;
} set_inhibit_struct;

void CDECL CDECL_EXT set_inhibit(set_inhibit_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_INHIBIT_IEC) (set_inhibit_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(SET_INHIBIT_NOTIMPLEMENTED)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_inhibit(p0) 
	#define CHK_set_inhibit  FALSE
	#define EXP_set_inhibit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3set_inhibit
	#define EXT_EmiconSys_3set_inhibit
	#define GET_EmiconSys_3set_inhibit  ERR_OK
	#define CAL_EmiconSys_3set_inhibit  set_inhibit
	#define CHK_EmiconSys_3set_inhibit  TRUE
	#define EXP_EmiconSys_3set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_set_inhibit
	#define EXT_set_inhibit
	#define GET_set_inhibit(fl)  CAL_CMGETAPI( "set_inhibit" ) 
	#define CAL_set_inhibit  set_inhibit
	#define CHK_set_inhibit  TRUE
	#define EXP_set_inhibit  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_set_inhibit  PFSET_INHIBIT_IEC pfset_inhibit;
	#define EXT_set_inhibit  extern PFSET_INHIBIT_IEC pfset_inhibit;
	#define GET_set_inhibit(fl)  s_pfCMGetAPI2( "set_inhibit", (RTS_VOID_FCTPTR *)&pfset_inhibit, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xAFE8BB40, 0x03051114)
	#define CAL_set_inhibit  pfset_inhibit
	#define CHK_set_inhibit  (pfset_inhibit != NULL)
	#define EXP_set_inhibit   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_inhibit", (RTS_UINTPTR)set_inhibit, 1, 0xAFE8BB40, 0x03051114) 
#endif


/**
 * <description>
 * set_watchdog
 * </description>
 * <element name="set_watchdog" type=OUT></element>
*/
typedef struct tagset_watchdog_struct
{
	RTS_IEC_INT set_watchdog;
} set_watchdog_struct;

void CDECL CDECL_EXT set_watchdog(set_watchdog_struct *p);
typedef void (CDECL CDECL_EXT* PFSET_WATCHDOG_IEC) (set_watchdog_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(SET_WATCHDOG_NOTIMPLEMENTED)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  ERR_NOTIMPLEMENTED
	#define CAL_set_watchdog(p0) 
	#define CHK_set_watchdog  FALSE
	#define EXP_set_watchdog  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3set_watchdog
	#define EXT_EmiconSys_3set_watchdog
	#define GET_EmiconSys_3set_watchdog  ERR_OK
	#define CAL_EmiconSys_3set_watchdog  set_watchdog
	#define CHK_EmiconSys_3set_watchdog  TRUE
	#define EXP_EmiconSys_3set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_set_watchdog
	#define EXT_set_watchdog
	#define GET_set_watchdog(fl)  CAL_CMGETAPI( "set_watchdog" ) 
	#define CAL_set_watchdog  set_watchdog
	#define CHK_set_watchdog  TRUE
	#define EXP_set_watchdog  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_set_watchdog  PFSET_WATCHDOG_IEC pfset_watchdog;
	#define EXT_set_watchdog  extern PFSET_WATCHDOG_IEC pfset_watchdog;
	#define GET_set_watchdog(fl)  s_pfCMGetAPI2( "set_watchdog", (RTS_VOID_FCTPTR *)&pfset_watchdog, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0x9CA67B6B, 0x03051114)
	#define CAL_set_watchdog  pfset_watchdog
	#define CHK_set_watchdog  (pfset_watchdog != NULL)
	#define EXP_set_watchdog   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"set_watchdog", (RTS_UINTPTR)set_watchdog, 1, 0x9CA67B6B, 0x03051114) 
#endif


/**
 * <description>
 * syssync
 * </description>
 * <element name="SysSync" type=OUT></element>
*/
typedef struct tagsyssync_struct
{
	RTS_IEC_INT SysSync;
} syssync_struct;

void CDECL CDECL_EXT syssync(syssync_struct *p);
typedef void (CDECL CDECL_EXT* PFSYSSYNC_IEC) (syssync_struct *p);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(SYSSYNC_NOTIMPLEMENTED)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  ERR_NOTIMPLEMENTED
	#define CAL_syssync(p0) 
	#define CHK_syssync  FALSE
	#define EXP_syssync  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03051114) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03051114) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3syssync
	#define EXT_EmiconSys_3syssync
	#define GET_EmiconSys_3syssync  ERR_OK
	#define CAL_EmiconSys_3syssync  syssync
	#define CHK_EmiconSys_3syssync  TRUE
	#define EXP_EmiconSys_3syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03051114) 
#elif defined(CPLUSPLUS)
	#define USE_syssync
	#define EXT_syssync
	#define GET_syssync(fl)  CAL_CMGETAPI( "syssync" ) 
	#define CAL_syssync  syssync
	#define CHK_syssync  TRUE
	#define EXP_syssync  s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03051114) 
#else /* DYNAMIC_LINK */
	#define USE_syssync  PFSYSSYNC_IEC pfsyssync;
	#define EXT_syssync  extern PFSYSSYNC_IEC pfsyssync;
	#define GET_syssync(fl)  s_pfCMGetAPI2( "syssync", (RTS_VOID_FCTPTR *)&pfsyssync, (fl) | CM_IMPORT_EXTERNAL_LIB_FUNCTION, 0xDC1119C9, 0x03051114)
	#define CAL_syssync  pfsyssync
	#define CHK_syssync  (pfsyssync != NULL)
	#define EXP_syssync   s_pfCMRegisterAPI2( (const CMP_EXT_FUNCTION_REF*)"syssync", (RTS_UINTPTR)syssync, 1, 0xDC1119C9, 0x03051114) 
#endif


#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

bool CDECL CmpEmiconSys_gpio_export(uint8_t n);
typedef bool (CDECL * PFCMPEMICONSYS_GPIO_EXPORT) (uint8_t n);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CMPEMICONSYS_GPIO_EXPORT_NOTIMPLEMENTED)
	#define USE_CmpEmiconSys_gpio_export
	#define EXT_CmpEmiconSys_gpio_export
	#define GET_CmpEmiconSys_gpio_export(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconSys_gpio_export(p0)  (bool)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconSys_gpio_export  FALSE
	#define EXP_CmpEmiconSys_gpio_export  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconSys_gpio_export
	#define EXT_CmpEmiconSys_gpio_export
	#define GET_CmpEmiconSys_gpio_export(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_export" ) 
	#define CAL_CmpEmiconSys_gpio_export  CmpEmiconSys_gpio_export
	#define CHK_CmpEmiconSys_gpio_export  TRUE
	#define EXP_CmpEmiconSys_gpio_export  CAL_CMEXPAPI( "CmpEmiconSys_gpio_export" ) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_CmpEmiconSys_gpio_export
	#define EXT_CmpEmiconSys_gpio_export
	#define GET_CmpEmiconSys_gpio_export(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_export" ) 
	#define CAL_CmpEmiconSys_gpio_export  CmpEmiconSys_gpio_export
	#define CHK_CmpEmiconSys_gpio_export  TRUE
	#define EXP_CmpEmiconSys_gpio_export  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_export", (RTS_UINTPTR)CmpEmiconSys_gpio_export, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3CmpEmiconSys_gpio_export
	#define EXT_EmiconSys_3CmpEmiconSys_gpio_export
	#define GET_EmiconSys_3CmpEmiconSys_gpio_export  ERR_OK
	#define CAL_EmiconSys_3CmpEmiconSys_gpio_export pIEmiconSys_3->ICmpEmiconSys_gpio_export
	#define CHK_EmiconSys_3CmpEmiconSys_gpio_export (pIEmiconSys_3 != NULL)
	#define EXP_EmiconSys_3CmpEmiconSys_gpio_export  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconSys_gpio_export
	#define EXT_CmpEmiconSys_gpio_export
	#define GET_CmpEmiconSys_gpio_export(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_export" ) 
	#define CAL_CmpEmiconSys_gpio_export pIEmiconSys_3->ICmpEmiconSys_gpio_export
	#define CHK_CmpEmiconSys_gpio_export (pIEmiconSys_3 != NULL)
	#define EXP_CmpEmiconSys_gpio_export  CAL_CMEXPAPI( "CmpEmiconSys_gpio_export" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconSys_gpio_export  PFCMPEMICONSYS_GPIO_EXPORT pfCmpEmiconSys_gpio_export;
	#define EXT_CmpEmiconSys_gpio_export  extern PFCMPEMICONSYS_GPIO_EXPORT pfCmpEmiconSys_gpio_export;
	#define GET_CmpEmiconSys_gpio_export(fl)  s_pfCMGetAPI2( "CmpEmiconSys_gpio_export", (RTS_VOID_FCTPTR *)&pfCmpEmiconSys_gpio_export, (fl), 0, 0)
	#define CAL_CmpEmiconSys_gpio_export  pfCmpEmiconSys_gpio_export
	#define CHK_CmpEmiconSys_gpio_export  (pfCmpEmiconSys_gpio_export != NULL)
	#define EXP_CmpEmiconSys_gpio_export  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_export", (RTS_UINTPTR)CmpEmiconSys_gpio_export, 0, 0) 
#endif




bool CDECL CmpEmiconSys_gpio_set_direction(uint8_t n, char *direction);
typedef bool (CDECL * PFCMPEMICONSYS_GPIO_SET_DIRECTION) (uint8_t n, char *direction);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CMPEMICONSYS_GPIO_SET_DIRECTION_NOTIMPLEMENTED)
	#define USE_CmpEmiconSys_gpio_set_direction
	#define EXT_CmpEmiconSys_gpio_set_direction
	#define GET_CmpEmiconSys_gpio_set_direction(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconSys_gpio_set_direction(p0,p1)  (bool)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconSys_gpio_set_direction  FALSE
	#define EXP_CmpEmiconSys_gpio_set_direction  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconSys_gpio_set_direction
	#define EXT_CmpEmiconSys_gpio_set_direction
	#define GET_CmpEmiconSys_gpio_set_direction(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_direction" ) 
	#define CAL_CmpEmiconSys_gpio_set_direction  CmpEmiconSys_gpio_set_direction
	#define CHK_CmpEmiconSys_gpio_set_direction  TRUE
	#define EXP_CmpEmiconSys_gpio_set_direction  CAL_CMEXPAPI( "CmpEmiconSys_gpio_set_direction" ) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_CmpEmiconSys_gpio_set_direction
	#define EXT_CmpEmiconSys_gpio_set_direction
	#define GET_CmpEmiconSys_gpio_set_direction(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_direction" ) 
	#define CAL_CmpEmiconSys_gpio_set_direction  CmpEmiconSys_gpio_set_direction
	#define CHK_CmpEmiconSys_gpio_set_direction  TRUE
	#define EXP_CmpEmiconSys_gpio_set_direction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_set_direction", (RTS_UINTPTR)CmpEmiconSys_gpio_set_direction, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3CmpEmiconSys_gpio_set_direction
	#define EXT_EmiconSys_3CmpEmiconSys_gpio_set_direction
	#define GET_EmiconSys_3CmpEmiconSys_gpio_set_direction  ERR_OK
	#define CAL_EmiconSys_3CmpEmiconSys_gpio_set_direction pIEmiconSys_3->ICmpEmiconSys_gpio_set_direction
	#define CHK_EmiconSys_3CmpEmiconSys_gpio_set_direction (pIEmiconSys_3 != NULL)
	#define EXP_EmiconSys_3CmpEmiconSys_gpio_set_direction  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconSys_gpio_set_direction
	#define EXT_CmpEmiconSys_gpio_set_direction
	#define GET_CmpEmiconSys_gpio_set_direction(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_direction" ) 
	#define CAL_CmpEmiconSys_gpio_set_direction pIEmiconSys_3->ICmpEmiconSys_gpio_set_direction
	#define CHK_CmpEmiconSys_gpio_set_direction (pIEmiconSys_3 != NULL)
	#define EXP_CmpEmiconSys_gpio_set_direction  CAL_CMEXPAPI( "CmpEmiconSys_gpio_set_direction" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconSys_gpio_set_direction  PFCMPEMICONSYS_GPIO_SET_DIRECTION pfCmpEmiconSys_gpio_set_direction;
	#define EXT_CmpEmiconSys_gpio_set_direction  extern PFCMPEMICONSYS_GPIO_SET_DIRECTION pfCmpEmiconSys_gpio_set_direction;
	#define GET_CmpEmiconSys_gpio_set_direction(fl)  s_pfCMGetAPI2( "CmpEmiconSys_gpio_set_direction", (RTS_VOID_FCTPTR *)&pfCmpEmiconSys_gpio_set_direction, (fl), 0, 0)
	#define CAL_CmpEmiconSys_gpio_set_direction  pfCmpEmiconSys_gpio_set_direction
	#define CHK_CmpEmiconSys_gpio_set_direction  (pfCmpEmiconSys_gpio_set_direction != NULL)
	#define EXP_CmpEmiconSys_gpio_set_direction  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_set_direction", (RTS_UINTPTR)CmpEmiconSys_gpio_set_direction, 0, 0) 
#endif




bool CDECL CmpEmiconSys_gpio_get_value(uint8_t n);
typedef bool (CDECL * PFCMPEMICONSYS_GPIO_GET_VALUE) (uint8_t n);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CMPEMICONSYS_GPIO_GET_VALUE_NOTIMPLEMENTED)
	#define USE_CmpEmiconSys_gpio_get_value
	#define EXT_CmpEmiconSys_gpio_get_value
	#define GET_CmpEmiconSys_gpio_get_value(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconSys_gpio_get_value(p0)  (bool)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconSys_gpio_get_value  FALSE
	#define EXP_CmpEmiconSys_gpio_get_value  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconSys_gpio_get_value
	#define EXT_CmpEmiconSys_gpio_get_value
	#define GET_CmpEmiconSys_gpio_get_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_get_value" ) 
	#define CAL_CmpEmiconSys_gpio_get_value  CmpEmiconSys_gpio_get_value
	#define CHK_CmpEmiconSys_gpio_get_value  TRUE
	#define EXP_CmpEmiconSys_gpio_get_value  CAL_CMEXPAPI( "CmpEmiconSys_gpio_get_value" ) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_CmpEmiconSys_gpio_get_value
	#define EXT_CmpEmiconSys_gpio_get_value
	#define GET_CmpEmiconSys_gpio_get_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_get_value" ) 
	#define CAL_CmpEmiconSys_gpio_get_value  CmpEmiconSys_gpio_get_value
	#define CHK_CmpEmiconSys_gpio_get_value  TRUE
	#define EXP_CmpEmiconSys_gpio_get_value  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_get_value", (RTS_UINTPTR)CmpEmiconSys_gpio_get_value, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3CmpEmiconSys_gpio_get_value
	#define EXT_EmiconSys_3CmpEmiconSys_gpio_get_value
	#define GET_EmiconSys_3CmpEmiconSys_gpio_get_value  ERR_OK
	#define CAL_EmiconSys_3CmpEmiconSys_gpio_get_value pIEmiconSys_3->ICmpEmiconSys_gpio_get_value
	#define CHK_EmiconSys_3CmpEmiconSys_gpio_get_value (pIEmiconSys_3 != NULL)
	#define EXP_EmiconSys_3CmpEmiconSys_gpio_get_value  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconSys_gpio_get_value
	#define EXT_CmpEmiconSys_gpio_get_value
	#define GET_CmpEmiconSys_gpio_get_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_get_value" ) 
	#define CAL_CmpEmiconSys_gpio_get_value pIEmiconSys_3->ICmpEmiconSys_gpio_get_value
	#define CHK_CmpEmiconSys_gpio_get_value (pIEmiconSys_3 != NULL)
	#define EXP_CmpEmiconSys_gpio_get_value  CAL_CMEXPAPI( "CmpEmiconSys_gpio_get_value" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconSys_gpio_get_value  PFCMPEMICONSYS_GPIO_GET_VALUE pfCmpEmiconSys_gpio_get_value;
	#define EXT_CmpEmiconSys_gpio_get_value  extern PFCMPEMICONSYS_GPIO_GET_VALUE pfCmpEmiconSys_gpio_get_value;
	#define GET_CmpEmiconSys_gpio_get_value(fl)  s_pfCMGetAPI2( "CmpEmiconSys_gpio_get_value", (RTS_VOID_FCTPTR *)&pfCmpEmiconSys_gpio_get_value, (fl), 0, 0)
	#define CAL_CmpEmiconSys_gpio_get_value  pfCmpEmiconSys_gpio_get_value
	#define CHK_CmpEmiconSys_gpio_get_value  (pfCmpEmiconSys_gpio_get_value != NULL)
	#define EXP_CmpEmiconSys_gpio_get_value  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_get_value", (RTS_UINTPTR)CmpEmiconSys_gpio_get_value, 0, 0) 
#endif




bool CDECL CmpEmiconSys_gpio_set_value(uint8_t n, uint8_t val);
typedef bool (CDECL * PFCMPEMICONSYS_GPIO_SET_VALUE) (uint8_t n, uint8_t val);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CMPEMICONSYS_GPIO_SET_VALUE_NOTIMPLEMENTED)
	#define USE_CmpEmiconSys_gpio_set_value
	#define EXT_CmpEmiconSys_gpio_set_value
	#define GET_CmpEmiconSys_gpio_set_value(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconSys_gpio_set_value(p0,p1)  (bool)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconSys_gpio_set_value  FALSE
	#define EXP_CmpEmiconSys_gpio_set_value  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconSys_gpio_set_value
	#define EXT_CmpEmiconSys_gpio_set_value
	#define GET_CmpEmiconSys_gpio_set_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_value" ) 
	#define CAL_CmpEmiconSys_gpio_set_value  CmpEmiconSys_gpio_set_value
	#define CHK_CmpEmiconSys_gpio_set_value  TRUE
	#define EXP_CmpEmiconSys_gpio_set_value  CAL_CMEXPAPI( "CmpEmiconSys_gpio_set_value" ) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_CmpEmiconSys_gpio_set_value
	#define EXT_CmpEmiconSys_gpio_set_value
	#define GET_CmpEmiconSys_gpio_set_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_value" ) 
	#define CAL_CmpEmiconSys_gpio_set_value  CmpEmiconSys_gpio_set_value
	#define CHK_CmpEmiconSys_gpio_set_value  TRUE
	#define EXP_CmpEmiconSys_gpio_set_value  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_set_value", (RTS_UINTPTR)CmpEmiconSys_gpio_set_value, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3CmpEmiconSys_gpio_set_value
	#define EXT_EmiconSys_3CmpEmiconSys_gpio_set_value
	#define GET_EmiconSys_3CmpEmiconSys_gpio_set_value  ERR_OK
	#define CAL_EmiconSys_3CmpEmiconSys_gpio_set_value pIEmiconSys_3->ICmpEmiconSys_gpio_set_value
	#define CHK_EmiconSys_3CmpEmiconSys_gpio_set_value (pIEmiconSys_3 != NULL)
	#define EXP_EmiconSys_3CmpEmiconSys_gpio_set_value  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconSys_gpio_set_value
	#define EXT_CmpEmiconSys_gpio_set_value
	#define GET_CmpEmiconSys_gpio_set_value(fl)  CAL_CMGETAPI( "CmpEmiconSys_gpio_set_value" ) 
	#define CAL_CmpEmiconSys_gpio_set_value pIEmiconSys_3->ICmpEmiconSys_gpio_set_value
	#define CHK_CmpEmiconSys_gpio_set_value (pIEmiconSys_3 != NULL)
	#define EXP_CmpEmiconSys_gpio_set_value  CAL_CMEXPAPI( "CmpEmiconSys_gpio_set_value" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconSys_gpio_set_value  PFCMPEMICONSYS_GPIO_SET_VALUE pfCmpEmiconSys_gpio_set_value;
	#define EXT_CmpEmiconSys_gpio_set_value  extern PFCMPEMICONSYS_GPIO_SET_VALUE pfCmpEmiconSys_gpio_set_value;
	#define GET_CmpEmiconSys_gpio_set_value(fl)  s_pfCMGetAPI2( "CmpEmiconSys_gpio_set_value", (RTS_VOID_FCTPTR *)&pfCmpEmiconSys_gpio_set_value, (fl), 0, 0)
	#define CAL_CmpEmiconSys_gpio_set_value  pfCmpEmiconSys_gpio_set_value
	#define CHK_CmpEmiconSys_gpio_set_value  (pfCmpEmiconSys_gpio_set_value != NULL)
	#define EXP_CmpEmiconSys_gpio_set_value  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_gpio_set_value", (RTS_UINTPTR)CmpEmiconSys_gpio_set_value, 0, 0) 
#endif




void CDECL CmpEmiconSys_clr_inhibit(void);
typedef void (CDECL * PFCMPEMICONSYS_CLR_INHIBIT) (void);
#if defined(EMICONSYS_3_NOTIMPLEMENTED) || defined(CMPEMICONSYS_CLR_INHIBIT_NOTIMPLEMENTED)
	#define USE_CmpEmiconSys_clr_inhibit
	#define EXT_CmpEmiconSys_clr_inhibit
	#define GET_CmpEmiconSys_clr_inhibit(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconSys_clr_inhibit()  
	#define CHK_CmpEmiconSys_clr_inhibit  FALSE
	#define EXP_CmpEmiconSys_clr_inhibit  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconSys_clr_inhibit
	#define EXT_CmpEmiconSys_clr_inhibit
	#define GET_CmpEmiconSys_clr_inhibit(fl)  CAL_CMGETAPI( "CmpEmiconSys_clr_inhibit" ) 
	#define CAL_CmpEmiconSys_clr_inhibit  CmpEmiconSys_clr_inhibit
	#define CHK_CmpEmiconSys_clr_inhibit  TRUE
	#define EXP_CmpEmiconSys_clr_inhibit  CAL_CMEXPAPI( "CmpEmiconSys_clr_inhibit" ) 
#elif defined(MIXED_LINK) && !defined(EMICONSYS_3_EXTERNAL)
	#define USE_CmpEmiconSys_clr_inhibit
	#define EXT_CmpEmiconSys_clr_inhibit
	#define GET_CmpEmiconSys_clr_inhibit(fl)  CAL_CMGETAPI( "CmpEmiconSys_clr_inhibit" ) 
	#define CAL_CmpEmiconSys_clr_inhibit  CmpEmiconSys_clr_inhibit
	#define CHK_CmpEmiconSys_clr_inhibit  TRUE
	#define EXP_CmpEmiconSys_clr_inhibit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_clr_inhibit", (RTS_UINTPTR)CmpEmiconSys_clr_inhibit, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_EmiconSys_3CmpEmiconSys_clr_inhibit
	#define EXT_EmiconSys_3CmpEmiconSys_clr_inhibit
	#define GET_EmiconSys_3CmpEmiconSys_clr_inhibit  ERR_OK
	#define CAL_EmiconSys_3CmpEmiconSys_clr_inhibit pIEmiconSys_3->ICmpEmiconSys_clr_inhibit
	#define CHK_EmiconSys_3CmpEmiconSys_clr_inhibit (pIEmiconSys_3 != NULL)
	#define EXP_EmiconSys_3CmpEmiconSys_clr_inhibit  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconSys_clr_inhibit
	#define EXT_CmpEmiconSys_clr_inhibit
	#define GET_CmpEmiconSys_clr_inhibit(fl)  CAL_CMGETAPI( "CmpEmiconSys_clr_inhibit" ) 
	#define CAL_CmpEmiconSys_clr_inhibit pIEmiconSys_3->ICmpEmiconSys_clr_inhibit
	#define CHK_CmpEmiconSys_clr_inhibit (pIEmiconSys_3 != NULL)
	#define EXP_CmpEmiconSys_clr_inhibit  CAL_CMEXPAPI( "CmpEmiconSys_clr_inhibit" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconSys_clr_inhibit  PFCMPEMICONSYS_CLR_INHIBIT pfCmpEmiconSys_clr_inhibit;
	#define EXT_CmpEmiconSys_clr_inhibit  extern PFCMPEMICONSYS_CLR_INHIBIT pfCmpEmiconSys_clr_inhibit;
	#define GET_CmpEmiconSys_clr_inhibit(fl)  s_pfCMGetAPI2( "CmpEmiconSys_clr_inhibit", (RTS_VOID_FCTPTR *)&pfCmpEmiconSys_clr_inhibit, (fl), 0, 0)
	#define CAL_CmpEmiconSys_clr_inhibit  pfCmpEmiconSys_clr_inhibit
	#define CHK_CmpEmiconSys_clr_inhibit  (pfCmpEmiconSys_clr_inhibit != NULL)
	#define EXP_CmpEmiconSys_clr_inhibit  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconSys_clr_inhibit", (RTS_UINTPTR)CmpEmiconSys_clr_inhibit, 0, 0) 
#endif



#ifdef __cplusplus
}
#endif


typedef struct
{
	IBase_C *pBase;
	PFCMPEMICONSYS_GPIO_EXPORT ICmpEmiconSys_gpio_export;
 	PFCMPEMICONSYS_GPIO_SET_DIRECTION ICmpEmiconSys_gpio_set_direction;
 	PFCMPEMICONSYS_GPIO_GET_VALUE ICmpEmiconSys_gpio_get_value;
 	PFCMPEMICONSYS_GPIO_SET_VALUE ICmpEmiconSys_gpio_set_value;
 	PFCMPEMICONSYS_CLR_INHIBIT ICmpEmiconSys_clr_inhibit;
 } IEmiconSys_3_C;

#ifdef CPLUSPLUS
class IEmiconSys_3 : public IBase
{
	public:
		virtual bool CDECL ICmpEmiconSys_gpio_export(uint8_t n) =0;
		virtual bool CDECL ICmpEmiconSys_gpio_set_direction(uint8_t n, char *direction) =0;
		virtual bool CDECL ICmpEmiconSys_gpio_get_value(uint8_t n) =0;
		virtual bool CDECL ICmpEmiconSys_gpio_set_value(uint8_t n, uint8_t val) =0;
		virtual void CDECL ICmpEmiconSys_clr_inhibit(void) =0;
};
	#ifndef ITF_EmiconSys_3
		#define ITF_EmiconSys_3 static IEmiconSys_3 *pIEmiconSys_3 = NULL;
	#endif
	#define EXTITF_EmiconSys_3
#else	/*CPLUSPLUS*/
	typedef IEmiconSys_3_C		IEmiconSys_3;
	#ifndef ITF_EmiconSys_3
		#define ITF_EmiconSys_3
	#endif
	#define EXTITF_EmiconSys_3
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_EMICONSYS_3ITF_H_*/
