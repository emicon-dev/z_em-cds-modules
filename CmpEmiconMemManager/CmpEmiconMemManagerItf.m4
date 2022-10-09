SET_INTERFACE_NAME(`CmpEmiconMemManager')

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
DEF_ITF_API(`uint32_t',`CDECL',`CmpEmiconMemManager_get_cs3_allocated_mem_size',`(void)')
DEF_ITF_API(`int16_t',`CDECL',`CmpEmiconMemManager_mem_to_file',`(long int l_byte, long int b_byte)')
DEF_ITF_API(`int16_t',`CDECL',`CmpEmiconMemManager_file_to_mem',`(void)')
DEF_ITF_API(`void',`CDECL',`get_sys_var_area',`(mem_buffer *buff)')
#ifdef __cplusplus
}
#endif
