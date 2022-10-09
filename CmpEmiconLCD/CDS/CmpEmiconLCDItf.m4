/**
 * <interfacename>CmpEmiconLCD</interfacename>
 * <description></description>
 *
 * <copyright></copyright>
 */

SET_INTERFACE_NAME(`CmpEmiconLCD')

/** EXTERN LIB SECTION BEGIN **/
/*  Comments are ignored for m4 compiler so restructured text can be used. changecom(`/*', `*/') */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * <description>
 * 
 * * Выводит на LCD экран с заданным номером.
 * 
 * </description>
 * <element name="display_screen" type=OUT></element>
 * <element name="n" type=IN>номер экрана</element>
*/
typedef struct tagdisplay_screen_struct
{
	RTS_IEC_USINT n;
	RTS_IEC_INT display_screen;
} display_screen_struct;

DEF_API(`void',`CDECL',`display_screen',`(display_screen_struct *p)',1,0x46B0648F,0x03051114)

/**
 * <description>
 * 
 * * Возвращает номер отображаемого экрана на LCD.
 * 
 * </description>
 * <element name="get_current_screen" type=OUT></element>
*/
typedef struct tagget_current_screen_struct
{
	RTS_IEC_USINT get_current_screen;
} get_current_screen_struct;

DEF_API(`void',`CDECL',`get_current_screen',`(get_current_screen_struct *p)',1,0xB05F91C6,0x03051114)

/**
 * <description>
 * 
 * * Возвращает номер экрана по умолчанию.
 * 
 * </description>
 * <element name="get_default_screen" type=OUT></element>
*/
typedef struct tagget_default_screen_struct
{
	RTS_IEC_USINT get_default_screen;
} get_default_screen_struct;

DEF_API(`void',`CDECL',`get_default_screen',`(get_default_screen_struct *p)',1,0xBC400E09,0x03051114)

/**
 * <description>
 * get_str_lcd_emu
 * </description>
 * <element name="get_str_lcd_emu" type=OUT></element>
 * <element name="ps_line1" type=IN></element>
 * <element name="ps_line2" type=IN></element>
*/
typedef struct tagget_str_lcd_emu_struct
{
	RTS_IEC_STRING *ps_line1;
	RTS_IEC_STRING *ps_line2;
	RTS_IEC_BOOL get_str_lcd_emu;
} get_str_lcd_emu_struct;

DEF_API(`void',`CDECL',`get_str_lcd_emu',`(get_str_lcd_emu_struct *p)',1,0x7E7019BC,0x03051114)

/**
 * <description>
 * lcd_puts
 * </description>
 * <element name="lcd_puts" type=OUT></element>
 * <element name="usiScreen" type=IN>номер экрана 0-9</element>
 * <element name="iLine" type=IN>Строка 0-1</element>
 * <element name="iPos" type=IN>Столбец 0-249</element>
 * <element name="stData" type=IN>Текст 1-250 сиволов</element>
*/
typedef struct taglcd_puts_struct
{
	RTS_IEC_USINT usiScreen;
	RTS_IEC_USINT iLine;
	RTS_IEC_USINT iPos;
	RTS_IEC_STRING stData[252];
	RTS_IEC_INT lcd_puts;
} lcd_puts_struct;

DEF_API(`void',`CDECL',`lcd_puts',`(lcd_puts_struct *p)',1,0xA74BD7B7,0x03051114)

/**
 * <description>
 * menu_item_create
 * </description>
 * <element name="menu_item_create" type=OUT></element>
 * <element name="screen" type=IN>номер экрана меню 0-9</element>
 * <element name="st_line1" type=IN>Текст 1-250 сиволов</element>
 * <element name="st_line2" type=IN>Текст 1-250 сиволов</element>
 * <element name="p_menu_function" type=IN>указатель на функцию</element>
*/
typedef struct tagmenu_item_create_struct
{
	RTS_IEC_USINT screen;
	RTS_IEC_STRING st_line1[252];
	RTS_IEC_STRING st_line2[252];
	RTS_IEC_BYTE *p_menu_function;
	RTS_IEC_UDINT menu_item_create;
} menu_item_create_struct;

DEF_API(`void',`CDECL',`menu_item_create',`(menu_item_create_struct *p)',1,0x4B583CD3,0x03051114)

/**
 * <description>
 * 
 * * Устанавливает эран по умолчанию.
 * 
 * </description>
 * <element name="set_default_screen" type=OUT></element>
 * <element name="n" type=IN>номер экрана</element>
*/
typedef struct tagset_default_screen_struct
{
	RTS_IEC_USINT n;
	RTS_IEC_USINT set_default_screen;
} set_default_screen_struct;

DEF_API(`void',`CDECL',`set_default_screen',`(set_default_screen_struct *p)',1,0x99CC3DB4,0x03051114)

/**
 * <description>
 * 
 * * Установка видимости экрана.
 * 
 * </description>
 * <element name="set_visibility" type=OUT></element>
 * <element name="n" type=IN>номер экрана</element>
 * <element name="visibility" type=IN></element>
*/
typedef struct tagset_visibility_struct
{
	RTS_IEC_USINT n;
	RTS_IEC_BOOL visibility;
	RTS_IEC_INT set_visibility;
} set_visibility_struct;

DEF_API(`void',`CDECL',`set_visibility',`(set_visibility_struct *p)',1,0x0FD7B385,0x03051114)

#ifdef __cplusplus
}
#endif

/** EXTERN LIB SECTION END **/

