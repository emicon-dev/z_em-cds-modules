
#include "stdint.h"
#include "errno.h"
#include <stdbool.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdarg.h>

#include "emiconlog.h"
#include "tiny-json.c"

#define	EFREAD		0x8002	/* Error occured while reading file */
#define	EFFORMAT	0x8003	/* Неверный формат файла */
#define ERR_FAILED	0x0001  /* General error - to be used only for internal errors */

#define SEARCHED_RULES_BUFFER_LEN 1000

char* err_str_rule_notfound = "[НЕ НАЙДЕНО]";

// структура основных секций файла расшифровки лога own_event_frame
typedef struct translation_rules {
	json_t const* json;
	json_t mem[3200];
	char* str_buffer;
	json_t const* default_events;
	json_t const* severities;
	json_t const* classes;
	json_t const* events;
	json_t const* inserts;
	char* default_events_prop_name;
	char* severities_prop_name;
	char* classes_prop_name;
	char* events_prop_name;
	char* inserts_prop_name;
} translation_rules;

translation_rules parse_rules = {
	.json = 0,
	.default_events = 0,
	.severities = 0,
	.classes = 0,
	.events = 0,
	.inserts = 0,
	.default_events_prop_name = "default",
	.severities_prop_name = "severities",
	.classes_prop_name = "classes",
	.events_prop_name = "events",
	.inserts_prop_name = "inserts"
};

typedef struct key_value_rule {
	char const* key;
	uint32_t val;
 } key_value_rule;


/*
* структура правил секции events
* Все аргументы после разбора json правила, укладываются в эту структуру с текстом.
* args - предназначен для хранения значений аргументов уже парсированных из
* 4х байт данных. Тк эти данные могу представлять как число, так и индекс правила,
* которе подставляет текст, то ячейка args сохраняет либо целочисленное значение
* данных либо указатель на строку. Этот аргумент подставляется в шаблон sprintf и
* и разбирается согласно шаблону. 
*/

typedef struct struct_event_data_parced {
	char const* text;
	intptr_t args[4];
} struct_event_data_parced;

// структура данных записи лога. Отличается от фрейма разделением битов event и severity
typedef struct struct_log_record {
	uint8_t class_id;
	uint8_t event_id;
	uint8_t severity;
	
	union {
		uint32_t val;
		uint8_t b[4];
	} args;
} struct_log_record;


int parse_rules_read();
int check_rule(const json_t** rule);
int parse_rules_read_file();
int get_rule_arg_value(json_t const* rule, struct_event_data_parced* event_parced_data, struct_log_record* data);
int parse_log(struct_log_record* data, char* str_result);
int parse_by_events(struct_log_record* data, char* str_result);
int parse_by_default(struct_log_record* data, char* str_result);
int parce_arg(char const* arg_name, uint32_t arg_val, intptr_t* res);
json_t const* get_rule(json_t const* rule_section, key_value_rule* search_data1, key_value_rule* search_data2);

/*
int main(int argc, char* argv[])
{

	char str[1000];
	struct_log_record data;

	char* a = argv[1];
	data.class_id = atoi(a);
	a = argv[2];
	data.event_id = atoi(a);
	a = argv[3];
	data.severity = atoi(a);
	a = argv[4];
	data.args.val = atoi(a);

	printf("Class %d event %d severity %d args %08X\n", data.class_id, data.event_id, data.severity, data.args.val);

	parse_rules_read();

	str[0] = '\0';
	parse_log(&data, str);
	printf("%s\n", str);

	printf("___\n");
	data.class_id = 102;
	str[0] = '\0';
	parse_log(&data, str);
	printf("%s\n", str);

	printf("\nEnd\n");

	return 0;
}
*/

/* parse_rules_read - читает правила из json файла, разбивает на секции.
 * Если секция отсутвует или заполнена неправильно, то указателю на эту секцию будет присвоен 0.
 */
int parse_rules_read()
{

	int res = parse_rules_read_file();

	if (res != 0)
		return res;

	parse_rules.json = json_create(parse_rules.str_buffer, parse_rules.mem, sizeof parse_rules.mem / sizeof *(parse_rules.mem));

	if (!parse_rules.json)
		return EFFORMAT;
	parse_rules.default_events = json_getProperty(parse_rules.json, parse_rules.default_events_prop_name);
	check_rule(&parse_rules.default_events);

	parse_rules.classes = json_getProperty(parse_rules.json, parse_rules.classes_prop_name);
	check_rule(&parse_rules.classes);

	parse_rules.severities = json_getProperty(parse_rules.json, parse_rules.severities_prop_name);
	check_rule(&parse_rules.severities);

	parse_rules.events = json_getProperty(parse_rules.json, parse_rules.events_prop_name);
	check_rule(&parse_rules.events);

	parse_rules.inserts = json_getProperty(parse_rules.json, parse_rules.inserts_prop_name);
	check_rule(&parse_rules.inserts);

	return 0;
}

int check_rule(const json_t** rule)
{

	if (*rule == 0)
		return 0;

	if (JSON_ARRAY != json_getType(*rule))
		*rule = 0;

	return 0;
}

int parse_rules_read_file()
{

	FILE* file;
	long numbytes;
	char* buffer;

	errno = 0;

	file = fopen(LOG_RULES_FILE, "r");
	if (file == NULL)
		return errno;

	fseek(file, 0L, SEEK_END);
	numbytes = ftell(file);
	fseek(file, 0L, SEEK_SET);

	buffer = (char*)calloc(numbytes, sizeof(char));
	if (buffer == NULL)
		return errno;

	fread(buffer, sizeof(char), numbytes, file);
	if (ferror(file)) {
		fclose(file);
		return EFREAD;
	}
	fclose(file);

	if (parse_rules.str_buffer)
		free(parse_rules.str_buffer);

	parse_rules.str_buffer = buffer;

	return 0;
}

/*
* parse_log - декодирует сообщение
* Основные правила для записей перечислены в разделе 'events' файла 'logrules.json'. 
* Если для записи правило отсутствует, выводится сообщение из раздела 'default', причем в хвост сообщения добавляется "сырое"
* представление данных - [Severity=X Class=XXX Event=XX Args=0xXXXXXXXX].
* Если для записи отсутствуют правила вообще (т.е. в обоих разделах: 'events' и 'default'), то выводится только "сырое" 
* представление данных - [Severity=X Class=XXX Event=XX Args=0xXXXXXXXX].
* - Поля 'Severity' и 'Class' выводятся только в том случае, если имеется для них правило.
* - Поле 'Event' формируется по правилам форматированного вывода 'printf()'. Передаваемые аргументы перечисляются
* последовательно (через запятую) в виде записи "arg":[index,size], где:
* - 'index' - это индекс массива 'args[4]' для выборки аргумента (ОДЗ: 0...3);
* - 'size' - это размер аргумента (ОДЗ: 1...4).
* Вместо ключевого слово "arg" может быть использовано другое:
* - "argToInsert" - требуется использовать текст из раздела 'inserts' по индексу, указанному в аргументе;
* - "argToClass" - требуется использовать текст из раздела 'classes' по индексу, указанному в аргументе;
* - "argToSeverity" - требуется использовать текст из раздела 'severeties' по индексу, указанному в аргументе;
*/
int parse_log(struct_log_record* data, char* str_result)
{

	char str[1000];

	str[0] = '\0';
	if (parse_by_events(data, str) != 0)	{
		parse_by_default(data, str);
		sprintf(str_result, "%s [Severity=%d Class=%03d Event=%02d Args=0x%08X]", str, data->severity, data->class_id, data->event_id, data->args.val);
	} else {
		strcpy(str_result, str);
	}
	
	return 0;
}

int parse_by_default(struct_log_record* data, char* str_result)
{

	json_t const* rule;
	json_t const* prop_class;
	json_t const* prop_text;
	json_t const* a_field;
	char const* text;

	uint8_t a[2] = { 0 }; // диапазон правил всегда массив 2х элементов.

	for (rule = json_getChild(parse_rules.default_events); rule != 0; rule = json_getSibling(rule)) {
		if (json_getType(rule) != JSON_OBJ)
			continue;

		prop_class = json_getProperty(rule, "class");
		if (!prop_class || json_getType(prop_class) != JSON_ARRAY)
			continue;

		prop_text = json_getProperty(rule, "text");
		if (!prop_text || json_getType(prop_text) != JSON_TEXT)
			continue;


		a_field = json_getChild(prop_class);
		if (!a_field || json_getType(a_field) != JSON_INTEGER)
			return ERR_FAILED;
		a[0] = (uint8_t)json_getInteger(a_field);

		a_field = json_getSibling(a_field);
		if (!a_field || json_getType(a_field) != JSON_INTEGER)
			return ERR_FAILED;
		a[1] = (uint8_t)json_getInteger(a_field);

		if (a[1] < a[0]) 
			continue;

		if (a[0] <= data->class_id && data->class_id <= a[1]) {
			text = json_getPropertyValue(rule, "text");
			strcpy(str_result, text);
			break;
		}
	}

	return 0;
}

int parse_by_events(struct_log_record* data, char* str_result)
{

	json_t const* rule;
	json_t const* prop_text;
	int res = ERR_FAILED;
	struct_event_data_parced event_parced_data;

	key_value_rule search_data1 = {.key = "class", .val = data->class_id};
	key_value_rule search_data2 = {.key = "event", .val = data->event_id};

	rule = get_rule(parse_rules.events, &search_data1, &search_data2);	

	if (rule) {
		prop_text = json_getProperty(rule, "text");

		// Если у правила нет текста, то и расшифровать не можем. Выходим с ошибкой.
		if (!prop_text || json_getType(prop_text) != JSON_TEXT)
			return ERR_FAILED;

		event_parced_data.text = json_getPropertyValue(rule, "text");
		get_rule_arg_value(rule, &event_parced_data, data);

		sprintf(str_result, event_parced_data.text, event_parced_data.args[0], event_parced_data.args[1], event_parced_data.args[2], event_parced_data.args[3]);
		res = 0;
	}

	return res;
}


/* Выборка аргументов правила. Это поля поля кроме class, event, text.
* Выборка производиться согласно расположению аргументов в тексте слева направо.
*/
int get_rule_arg_value(json_t const* rule, struct_event_data_parced* event_parced_data, struct_log_record* data)
{

	json_t const* sibling;
	int i = 0;
	uint8_t a[2] = { 0 }; // аргументы правил всегда массив 2х элементов- позиция и размер.
	json_t const* a_field;
	union {
		uint32_t val;
		uint8_t b[4];
	} args;

	event_parced_data->args[0] = 0;
	event_parced_data->args[1] = 0;
	event_parced_data->args[2] = 0;
	event_parced_data->args[3] = 0;
	
	for (sibling = rule->u.c.child; sibling && i < 4; sibling = sibling->sibling) {
		if (sibling->name && strcmp(sibling->name, "class") 
			&& strcmp(sibling->name, "event") && strcmp(sibling->name, "text")) {

			// параметр должен быть массиовм, иначе правило нерабочее
			if (sibling->type != JSON_ARRAY)
				return ERR_FAILED;

			// массив любого параметра должен быть обязательно 2х целочисленных элементов.
			a_field = json_getChild(sibling);
			if (!a_field || json_getType(a_field) != JSON_INTEGER) 
				return ERR_FAILED;
			a[0] = (uint8_t)json_getInteger(a_field);

			a_field = json_getSibling(a_field);
			if (!a_field || json_getType(a_field) != JSON_INTEGER) 
				return ERR_FAILED;
			a[1] = (uint8_t)json_getInteger(a_field);

			// первый элемент массива- позиция данных, второй элемент массива - количесвто байт
			// позиция должна быть в диапазоне  0..3, количество 1..4.
			if (a[0] < 0 || a[0] > 3 || a[1] < 1 || a[1] > 4 || a[0] + a[1] > 4)
				return ERR_FAILED;

			uint32_t val = 0;
			args.val = data->args.val;			
			memcpy(&val, &args.b[a[0]], a[1]);

			intptr_t t_arg;
			parce_arg(sibling->name, val, &t_arg);
			event_parced_data->args[i] = t_arg;

			i++;
		}
	}

	return 0;
}

int parce_arg(char const* arg_name, uint32_t arg_val, intptr_t* res)
{

	json_t const* rule;
	json_t const* rules_section;
	char rule_arg_name[250];
	key_value_rule search_data;
	rule_arg_name[0] = '\0';

	*res = 0;

	if (!strcmp(arg_name, "arg")) {
		*res = arg_val;
	} else if (!strcmp(arg_name, "argToInsert")) {
		rules_section = parse_rules.inserts;
		strcpy(rule_arg_name, "insert");
	} else if (!strcmp(arg_name, "argToClass")) {
		rules_section = parse_rules.classes;
		strcpy(rule_arg_name, "class");
	} else if (!strcmp(arg_name, "argToSeverity")) {
		rules_section = parse_rules.severities;
		strcpy(rule_arg_name, "severity");
	}

	if (strlen(rule_arg_name) > 0) {
		search_data.key = rule_arg_name;
		search_data.val = arg_val;
		rule = get_rule(rules_section, &search_data, NULL);

		if (!rule) {
			*res = (intptr_t)err_str_rule_notfound;
		} else {
			json_t const* rule_prop;
			rule_prop = json_getProperty(rule, "text");
			if (rule_prop && json_getType(rule_prop) == JSON_TEXT)
				*res = (intptr_t)json_getPropertyValue(rule, "text");
			else
				*res = (intptr_t) err_str_rule_notfound;
		} 

	}

	return 0;
}

json_t const* get_rule(json_t const* rule_section, key_value_rule* search_data1, key_value_rule* search_data2)
{

	json_t const* rule = 0;
	json_t const* found_rules[SEARCHED_RULES_BUFFER_LEN];
	int count_rules = 0, j, i;
	json_t const* rule_prop = 0;

	memset(found_rules, 0, sizeof(found_rules));

	for (rule = json_getChild(rule_section); rule != 0; rule = json_getSibling(rule)) {
		if (json_getType(rule) != JSON_OBJ)
			continue;

		rule_prop = json_getProperty(rule, search_data1->key);
		if (!rule_prop || json_getType(rule_prop) != JSON_INTEGER)
			continue;

		if ((uint16_t)json_getInteger(rule_prop) == search_data1->val) {
			found_rules[count_rules] = rule;
			count_rules++;
			if (count_rules >= SEARCHED_RULES_BUFFER_LEN)
				count_rules = SEARCHED_RULES_BUFFER_LEN - 1;
		}
	}

	if (search_data2) {
		for (j = 0; j < count_rules; j ++) {
			rule = found_rules[j];
			if (!rule) continue;

			rule_prop = json_getProperty(rule, search_data2->key);
			if (!rule_prop || json_getType(rule_prop) != JSON_INTEGER)
				continue;
			if ((uint16_t)json_getInteger(rule_prop) != search_data2->val)
				found_rules[j] = 0;
		}
	}

	rule = 0;
	for (i = 0; i < SEARCHED_RULES_BUFFER_LEN; i++) {
		if (found_rules[i] != 0) {
			rule = found_rules[i];
			break;
		}
	}

	return rule;
}