

#include "../wire_format/um6_parser.h"

#include <stdlib.h>


int main(void)
{
   um6_parser_t parser;
   um6_parser_init(&parser);
   int c;
   while ((c = getchar()) >= 0)
   {
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
   return 0;
}

