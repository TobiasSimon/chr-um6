

#include <termios.h>


#ifndef __SERIAL_H__
#define __SERIAL_H__


typedef struct
{
   const char *path;
   int handle;
   struct termios orig_options;
}
serialport_t;


int serial_open(serialport_t *port, const char *path, int baudrate, unsigned int oflag, unsigned int lflag, unsigned int cflag);

int serial_read_line(char buffer[256], const serialport_t *port);

int serial_read_char(const serialport_t *port);

int serial_read_buffer(char *buffer, int buf_size, const serialport_t *port);

int serial_write(const serialport_t *port, const char *buffer, unsigned int len);

int serial_write_char(const serialport_t *port, unsigned char c);

int serial_write_line(const serialport_t *port, const char *buffer);

int serial_close(serialport_t *port);


#endif /* COCO_SERIAL_H */

