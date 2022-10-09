
/*
    
*/

#ifndef _EMICONLOG_H_
#define	_EMICONLOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "CP56Time2a.c"

//#define LOG_RULES_FILE "logrules.json"
#define LOG_RULES_FILE "/home/plc/log/logrules.json"
#define MAX_SZ_FILE_NAME	200
#define MARK_SYS_LOG		0x80
#define MARK_TI_LOG			0x40
#define MASK_ALL_MARK		0x3F
    // ������ ����������� ������ nvram
#define NVRAM_CS3_MEM_ADDRESS	0x2000000; 

/*
 * ������������ ��� ����������� ��������� ������:
 * ���� ��������� ������ � ����� ��������� � ��������� �� NONE, �� ����� ����.
 * ���������, ��� ��� ������ �� ������� ��������� ��������� ������ �� ����� ����
 * ����� NONE. � ������ ������ 0.
 */
#define NONE 	0 

 // ����������������� ����������� ��������� �������
#define OWN_EVENT_ID_CLR 	0 	// ������� ������
#define OWN_EVENT_ID_STOP 	1 	// ������� ��� ����������
#define OWN_EVENT_ID_START 	2 	// ����� ��� ����������

#define SEVERITY_INFO 6

/*
 * ����������� ������ ���� � ������� ����� ��� �����������
 * ���������� ������ ���������� � ���������� ������� ������
 * � ������������������ ������������ � ������.
 * ������������������ � ������ �������.
 */
const int _is_bigendian_i = 1;
#define is_bigendian() ( (*(uint8_t*)&_is_bigendian_i) == 0 )

static bool _is_emu = false;

/*
 * ��������� ������ ������ ��� ������� ���� �������.
 * ��������! ��������� ������������ ������ ���� ��������� �����
 * #pragma pack(push, 1) � #pragma pack(pop). ������ ����� ����������� ���������
 * �� �������. ����� ������������ ����� ��������� �����.
 */
#pragma pack(push, 1)
typedef struct own_event_frame {
	uint8_t class_id;
	uint8_t severity_event; // 0..4 ���� ��� event, � 5..7 severity
	uint32_t args;
	CP56Time2a datetime;
} own_event_frame;

typedef struct ts_frame {
	uint8_t class_id;
	uint8_t address[3];
	uint8_t value;
	CP56Time2a datetime;
} ts_frame;

typedef struct ti_frame {
	uint8_t class_id;
	uint8_t address[3];
	uint8_t value[4];
	uint8_t quality;
	CP56Time2a datetime;
} ti_frame;
#pragma pack(pop)

#define SIZE_OF_OWN_EVENT sizeof(own_event_frame)
#define SIZE_OF_TS sizeof(ts_frame)
#define SIZE_OF_TI sizeof(ti_frame)

#define FRAME_TYPE_OWN_EVENT	1
#define FRAME_TYPE_TS			2
#define FRAME_TYPE_TI			3

static bool log_init_done = false;
/*
 * ���������� ���������� ������ ����. �� ��������� �������� � ����� � ���������.
 */
char _log_folder[] = "/home/plc/log/";

/*
 * ���������� ������ ���� ���� (_init_mark), ���������� ������������� ������
 * �� ������ LOG_INIT_MARK, ���� ����� ����� �������/������� LOG_INIT_MARK_BUSY.
 */
#define LOG_INIT_MARK 		0x55aa
#define LOG_INIT_MARK_BUSY 	0x65aa

#ifdef __cplusplus
}
#endif

#endif	/* _EMICONLOG_H_ */
