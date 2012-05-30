
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
#include <stdint.h>
#include <string.h>


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
   um6_dev_init(&dev, &lock, &io, &event_interface, 1);
   
   /* create reader thread: */
   pthread_t thread;
   pthread_create(&thread, NULL, um6_reader, &dev);

   sleep(1);

   int ret;
   /* get and print firmware version: */
   char version_str[5];
   if ((ret = um6_get_fw_version(&dev, version_str)) != 0)
   {
      printf("could not read firmware version: err = %d\n", ret);
   }
   printf("UM6 firmware version: %s\n", version_str);

   printf("getting communication parameters\n");
   uint32_t comm;
   if ((ret = um6_get_comm(&dev, &comm)) != 0)
   {
      printf("could not read comm registers: err = %d\n", ret);
      return ret;
   }
   uint8_t br = UM6_COMM_GET_BAUD_RATE(comm);
   comm = 0;
   UM6_COMM_SET_BAUD_RATE(comm, br);
   UM6_COMM_SET_BC_RATE(comm, 0xF);
   UM6_COMM_SET_EU(comm);
   UM6_COMM_SET_AP(comm);
   UM6_COMM_SET_GP(comm);
   UM6_COMM_SET_BEN(comm);
   printf("setting communication parameters\n");
   if ((ret = um6_set_comm(&dev, comm)) != 0)
   {
      printf("could not send comm registers: err = %d\n", ret);
      return ret;
   }
   sleep(1);
   printf("reading communication parameters\n");
   uint32_t comm_read;
   if ((ret = um6_get_comm(&dev, &comm_read)) != 0)
   {
      printf("could not read comm registers: err = %d\n", ret);
      return ret;
   }
   if (comm != comm_read)
   {
      printf("comm verify failed: wrote: %X, read: %X\n", comm, comm_read);
   }

   printf("zeroing rate gyros\n");
   if ((ret = um6_zero_gyros(&dev)) != 0)
   {
      printf("could not zero gyros: err = %d\n", ret);
      return ret;
   }
   if ((ret = event_timed_wait(&dev.data.gyro_bias.event, 3)) != 0)
   {
      printf("zero gyros failed: err = %d\n", ret);
      return ret;
   }
#
   printf("writing mag variance\n");
   float proc_var = 1.0e-6;
   float mag_var = 1.0e-3;
   float acc_var = 1000.0;
   if ((ret = um6_set_mag_var(&dev, mag_var)) != 0)
   {
      printf("could not set mag var: err = %d\n", ret);
      return ret;
   }
   float mag_var_read;
   if ((ret = um6_get_mag_var(&dev, &mag_var_read)) != 0)
   {
      printf("could not get mag var: err = %d\n", ret);
      return ret;
   }
   if (mag_var_read != mag_var)
   {
      printf("mag var verify failed: wrote: %f, read: %f\n", mag_var, mag_var_read);
      return -1;
   }
   
   printf("writing acc variance\n");
   if ((ret = um6_set_acc_var(&dev, acc_var)) != 0)
   {
      printf("could not set acc var: err = %d\n", ret);
      return ret;
   }
   float acc_var_read;
   if ((ret = um6_get_acc_var(&dev, &acc_var_read)) != 0)
   {
      printf("could not get acc var: err = %d\n", ret);
      return ret;
   }
   if (acc_var_read != acc_var)
   {
      printf("acc var verify failed: wrote: %f, read: %f\n", acc_var, acc_var_read);
      return -1;
   }

   printf("writing proc variance\n");
   if ((ret = um6_set_proc_var(&dev, proc_var)) != 0)
   {
      printf("could not set proc var: err = %d\n", ret);
      return ret;
   }
   float proc_var_read;
   if ((ret = um6_get_proc_var(&dev, &proc_var_read)) != 0)
   {
      printf("could not get proc var: err = %d\n", ret);
      return ret;
   }
   if (proc_var_read != proc_var)
   {
      printf("proc var verify failed: wrote: %f, read: %f\n", proc_var, proc_var_read);
      return -1;
   }

   printf("resetting extended kalman filter\n");
   if ((ret = um6_reset_ekf(&dev)) != 0)
   {
      printf("could not reset ekf: err = %d\n", ret);
      return ret;
   }

   while (1)
   {
      event_wait(&dev.data.euler.event);
      printf("%f %f %f\n", dev.data.euler.psi, dev.data.euler.theta, dev.data.euler.phi);
   }

   return 0;
}

