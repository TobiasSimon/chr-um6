
/* 
 * File: chr_um6.c
 * Purpose: CHR-UM6 Interface
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


#include "chr_um6.h"
#include "../wire_format/um6_parser.h"
#include "../regs/um6_convert.h"
#include "../regs/um6_regs.h"

#include <pthread.h>
#include <endian.h>
#include <string.h>
#include <stdio.h>
#include <math.h>


void um6_event_init(um6_event_t *event, um6_event_interface_t *interface)
{
   event->data = interface->create();
   event->interface = interface;
}


int um6_event_timed_wait(um6_event_t *event, unsigned int timeout)
{
   return event->interface->timed_wait(event->data, timeout);
}


void um6_event_wait(um6_event_t *event)
{
   event->interface->wait(event->data);
}


void um6_event_signal(um6_event_t *event)
{
   event->interface->signal(event->data);
}


int um6_lock(um6_dev_t *dev)
{
   return dev->lock->lock(dev->lock->context);
}


int um6_unlock(um6_dev_t *dev)
{
   return dev->lock->unlock(dev->lock->context);
}


static void handle_data(um6_data_t *out, uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = le32toh(*(uint32_t *)data);
   uint32_t data32_2 = le32toh(*(uint32_t *)(data + UM6_DATA_ITEM_SIZE));
   switch (ca)
   {
      case UM6_STATUS:
         out->status.data = data32_1;
         out->status.valid = 1;
         um6_event_signal(&out->status.event);
         break;
      
      case UM6_TEMPERATURE:
         out->temperature.data = float_from_uint32(*(uint32_t *)data);
         out->temperature.valid = 1;
         um6_event_signal(&out->temperature.event);
         break;
      
      case UM6_COMM:
         out->comm.data = data32_1;
         out->comm.valid = 1;
         um6_event_signal(&out->comm.event);
         break;
      
      case UM6_GYRO_RAW1:
         out->gyro_raw.x = gyro_from_uint16(UM6_GYRO_RAW1_GET_X(data32_1));
         out->gyro_raw.y = gyro_from_uint16(UM6_GYRO_RAW1_GET_Y(data32_1));
         out->gyro_raw.z = gyro_from_uint16(UM6_GYRO_RAW2_GET_Z(data32_2));
         out->gyro_raw.valid = 1;
         um6_event_signal(&out->gyro_raw.event);
         break;

      case UM6_GYRO_PROC1:
         out->gyro_proc.x = gyro_from_uint16(UM6_GYRO_PROC1_GET_X(data32_1));
         out->gyro_proc.y = gyro_from_uint16(UM6_GYRO_PROC1_GET_Y(data32_1));
         out->gyro_proc.z = gyro_from_uint16(UM6_GYRO_PROC2_GET_Z(data32_2));
         out->gyro_proc.valid = 1;
         um6_event_signal(&out->gyro_proc.event);
         break;

      case UM6_ACC_PROC1:
         out->acc_proc.x = acc_from_uint16(UM6_ACC_PROC1_GET_X(data32_1));
         out->acc_proc.y = acc_from_uint16(UM6_ACC_PROC1_GET_Y(data32_1));
         out->acc_proc.z = acc_from_uint16(UM6_ACC_PROC2_GET_Z(data32_2));
         out->acc_proc.valid = 1;
         um6_event_signal(&out->acc_proc.event);
         break;

      case UM6_MAG_PROC1:
         out->mag_proc.x = mag_from_uint16(UM6_MAG_PROC1_GET_X(data32_1));
         out->mag_proc.y = mag_from_uint16(UM6_MAG_PROC1_GET_Y(data32_1));
         out->mag_proc.z = mag_from_uint16(UM6_MAG_PROC2_GET_Z(data32_2));
         out->mag_proc.valid = 1;
         um6_event_signal(&out->mag_proc.event);
         break;

      case UM6_EULER1:
         out->euler.phi = euler_from_uint16(UM6_EULER1_GET_PHI(data32_1));
         out->euler.theta = euler_from_uint16(UM6_EULER1_GET_THETA(data32_1));
         out->euler.psi = euler_from_uint16(UM6_EULER2_GET_PSI(data32_2));
         out->euler.valid = 1;
         um6_event_signal(&out->euler.event);
         break;

      default:
         printf("%X\n", ca);
   }
}


void *um6_reader(void *arg)
{
   um6_dev_t *dev = (um6_dev_t *)arg;
   um6_io_t *io = dev->io;
   um6_parser_t parser;
   um6_parser_init(&parser);
   int start = 0;
   while (1)
   {
      int c = io->read(io->context);
      if (c >= 0)
      {
         int ret = um6_parser_run(&parser, c);
         if (ret == 1)
         {
            handle_data(&dev->data, parser.ca, parser.data);
         }
         else if (ret < 0 && start++ > UM6_DATA_MAX)
         {
            start = UM6_DATA_MAX;
            printf("error: %d\n", ret);
         }
      }
   }
   pthread_exit(NULL);
}


void um6_dev_init(um6_dev_t *dev, um6_lock_t *lock, um6_io_t *io, um6_event_interface_t *event_interface)
{
   dev->io = io;
   dev->lock = lock;
   memset(&dev->data, 0, sizeof(um6_data_t));
   um6_composer_init(&dev->composer);
   um6_event_init(&dev->data.status.event, event_interface);
   um6_event_init(&dev->data.temperature.event, event_interface);
   um6_event_init(&dev->data.comm.event, event_interface);
   um6_event_init(&dev->data.gyro_raw.event, event_interface);
   um6_event_init(&dev->data.gyro_proc.event, event_interface);
   um6_event_init(&dev->data.acc_proc.event, event_interface);
   um6_event_init(&dev->data.mag_proc.event, event_interface);
   um6_event_init(&dev->data.euler.event, event_interface);
}


int um6_compose_and_send(um6_dev_t *dev, const uint8_t *data, const uint8_t data_len,
                         const uint8_t is_batch, const uint8_t ca)
{
   int ret;
   um6_lock(dev);
   um6_composer_run(&dev->composer, data, data_len, is_batch, ca);
   int i;
   for (i = 0; i < dev->composer.size; i++)
   {
      ret = dev->io->write(dev->io->context, dev->composer.data[i]);
      if (ret != 1)
      {
         goto out;
      }
   }
out:
   um6_unlock(dev);
   return ret;
}


uint32_t um6_get_status(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_STATUS);
   um6_event_wait(&dev->data.status.event);
   return dev->data.status.data;
}


uint32_t um6_get_comm(um6_dev_t *dev)
{
   um6_compose_and_send(dev, NULL, 0, 0, UM6_COMM);
   um6_event_wait(&dev->data.comm.event);
   return dev->data.comm.data;
}

