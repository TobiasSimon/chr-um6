
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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{   
   um6_dev_t dev;
   um6_lock_t lock;
   um6_io_t io;

   serialport_t port;
   serial_open(&port, "/dev/ttyUSB0", 115200, 0, 0, 0);
   
   um6_event_interface_t event_interface;
   event_interface.create = posix_event_create;
   event_interface.timed_wait = posix_event_timed_wait;
   event_interface.wait = posix_event_wait;
   event_interface.signal = posix_event_signal;

   
   io.context = (void *)&port;
   io.read = (int(*)(void *))serial_read_char;
   io.write = (int(*)(void *, uint8_t))serial_write_char;

   um6_posix_lock_init(&lock);
   um6_dev_init(&dev, &lock, &io, &event_interface);
   dev.lock = &lock;
   dev.io = &io;

   pthread_t thread;
   pthread_create(&thread, NULL, um6_reader, &dev);
  
   while (1)
   {
      um6_compose_and_send(&dev, NULL, 0, 0, UM6_STATUS);
      um6_event_timed_wait(&dev.data.status.event, 1);
      
      printf("comm\n");
      //printf("euler: yaw: %f pitch: %f roll: %f\n", dev.data.euler.psi, dev.data.euler.theta, dev.data.euler.phi);
   }
   return 0;
}

