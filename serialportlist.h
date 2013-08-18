#ifndef SERIAL_PORT_LIST_H_INCLUDED
#define SERIAL_PORT_LIST_H_INCLUDED

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SERIAL_PORT_LIST_VERSION_MAJOR 0
#define SERIAL_PORT_LIST_VERSION_MINOR 0
#define SERIAL_PORT_LIST_VERSION_MICRO 1

typedef struct _SerialPortList SerialPortList;

struct _SerialPortList {
	size_t size;
	char **ports;
};

SerialPortList *
serial_port_list_new      ();

void
serial_port_list_free     (SerialPortList *serial_port_list);

size_t
serial_port_list_get_size (const SerialPortList *serial_port_list);

const char *
serial_port_list_get_port (const SerialPortList *serial_port_list,
                           size_t index);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_PORT_LIST_H_INCLUDED
