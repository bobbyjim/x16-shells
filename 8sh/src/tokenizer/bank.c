#include <peekpoke.h>

#include "bank.h"

int currentBank = 0;

void setBank(int bank)
{
   if (bank < 1) bank = 1;

   if (currentBank != bank)
   {
      POKE(0x9f61, bank); // r38
      POKE(0,bank);       // r39+
      currentBank = bank;
   }
}
