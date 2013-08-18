#include "serialportlist.h"

#include <stdio.h>
#include <string.h>

#define BREAK_IF_NULL(arg) if (arg == NULL) break
#define RETURN_IF_NULL(arg) if (arg == NULL) return
#define RETURN_VAL_IF_NULL(arg, val) if (arg == NULL) return val

static char *
execute_system_command    (const char *command)
{
	FILE *file = popen(command, "r");
	RETURN_VAL_IF_NULL(file, NULL);
	const int result_length = 4096;
	char *result = malloc(result_length);
	RETURN_VAL_IF_NULL(result, NULL);
	int offset = 0;
	while (offset != (result_length - 1)) {
		int c = fgetc(file);
		if (c == EOF) {
			result[offset] = '\0';
			break;
		}
		result[offset] = c;
		++offset;
	}
	result[offset] = '\0';
	pclose(file);
	return result;
}

static void
append_port(SerialPortList *serial_port_list, const char *port)
{
	char **ports = realloc(serial_port_list->ports, serial_port_list->size + 1);
	RETURN_IF_NULL(ports);
	serial_port_list->ports = ports;
	int len = strlen(port);
	char *new_port = malloc(len + 1);
	RETURN_IF_NULL(new_port);
	serial_port_list->ports[serial_port_list->size] = strcpy(new_port, port);
	serial_port_list->size++;
}

static void
append_socat_serial_ports (SerialPortList *serial_port_list)
{
	char *result = execute_system_command("lsof -w -c socat | grep -o '/dev/pts/[0-9]*' | uniq -u");
	RETURN_IF_NULL(result);
	int offset = 0;
	while (1) {
		const char *line = &result[offset];
		int len = 0;
		while (line[len] != '\n' && line[len] != '\0') {
			++len;
		}
		if (len > 0) {
			char *port = malloc(len + 1);
			BREAK_IF_NULL(port);
			strncpy(port, line, len);
			port[len] = '\0';
			append_port(serial_port_list, port);
			free(port);
		}
		offset += len + 1;
		if (offset > strlen(result)) {
			break;
		}
	}
	free(result);
}

static void
append_pty_serial_ports   (SerialPortList *serial_port_list)
{
	append_socat_serial_ports(serial_port_list);
}

SerialPortList *
serial_port_list_new      ()
{
	SerialPortList *serial_port_list = malloc(sizeof(SerialPortList));
	serial_port_list->size = 0;
	serial_port_list->ports = NULL;
	append_pty_serial_ports(serial_port_list);
	return serial_port_list;
}

void
serial_port_list_free     (SerialPortList *serial_port_list)
{
	int i;
	for (i = 0; i < serial_port_list->size; ++i)
	{
		free(serial_port_list->ports[i]);
	}
	if (serial_port_list->ports != NULL) {
		free(serial_port_list->ports);
	}
	free(serial_port_list);
}

size_t
serial_port_list_get_size (const SerialPortList *serial_port_list)
{
	return serial_port_list->size;
}

const char *
serial_port_list_get_port (const SerialPortList *serial_port_list,
                            size_t index)
{
	return serial_port_list->ports[index];
}
