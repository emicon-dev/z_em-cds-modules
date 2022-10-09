 
	
	
#ifndef _CMPEMICONMEMMANAGERITF_H_
#define _CMPEMICONMEMMANAGERITF_H_

#include "CmpStd.h"

 

 




#include "CmpItf.h"

/* Hook definitions (0..10000 reserved for core components) */

#define CH_USER_1						10000
/*	First user hook
	ulParam1: Not used
	ulParam2: Not used
*/


#ifdef __cplusplus
extern "C" {
#endif

typedef struct mem_buffer {
	void *p;
	uint32_t size;
} mem_buffer;

/**
 * <description> 
 * A useless export function:
 * This function is exported and could be called from other components. This is only for Components, which have
 * exactly one instance of itself in the whole runtime.
 * </description>
 * <result>ERR_OK</result>
 */
uint32_t CDECL CmpEmiconMemManager_get_cs3_allocated_mem_size(void);
typedef uint32_t (CDECL * PFCMPEMICONMEMMANAGER_GET_CS3_ALLOCATED_MEM_SIZE) (void);
#if defined(CMPEMICONMEMMANAGER_NOTIMPLEMENTED) || defined(CMPEMICONMEMMANAGER_GET_CS3_ALLOCATED_MEM_SIZE_NOTIMPLEMENTED)
	#define USE_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size()  (uint32_t)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconMemManager_get_cs3_allocated_mem_size  FALSE
	#define EXP_CmpEmiconMemManager_get_cs3_allocated_mem_size  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_get_cs3_allocated_mem_size" ) 
	#define CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size  CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define CHK_CmpEmiconMemManager_get_cs3_allocated_mem_size  TRUE
	#define EXP_CmpEmiconMemManager_get_cs3_allocated_mem_size  CAL_CMEXPAPI( "CmpEmiconMemManager_get_cs3_allocated_mem_size" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONMEMMANAGER_EXTERNAL)
	#define USE_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_get_cs3_allocated_mem_size" ) 
	#define CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size  CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define CHK_CmpEmiconMemManager_get_cs3_allocated_mem_size  TRUE
	#define EXP_CmpEmiconMemManager_get_cs3_allocated_mem_size  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_get_cs3_allocated_mem_size", (RTS_UINTPTR)CmpEmiconMemManager_get_cs3_allocated_mem_size, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size
	#define EXT_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size
	#define GET_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size  ERR_OK
	#define CAL_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size pICmpEmiconMemManager->ICmpEmiconMemManager_get_cs3_allocated_mem_size
	#define CHK_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManagerCmpEmiconMemManager_get_cs3_allocated_mem_size  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size
	#define GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_get_cs3_allocated_mem_size" ) 
	#define CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size pICmpEmiconMemManager->ICmpEmiconMemManager_get_cs3_allocated_mem_size
	#define CHK_CmpEmiconMemManager_get_cs3_allocated_mem_size (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManager_get_cs3_allocated_mem_size  CAL_CMEXPAPI( "CmpEmiconMemManager_get_cs3_allocated_mem_size" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconMemManager_get_cs3_allocated_mem_size  PFCMPEMICONMEMMANAGER_GET_CS3_ALLOCATED_MEM_SIZE pfCmpEmiconMemManager_get_cs3_allocated_mem_size;
	#define EXT_CmpEmiconMemManager_get_cs3_allocated_mem_size  extern PFCMPEMICONMEMMANAGER_GET_CS3_ALLOCATED_MEM_SIZE pfCmpEmiconMemManager_get_cs3_allocated_mem_size;
	#define GET_CmpEmiconMemManager_get_cs3_allocated_mem_size(fl)  s_pfCMGetAPI2( "CmpEmiconMemManager_get_cs3_allocated_mem_size", (RTS_VOID_FCTPTR *)&pfCmpEmiconMemManager_get_cs3_allocated_mem_size, (fl), 0, 0)
	#define CAL_CmpEmiconMemManager_get_cs3_allocated_mem_size  pfCmpEmiconMemManager_get_cs3_allocated_mem_size
	#define CHK_CmpEmiconMemManager_get_cs3_allocated_mem_size  (pfCmpEmiconMemManager_get_cs3_allocated_mem_size != NULL)
	#define EXP_CmpEmiconMemManager_get_cs3_allocated_mem_size  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_get_cs3_allocated_mem_size", (RTS_UINTPTR)CmpEmiconMemManager_get_cs3_allocated_mem_size, 0, 0) 
#endif



int16_t CDECL CmpEmiconMemManager_mem_to_file(long int l_byte, long int b_byte);
typedef int16_t (CDECL * PFCMPEMICONMEMMANAGER_MEM_TO_FILE) (long int l_byte, long int b_byte);
#if defined(CMPEMICONMEMMANAGER_NOTIMPLEMENTED) || defined(CMPEMICONMEMMANAGER_MEM_TO_FILE_NOTIMPLEMENTED)
	#define USE_CmpEmiconMemManager_mem_to_file
	#define EXT_CmpEmiconMemManager_mem_to_file
	#define GET_CmpEmiconMemManager_mem_to_file(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconMemManager_mem_to_file(p0,p1)  (int16_t)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconMemManager_mem_to_file  FALSE
	#define EXP_CmpEmiconMemManager_mem_to_file  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconMemManager_mem_to_file
	#define EXT_CmpEmiconMemManager_mem_to_file
	#define GET_CmpEmiconMemManager_mem_to_file(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_mem_to_file" ) 
	#define CAL_CmpEmiconMemManager_mem_to_file  CmpEmiconMemManager_mem_to_file
	#define CHK_CmpEmiconMemManager_mem_to_file  TRUE
	#define EXP_CmpEmiconMemManager_mem_to_file  CAL_CMEXPAPI( "CmpEmiconMemManager_mem_to_file" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONMEMMANAGER_EXTERNAL)
	#define USE_CmpEmiconMemManager_mem_to_file
	#define EXT_CmpEmiconMemManager_mem_to_file
	#define GET_CmpEmiconMemManager_mem_to_file(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_mem_to_file" ) 
	#define CAL_CmpEmiconMemManager_mem_to_file  CmpEmiconMemManager_mem_to_file
	#define CHK_CmpEmiconMemManager_mem_to_file  TRUE
	#define EXP_CmpEmiconMemManager_mem_to_file  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_mem_to_file", (RTS_UINTPTR)CmpEmiconMemManager_mem_to_file, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file
	#define EXT_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file
	#define GET_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file  ERR_OK
	#define CAL_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file pICmpEmiconMemManager->ICmpEmiconMemManager_mem_to_file
	#define CHK_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManagerCmpEmiconMemManager_mem_to_file  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconMemManager_mem_to_file
	#define EXT_CmpEmiconMemManager_mem_to_file
	#define GET_CmpEmiconMemManager_mem_to_file(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_mem_to_file" ) 
	#define CAL_CmpEmiconMemManager_mem_to_file pICmpEmiconMemManager->ICmpEmiconMemManager_mem_to_file
	#define CHK_CmpEmiconMemManager_mem_to_file (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManager_mem_to_file  CAL_CMEXPAPI( "CmpEmiconMemManager_mem_to_file" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconMemManager_mem_to_file  PFCMPEMICONMEMMANAGER_MEM_TO_FILE pfCmpEmiconMemManager_mem_to_file;
	#define EXT_CmpEmiconMemManager_mem_to_file  extern PFCMPEMICONMEMMANAGER_MEM_TO_FILE pfCmpEmiconMemManager_mem_to_file;
	#define GET_CmpEmiconMemManager_mem_to_file(fl)  s_pfCMGetAPI2( "CmpEmiconMemManager_mem_to_file", (RTS_VOID_FCTPTR *)&pfCmpEmiconMemManager_mem_to_file, (fl), 0, 0)
	#define CAL_CmpEmiconMemManager_mem_to_file  pfCmpEmiconMemManager_mem_to_file
	#define CHK_CmpEmiconMemManager_mem_to_file  (pfCmpEmiconMemManager_mem_to_file != NULL)
	#define EXP_CmpEmiconMemManager_mem_to_file  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_mem_to_file", (RTS_UINTPTR)CmpEmiconMemManager_mem_to_file, 0, 0) 
#endif



int16_t CDECL CmpEmiconMemManager_file_to_mem(void);
typedef int16_t (CDECL * PFCMPEMICONMEMMANAGER_FILE_TO_MEM) (void);
#if defined(CMPEMICONMEMMANAGER_NOTIMPLEMENTED) || defined(CMPEMICONMEMMANAGER_FILE_TO_MEM_NOTIMPLEMENTED)
	#define USE_CmpEmiconMemManager_file_to_mem
	#define EXT_CmpEmiconMemManager_file_to_mem
	#define GET_CmpEmiconMemManager_file_to_mem(fl)  ERR_NOTIMPLEMENTED
	#define CAL_CmpEmiconMemManager_file_to_mem()  (int16_t)ERR_NOTIMPLEMENTED
	#define CHK_CmpEmiconMemManager_file_to_mem  FALSE
	#define EXP_CmpEmiconMemManager_file_to_mem  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_CmpEmiconMemManager_file_to_mem
	#define EXT_CmpEmiconMemManager_file_to_mem
	#define GET_CmpEmiconMemManager_file_to_mem(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_file_to_mem" ) 
	#define CAL_CmpEmiconMemManager_file_to_mem  CmpEmiconMemManager_file_to_mem
	#define CHK_CmpEmiconMemManager_file_to_mem  TRUE
	#define EXP_CmpEmiconMemManager_file_to_mem  CAL_CMEXPAPI( "CmpEmiconMemManager_file_to_mem" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONMEMMANAGER_EXTERNAL)
	#define USE_CmpEmiconMemManager_file_to_mem
	#define EXT_CmpEmiconMemManager_file_to_mem
	#define GET_CmpEmiconMemManager_file_to_mem(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_file_to_mem" ) 
	#define CAL_CmpEmiconMemManager_file_to_mem  CmpEmiconMemManager_file_to_mem
	#define CHK_CmpEmiconMemManager_file_to_mem  TRUE
	#define EXP_CmpEmiconMemManager_file_to_mem  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_file_to_mem", (RTS_UINTPTR)CmpEmiconMemManager_file_to_mem, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem
	#define EXT_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem
	#define GET_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem  ERR_OK
	#define CAL_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem pICmpEmiconMemManager->ICmpEmiconMemManager_file_to_mem
	#define CHK_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManagerCmpEmiconMemManager_file_to_mem  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_CmpEmiconMemManager_file_to_mem
	#define EXT_CmpEmiconMemManager_file_to_mem
	#define GET_CmpEmiconMemManager_file_to_mem(fl)  CAL_CMGETAPI( "CmpEmiconMemManager_file_to_mem" ) 
	#define CAL_CmpEmiconMemManager_file_to_mem pICmpEmiconMemManager->ICmpEmiconMemManager_file_to_mem
	#define CHK_CmpEmiconMemManager_file_to_mem (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManager_file_to_mem  CAL_CMEXPAPI( "CmpEmiconMemManager_file_to_mem" ) 
#else /* DYNAMIC_LINK */
	#define USE_CmpEmiconMemManager_file_to_mem  PFCMPEMICONMEMMANAGER_FILE_TO_MEM pfCmpEmiconMemManager_file_to_mem;
	#define EXT_CmpEmiconMemManager_file_to_mem  extern PFCMPEMICONMEMMANAGER_FILE_TO_MEM pfCmpEmiconMemManager_file_to_mem;
	#define GET_CmpEmiconMemManager_file_to_mem(fl)  s_pfCMGetAPI2( "CmpEmiconMemManager_file_to_mem", (RTS_VOID_FCTPTR *)&pfCmpEmiconMemManager_file_to_mem, (fl), 0, 0)
	#define CAL_CmpEmiconMemManager_file_to_mem  pfCmpEmiconMemManager_file_to_mem
	#define CHK_CmpEmiconMemManager_file_to_mem  (pfCmpEmiconMemManager_file_to_mem != NULL)
	#define EXP_CmpEmiconMemManager_file_to_mem  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"CmpEmiconMemManager_file_to_mem", (RTS_UINTPTR)CmpEmiconMemManager_file_to_mem, 0, 0) 
#endif



void CDECL get_sys_var_area(mem_buffer *buff);
typedef void (CDECL * PFGET_SYS_VAR_AREA) (mem_buffer *buff);
#if defined(CMPEMICONMEMMANAGER_NOTIMPLEMENTED) || defined(GET_SYS_VAR_AREA_NOTIMPLEMENTED)
	#define USE_get_sys_var_area
	#define EXT_get_sys_var_area
	#define GET_get_sys_var_area(fl)  ERR_NOTIMPLEMENTED
	#define CAL_get_sys_var_area(p0)  
	#define CHK_get_sys_var_area  FALSE
	#define EXP_get_sys_var_area  ERR_OK
#elif defined(STATIC_LINK)
	#define USE_get_sys_var_area
	#define EXT_get_sys_var_area
	#define GET_get_sys_var_area(fl)  CAL_CMGETAPI( "get_sys_var_area" ) 
	#define CAL_get_sys_var_area  get_sys_var_area
	#define CHK_get_sys_var_area  TRUE
	#define EXP_get_sys_var_area  CAL_CMEXPAPI( "get_sys_var_area" ) 
#elif defined(MIXED_LINK) && !defined(CMPEMICONMEMMANAGER_EXTERNAL)
	#define USE_get_sys_var_area
	#define EXT_get_sys_var_area
	#define GET_get_sys_var_area(fl)  CAL_CMGETAPI( "get_sys_var_area" ) 
	#define CAL_get_sys_var_area  get_sys_var_area
	#define CHK_get_sys_var_area  TRUE
	#define EXP_get_sys_var_area  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get_sys_var_area", (RTS_UINTPTR)get_sys_var_area, 0, 0) 
#elif defined(CPLUSPLUS_ONLY)
	#define USE_CmpEmiconMemManagerget_sys_var_area
	#define EXT_CmpEmiconMemManagerget_sys_var_area
	#define GET_CmpEmiconMemManagerget_sys_var_area  ERR_OK
	#define CAL_CmpEmiconMemManagerget_sys_var_area pICmpEmiconMemManager->Iget_sys_var_area
	#define CHK_CmpEmiconMemManagerget_sys_var_area (pICmpEmiconMemManager != NULL)
	#define EXP_CmpEmiconMemManagerget_sys_var_area  ERR_OK
#elif defined(CPLUSPLUS)
	#define USE_get_sys_var_area
	#define EXT_get_sys_var_area
	#define GET_get_sys_var_area(fl)  CAL_CMGETAPI( "get_sys_var_area" ) 
	#define CAL_get_sys_var_area pICmpEmiconMemManager->Iget_sys_var_area
	#define CHK_get_sys_var_area (pICmpEmiconMemManager != NULL)
	#define EXP_get_sys_var_area  CAL_CMEXPAPI( "get_sys_var_area" ) 
#else /* DYNAMIC_LINK */
	#define USE_get_sys_var_area  PFGET_SYS_VAR_AREA pfget_sys_var_area;
	#define EXT_get_sys_var_area  extern PFGET_SYS_VAR_AREA pfget_sys_var_area;
	#define GET_get_sys_var_area(fl)  s_pfCMGetAPI2( "get_sys_var_area", (RTS_VOID_FCTPTR *)&pfget_sys_var_area, (fl), 0, 0)
	#define CAL_get_sys_var_area  pfget_sys_var_area
	#define CHK_get_sys_var_area  (pfget_sys_var_area != NULL)
	#define EXP_get_sys_var_area  s_pfCMRegisterAPI( (const CMP_EXT_FUNCTION_REF*)"get_sys_var_area", (RTS_UINTPTR)get_sys_var_area, 0, 0) 
#endif



#ifdef __cplusplus
}
#endif



typedef struct
{
	IBase_C *pBase;
	PFCMPEMICONMEMMANAGER_GET_CS3_ALLOCATED_MEM_SIZE ICmpEmiconMemManager_get_cs3_allocated_mem_size;
 	PFCMPEMICONMEMMANAGER_MEM_TO_FILE ICmpEmiconMemManager_mem_to_file;
 	PFCMPEMICONMEMMANAGER_FILE_TO_MEM ICmpEmiconMemManager_file_to_mem;
 	PFGET_SYS_VAR_AREA Iget_sys_var_area;
 } ICmpEmiconMemManager_C;

#ifdef CPLUSPLUS
class ICmpEmiconMemManager : public IBase
{
	public:
		virtual uint32_t CDECL ICmpEmiconMemManager_get_cs3_allocated_mem_size(void) =0;
		virtual int16_t CDECL ICmpEmiconMemManager_mem_to_file(long int l_byte, long int b_byte) =0;
		virtual int16_t CDECL ICmpEmiconMemManager_file_to_mem(void) =0;
		virtual void CDECL Iget_sys_var_area(mem_buffer *buff) =0;
};
	#ifndef ITF_CmpEmiconMemManager
		#define ITF_CmpEmiconMemManager static ICmpEmiconMemManager *pICmpEmiconMemManager = NULL;
	#endif
	#define EXTITF_CmpEmiconMemManager
#else	/*CPLUSPLUS*/
	typedef ICmpEmiconMemManager_C		ICmpEmiconMemManager;
	#ifndef ITF_CmpEmiconMemManager
		#define ITF_CmpEmiconMemManager
	#endif
	#define EXTITF_CmpEmiconMemManager
#endif

#ifdef CPLUSPLUS_ONLY
  #undef CPLUSPLUS_ONLY
#endif

#endif /*_CMPEMICONMEMMANAGERITF_H_*/
