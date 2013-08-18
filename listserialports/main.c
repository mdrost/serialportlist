#include "serialportlist/serialportlist.h"
#include <stdio.h>

int main()
{
	size_t i;
	SerialPortList *list = serial_port_list_new();
	for (i = 0; i < serial_port_list_get_size(list); ++i) {
		printf("%s\n", serial_port_list_get_port(list, i));
	}
	serial_port_list_free(list);
	return 0;
}
