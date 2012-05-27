
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



#include "../wire_format/um6_composer.h"
#include "../wire_format/um6_parser.h"
#include "../util/serial.h"
#include "../commands/um6_registers.h"
#include <netinet/in.h>


#include <pthread.h>
#include <stdio.h>
#include <math.h>


/*
 * network string [4 bytes binary] to 32-bit host float
 */
float ntohf(uint8_t *data)
{
  uint32_t host_data = ntohl(*(uint32_t *)data);
  return *((float *)&host_data);
}


inline float euler_from_uint16(uint16_t val)
{
   val = ntohs(val);
   int16_t *tmp = &val;
   return ((float)*tmp) * 0.0109863 / 180.0 * M_PI;
}


inline float gyro_from_uint16(uint16_t val)
{
   val = ntohs(val);
   int16_t *tmp = &val;
   return ((float)*tmp) * 0.0610352 / 180.0 * M_PI;
}


inline float acc_from_uint16(uint16_t val)
{
   val = ntohs(val);
   int16_t *tmp = &val;
   return ((float)*tmp) * 0.000183105;
}


inline float mag_from_uint16(uint16_t val)
{
   val = ntohs(val);
   int16_t *tmp = &val;
   return ((float)*tmp) * 0.000305176;
}


void handle_data(uint8_t ca, uint8_t *data)
{
   uint32_t data32_1 = *(uint32_t *)data;
   uint32_t data32_2 = *(uint32_t *)(data + 4);
   switch (ca)
   {
      case UM6_STATUS:
         UM6_STATUS_DEBUG(data32_1);
         break;
      
      case UM6_TEMPERATURE:
         printf("temperature: %f\n", ntohf(data));
         break;
      
      case UM6_COMM:
         UM6_COMM_DEBUG(data32_1);
         break;
      
      case UM6_GYRO_RAW1:
      {
         float grx = gyro_from_uint16(UM6_GYRO_RAW1_GET_X(data32_1));
         float gry = gyro_from_uint16(UM6_GYRO_RAW1_GET_Y(data32_1));
         float grz = gyro_from_uint16(UM6_GYRO_RAW2_GET_Z(data32_2));
         printf("gyro raw x = %f y = %f z = %f\n", grx, gry, grz);
         break;
      }

      case UM6_GYRO_PROC1:
      {
         float gx = gyro_from_uint16(UM6_GYRO_PROC1_GET_X(data32_1));
         float gy = gyro_from_uint16(UM6_GYRO_PROC1_GET_Y(data32_1));
         float gz = gyro_from_uint16(UM6_GYRO_PROC2_GET_Z(data32_2));
         printf("gyro x = %f y = %f z = %f\n", gx, gy, gz);
         break;
      }

      case UM6_ACC_PROC1:
      {
         float ax = acc_from_uint16(UM6_ACC_PROC1_GET_X(data32_1));
         float ay = acc_from_uint16(UM6_ACC_PROC1_GET_Y(data32_1));
         float az = acc_from_uint16(UM6_ACC_PROC2_GET_Z(data32_2));
         printf("acc x = %f y = %f z = %f\n", ax, ay, az);
         break;
      }

      case UM6_MAG_PROC1:
      {
         float mx = mag_from_uint16(UM6_MAG_PROC1_GET_X(data32_1));
         float my = mag_from_uint16(UM6_MAG_PROC1_GET_Y(data32_1));
         float mz = mag_from_uint16(UM6_MAG_PROC2_GET_Z(data32_2));
         printf("mag x = %f y = %f z = %f\n", mx, my, mz);
         break;
      }

      case UM6_EULER1:
      {
         float phi = euler_from_uint16(UM6_EULER1_GET_PHI(data32_1));
         float theta = euler_from_uint16(UM6_EULER1_GET_THETA(data32_1));
         float psi = euler_from_uint16(UM6_EULER2_GET_PSI(data32_2));
         printf("euler roll = %f pitch = %f yaw = %f\n", phi, theta, psi);
         break;
      }

      default:
         printf("%X\n", ca);
   }
}


void *um6_reader(void *ptr)
{
   serialport_t *port = ptr;
   um6_parser_t parser;
   um6_parser_init(&parser);
   int start = 0;
   while (1)
   {
      int c = serial_read_char(port);
      if (c >= 0)
      {
         int ret = um6_parser_run(&parser, c);
         if (ret == 1)
         {
            handle_data(parser.ca, parser.data);
         }
         else if (ret < 0 && start++ > UM6_DATA_MAX)
         {
            start = UM6_DATA_MAX;
            printf("error: %d\n", ret);
         }
      }
      else
      {
         fprintf(stderr, "could not read\n");
      }
   }
   pthread_exit(NULL);
}


int main(void)
{
   serialport_t port;
   serial_open(&port, "/dev/ttyUSB0", 115200, 0, 0, 0);
   
   pthread_t thread;
   pthread_create(&thread, NULL, um6_reader, &port);
  
   um6_composer_t composer;
   um6_composer_init(&composer);
   while (1)
   {
      sleep(1);
      um6_composer_run(&composer, NULL, 0, 0, UM6_COMM);
      serial_write(&port, composer.data, composer.size);
   }
   return 0;
}

