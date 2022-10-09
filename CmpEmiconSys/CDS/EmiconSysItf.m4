/**
 * <interfacename>EmiconSys_3</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`EmiconSys_3')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

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

DEF_API(`void',`CDECL',`clr_inhibit',`(clr_inhibit_struct *p)',1,0x0D052147,0x03051114)

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

DEF_API(`void',`CDECL',`get_ptr_to_dpm',`(get_ptr_to_dpm_struct *p)',1,0x7C8941E2,0x03051114)

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

DEF_API(`void',`CDECL',`get_ptr_to_slot0',`(get_ptr_to_slot0_struct *p)',1,0xE6CB94A0,0x03051114)

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

DEF_API(`void',`CDECL',`get_ptr_to_sock_arr',`(get_ptr_to_sock_arr_struct *p)',1,0x7F4ADBA2,0x03051114)

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

DEF_API(`void',`CDECL',`get_ptr_to_sys_area',`(get_ptr_to_sys_area_struct *p)',1,0x459659D7,0x03051114)

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

DEF_API(`void',`CDECL',`get_size_of_sys_area',`(get_size_of_sys_area_struct *p)',1,0x60094181,0x03051114)

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

DEF_API(`void',`CDECL',`getrequesttoreserve',`(getrequesttoreserve_struct *p)',1,0x1464D92A,0x03051114)

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

DEF_API(`void',`CDECL',`gpioexport',`(gpioexport_struct *p)',1,0xF49480CA,0x03051114)

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

DEF_API(`void',`CDECL',`gpiogetvalue',`(gpiogetvalue_struct *p)',1,0xC95BC6EF,0x03051114)

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

DEF_API(`void',`CDECL',`gpiosetdirection',`(gpiosetdirection_struct *p)',1,0x30BD8EA7,0x03051114)

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

DEF_API(`void',`CDECL',`gpiosetvalue',`(gpiosetvalue_struct *p)',1,0x6F55F30C,0x03051114)

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

DEF_API(`void',`CDECL',`is_emu',`(is_emu_struct *p)',1,0x7320DC54,0x03051114)

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

DEF_API(`void',`CDECL',`set_inhibit',`(set_inhibit_struct *p)',1,0xAFE8BB40,0x03051114)

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

DEF_API(`void',`CDECL',`set_watchdog',`(set_watchdog_struct *p)',1,0x9CA67B6B,0x03051114)

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

DEF_API(`void',`CDECL',`syssync',`(syssync_struct *p)',1,0xDC1119C9,0x03051114)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

#ifdef __cplusplus
extern "C" {
#endif

DEF_ITF_API(`bool',`CDECL',`CmpEmiconSys_gpio_export',`(uint8_t n)')

DEF_ITF_API(`bool',`CDECL',`CmpEmiconSys_gpio_set_direction',`(uint8_t n, char *direction)')

DEF_ITF_API(`bool',`CDECL',`CmpEmiconSys_gpio_get_value',`(uint8_t n)')

DEF_ITF_API(`bool',`CDECL',`CmpEmiconSys_gpio_set_value',`(uint8_t n, uint8_t val)')

DEF_ITF_API(`void',`CDECL',`CmpEmiconSys_clr_inhibit',`(void)')
#ifdef __cplusplus
}
#endif