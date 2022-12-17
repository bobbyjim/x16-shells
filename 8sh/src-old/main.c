/*

    8SH: a command interpreter for 8 bit 'retro' systems.
    Copyright (C) 2020 Robert Eaglestone

    This file is part of 8SH.

    8SH is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    8SH is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with 8SH.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cbm.h>
#include <peekpoke.h>
#include <time.h>
#include <conio.h>

#include "vm.h"
#include "chunk.h"
#include "opcodes.h"
#include "scanner.h"
#include "bank.h"
#include "debug.h"
#include "hash.h"
#include "fortune.h"
#include "version.h"
#include "common.h"
#include "compiler.h"


#define PROMPT    cprintf("\r\n%u %c ", _heapmemavail(), '%')

/***********************************************************************************************

				Globally useful variables go here.

***********************************************************************************************/

	uint8_t fortuneBank	   = 1;
	uint8_t sourceBank     	= 10;
	uint8_t tokenBank      	= 11;

	uint16_t currentToken	= 0;
	uint16_t tokenCount    	= 0;
	uint16_t tokenReadHead 	= 0;

	VM vm;

/***********************************************************************************************

				End of globally useful area.

***********************************************************************************************/
char lineInputBuffer[256];

void login()
{
   uint8_t version;
   char proto;
   uint8_t banks;

   clrscr();
   version = getVersion();
   proto   = isProto() > 0? 'p' : ' '; 
   banks   = determineBankCount();

   logo(2,9);

   textcolor(5);

   gotoxy(0,2);
   cprintf("  r%03d%c                             8-shell                               b%03d",version,proto,banks);
   cputsxy(2,5,  "****************************************************************************");
   cputsxy(9,8,  "not a warning!  all are welcome to access this system; there are no");
   cputsxy(9,10, "penalties nor any 8-shell security policy,  and no applicable state");
   cputsxy(9,12, "or federal laws. sessions & e-mail are not monitored, as the system"); 
   cputsxy(9,14, "has neither.     * * * note: system will be down if it is shut off.");
   cputsxy(2,17, "****************************************************************************");
   cputsxy(2,19,"                        commander x16 | 2021.04.15 ");

   textcolor(10);
   cputsxy(2,25,"                    * * *   press a key to login   * * * ");
   cgetc();
   cclearxy(2,25,70);
   textcolor(5);

   gotoxy(0,20);
}

void setup()
{
   _randomize();
   cbm_k_bsout(0x8E); // revert to primary case

   //
   //  Load the PET font (I think it looks better)
   //
   cbm_k_setnam("petfont.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(2, 0x0f800);

   //
   //  Load the FORTUNE file into bank 1.
   //
   setBank(fortuneBank);
   cbm_k_setnam("fortune.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(0, 0xa000);

   bgcolor(BLACK);
   initVM();
}

void teardown()
{
   freeVM();
}

void logout()
{
   clrscr();
   fortune();
   textcolor(1);
   cputs(" * * *  commander x16 basic v2+  * * *\r\n");
}


int readLine()
{
   if (!fgets(lineInputBuffer, sizeof(lineInputBuffer), stdin)) 
   {
      cprintf("\r\n");
      return 0;
   }
   lineInputBuffer[strlen(lineInputBuffer)-1] = '\0'; // chop newline
   return 1;
}

void repl()
{
   for(;;)
   {
      PROMPT;
      if (! readLine()) continue;
      if (! strcmp(lineInputBuffer,"logout")) return;

      /******************************************************

       Script is stored in Bank 1.
       That means the maximum script size is 8K.
       I don't think that's a problem!

      ******************************************************/
      setBank(sourceBank);
      bankputs(lineInputBuffer, strlen(lineInputBuffer), 0);
 
      scan();       // in scanner.c
      interpret();  // in vm.c
   }
}

void main() 
{
   setup();
   login();   
   repl();
   teardown();
   logout();
}

