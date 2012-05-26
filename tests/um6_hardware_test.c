

#include "../wire_format/um6_composer.h"
#include "../wire_format/um6_parser.h"
#include "../util/serial.h"
#include "../commands/um6_regs.h"
#include <netinet/in.h>


#include <pthread.h>
#include <stdio.h>


/*
 * network string [4 bytes binary] to 32-bit host float
 */
float nstohf(uint8_t *data)
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


void handle_data(uint8_t ca, uint8_t *data)
{
   switch(ca)
   {
      case UM6_TEMPERATURE:
      {
         printf("%f\n", nstohf(data));
      }
   }
}

void *um6_reader(void *ptr)
{
   serialport_t *port = ptr;
   um6_parser_t parser;
   um6_parser_init(&parser);
   while (1)
   {
      int c = serial_read_char(port);
      if (c >= 0)
      {
         int ret = um6_parser_run(&parser, c);
         if (ret == 1)
         {
            printf("success: pt = %X, ca = %X, len = %d\n", parser.pt, parser.ca, parser.data_len);
            handle_data(parser.ca, parser.data);
         }
         else if (ret < 0)
         {
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
  
   pthread_join(thread, NULL);
   /*um6_composer_t composer;
   um6_composer_init(&composer);
   um6_composer_run(&composer, NULL, 0, 0, 0xFF);
   
   int i;
   for (i = 0; i < composer.size; i++)
   {
      printf("%c", composer.data[i]);
   }*/
   return 0;
}

