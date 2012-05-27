
/* 
 * File: um6_composer_test.c
 * Purpose: CHR-UM6 Serial Protocol Composer Test
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

