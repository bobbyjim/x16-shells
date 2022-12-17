
#include <stdlib.h>
#include <conio.h>
#include <peekpoke.h>

#include "bank.h"

extern uint8_t fortuneBank; // from main.c

void fortune()
{
   int index;
   char* address = (char*)(0xa020);

   setBank(fortuneBank);

   index = rand() % PEEK(0xa010); 

   cputs("\r\n\r\n\r\n\r\n");
   while(--index)
   {
      while(address[0] != 0)
      {
         if (index == 1)
         {
            switch(address[0])
	    {
//               case  0: break;

               case  9: // tab
		   cprintf("     ");
		   break;

               case 10: // \r
		   cprintf("\r\n   ");
		   break;

               default:
		   cprintf("%c", address[0]);
		   break;
            }
         }
         ++address;
      }
      ++address; // skip the zero?
   }
   cputs("\r\n\r\n\r\n\r\n");
}
