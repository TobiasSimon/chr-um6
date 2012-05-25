

#include "um6_parser.h"

#include <stdio.h>


int main(void)
{
   um6_parser_t parser;
   um6_parser_init(&parser);
   FILE *f = fopen("data.log", "r");
   while (!feof(f))
   {
      int c = fgetc(f);
      int ret = um6_parser_run(&parser, c);
      if (ret == 1)
      {
         printf("success\n");
      }
      else if (ret < 0)
      {
         printf("error: %d\n", ret);
      }
   }
   fclose(f);
   return 0;
}

