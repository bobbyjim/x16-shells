#include <stdint.h>

#include <peekpoke.h>

#include "version.h"
#include "common.h"
#include "bank.h"

uint8_t getVersion()
{
   return PEEK(VERSION_ADDR) > 127?
      0x100 - PEEK(VERSION_ADDR)
      : PEEK(VERSION_ADDR);
}

uint8_t isProto()
{
   return PEEK(VERSION_ADDR) > 127;
}

uint8_t determineBankCount()
{
   setBank(255);
   POKE(0xb000,17);
   if (PEEK(0xb000) == 17) return 255;
   
   setBank(191);
   POKE(0xb000,17);
   if (PEEK(0xb000) == 17) return 191;
   
   setBank(127);
   POKE(0xb000,17);
   if (PEEK(0xb000) == 17) return 127;

   return 63;
}

