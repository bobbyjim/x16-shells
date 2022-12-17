/*
  
    SCAN-8: a tokenizer for 8 bit systems.
    Copyright (C) 2021 Robert Eaglestone

    This file is part of SCAN-8.

    SCAN-8 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SCAN-8 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SCAN-8.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>
#include <cx16.h>

#include "scanner.h"

char *ram    = ((char *)(0xA000));

void main()
{
    char line[80];

    for(;;)
    {
        printf("%c ", '%');
        gets(line);
        RAM_BANK = SOURCE_BANK;
        strcpy(ram, line); 
        initTokenDebug();
        initScanner();
        scan();
    }
}
