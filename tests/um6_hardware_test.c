
/* 
 * File: um6_hardware_test.c
 * Purpose: CHR-UM6 Serial Protocol Hardware Test
 *
 * Copyright (C) 2012 Tobias Simon, Ilmenau University of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */


#include "../regs/um6_regs.h"
#include "../interface/chr_um6.h"
#include "../sys/posix_serial.h"
#include "../sys/posix_lock.h"
#include "../sys/posix_event.h"
#include "../sys/lock.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{   
   /* set up event interface: */
   event_interface_t event_interface;
   posix_event_interface_init(&event_interface);
   
   /* set up serial port: */
   serialport_t port;
   serial_open(&port, "/dev/ttyUSB0", 115200, 0, 0, 0);
   um6_io_t io;
   io.context = (void *)&port;
   io.read = (int(*)(void *))serial_read_char;
   io.write = (int(*)(void *, uint8_t))serial_write_char;

   /* set-up lock: */
   lock_interface_t lock_interface;
   posix_lock_interface_init(&lock_interface);
   lock_t lock;
   lock_init(&lock, &lock_interface);

   /* finally, create device: */
   um6_dev_t dev;
   um6_dev_init(&dev, &lock, &io, &event_interface);
   
   /* create reader thread: */
   pthread_t thread;
   pthread_create(&thread, NULL, um6_reader, &dev);

   /* request registers: */
   UM6_STATUS_DEBUG(um6_get_status(&dev));
   UM6_COMM_DEBUG(um6_get_comm(&dev));
   return 0;
}

