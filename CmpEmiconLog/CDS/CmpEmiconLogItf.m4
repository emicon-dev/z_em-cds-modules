/**
 * <interfacename>CmpEmiconLog</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEmiconLog')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 * clr_sys_log
 * </description>
 * <element name="clr_sys_log" type=OUT></element>
*/
typedef struct tagclr_sys_log_struct
{
	RTS_IEC_UDINT clr_sys_log;
} clr_sys_log_struct;

DEF_API(`void',`CDECL',`clr_sys_log',`(clr_sys_log_struct *p)',1,0x8B141454,0x03051114)

/**
 * <description>
 * create_log_files
 * </description>
 * <element name="create_log_files" type=OUT></element>
*/
typedef struct tagcreate_log_files_struct
{
	RTS_IEC_DINT create_log_files;
} create_log_files_struct;

DEF_API(`void',`CDECL',`create_log_files',`(create_log_files_struct *p)',1,0x5B82FD55,0x03051114)

/**
 * <description>
 * get_next_log_item
 * </description>
 * <element name="get_next_log_item" type=OUT></element>
 * <element name="get_first" type=IN></element>
 * <element name="log_str" type=IN></element>
*/
typedef struct tagget_next_log_item_struct
{
	RTS_IEC_BOOL get_first;
	RTS_IEC_STRING *log_str;
	RTS_IEC_INT get_next_log_item;
} get_next_log_item_struct;

DEF_API(`void',`CDECL',`get_next_log_item',`(get_next_log_item_struct *p)',1,0xDA44E7BB,0x03051114)

/**
 * <description>
 * write_sys_log
 * </description>
 * <element name="write_sys_log" type=OUT></element>
 * <element name="bySeverity" type=IN>Уровень важности. ОДЗ: 0..7</element>
 * <element name="byClassId" type=IN>Класс (модуль, блок и т.п.), инициировавший запись в системный журнал. ОДЗ: 0...255</element>
 * <element name="byEvent" type=IN>Cобытие. ОДЗ: 0...31</element>
 * <element name="dwArgs" type=IN>Аргументы. Массив из 4х байт.</element>
*/
typedef struct tagwrite_sys_log_struct
{
	RTS_IEC_BYTE bySeverity;
	RTS_IEC_BYTE byClassId;
	RTS_IEC_BYTE byEvent;
	RTS_IEC_DWORD dwArgs;
	RTS_IEC_UDINT write_sys_log;
} write_sys_log_struct;

DEF_API(`void',`CDECL',`write_sys_log',`(write_sys_log_struct *p)',1,0x9D6173B8,0x03051114)

/**
 * <description>
 * write_ti_log
 * </description>
 * <element name="write_ti_log" type=OUT></element>
 * <element name="byClassId" type=IN></element>
 * <element name="pbyData" type=IN></element>
*/
typedef struct tagwrite_ti_log_struct
{
	RTS_IEC_BYTE byClassId;
	RTS_IEC_BYTE *pbyData;
	RTS_IEC_UDINT write_ti_log;
} write_ti_log_struct;

DEF_API(`void',`CDECL',`write_ti_log',`(write_ti_log_struct *p)',1,0xEED4B686,0x03051114)

/**
 * <description>
 * write_ts_log
 * </description>
 * <element name="write_ts_log" type=OUT></element>
 * <element name="byClassId" type=IN></element>
 * <element name="pbyData" type=IN></element>
*/
typedef struct tagwrite_ts_log_struct
{
	RTS_IEC_BYTE byClassId;
	RTS_IEC_BYTE *pbyData;
	RTS_IEC_UDINT write_ts_log;
} write_ts_log_struct;

DEF_API(`void',`CDECL',`write_ts_log',`(write_ts_log_struct *p)',1,0xBBC343F7,0x03051114)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

