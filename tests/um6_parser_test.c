
/* 
 * File: um6_parser_test.h
 * Purpose: CHR-UM6 Serial Protocol Parser Test (stdin)
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



#include "../wire_format/um6_parser.h"

#include <stdlib.h>
#include <stdio.h>


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

