

#include "../wire_format/um6_composer.h"

#include <stdio.h>


int main(void)
{
   um6_composer_t composer;
   um6_composer_init(&composer);
   um6_composer_run(&composer, NULL, 0, 0, 0xFF);
   int i;
   for (i = 0; i < composer.size; i++)
   {
      printf("%c", composer.data[i]);
   }
   return 0;
}

