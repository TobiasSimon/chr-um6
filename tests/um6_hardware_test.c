

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


typedef struct
{
   uint8_t valid;

   enum
   {
      TYPE_FLOAT,
      TYPE_INT,
      TYPE_STR
   }
   type;

   union
   {
      float fl;
      int i;
      char str[5];
   };
};


float euler_from_uint16(uint16_t val)
{
   int16_t *tmp = &val;
   return ((float)*tmp) * 0.0109863 / 180.0 * M_PI;
}


void handle_data(uint8_t ca, uint8_t *data)
{
   uint32_t data32 = ntohl(*(uint32_t *)data);
   switch(ca)
   {
      case UM6_STATUS:
         UM6_STATUS_DEBUG(data32);
         break;
      
      case UM6_COMM:
         UM6_COMM_DEBUG(data32);
         break;

      case UM6_EULER_PHI_THETA:
      {
         float phi = euler_from_uint16(UM6_EULER_PHI_THETA_GET_PHI(data32));
         float theta = euler_from_uint16(UM6_EULER_PHI_THETA_GET_THETA(data32));
         printf("euler %f %f\n", phi, theta);
         break;
      }

      case UM6_EULER_PSI:
      {
         float psi = euler_from_uint16(UM6_EULER_PSI_GET_PSI(data32));
         printf("euler %f\n", psi);
         break;
      }
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

