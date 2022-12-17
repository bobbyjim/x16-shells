
#include <stdint.h>
#include <conio.h>

#include "common.h"

void logo(uint8_t x, uint8_t y)
{
   textcolor(LTBLUE);
   revers(1);
   cputcxy(x,y,169);
   cputsxy(x+1,y,"  ");

   cputsxy(x,y+1," ");
   cputsxy(x+3,y+1," ");
   revers(0);
   cputcxy(x+4,y+1,169);

   revers(1);
   cputsxy(x,y+2," ");
   textcolor(RED);
   cputcxy(x+3,y+2,163);
   cputcxy(x+4,y+2,223);
   textcolor(LTBLUE);

   revers(0);
   cputcxy(x,y+3,223);
   revers(1);
   cputsxy(x+1,y+3,"  ");
   revers(0);
}
