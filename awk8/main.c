#include <stdio.h>
#include <conio.h>
#include <cbm.h>
#include <cx16.h>
#include <fcntl.h>
#include <string.h>
#include <peekpoke.h>

#include "universal.h"
#include "scanner.h"

#define LOAD_TO_MAIN_RAM         0
#define LOAD_TO_VERA             2
#define BANKED_RAM               ((unsigned char *) 0xa000)

char line[80];
char condition[20];
char action[40];
char buffer[80];


    char FILENAME[80];
    char FS[80];
    unsigned char NF;
    unsigned char NR;
    char OFS[80];
    char ORS[80];
    char RS[80];



int fd;
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

int loadFile(char *fname, unsigned char bank) 
{
   setBank( bank );
   memset(BANKED_RAM, 0, 8190);
   cbm_k_setnam(fname);
   cbm_k_setlfs(0,8,0);
   cbm_k_load(LOAD_TO_MAIN_RAM, 0xa000);
   return 0;
}

int readLine(int *fdesc)
{
    unsigned char bufpos = 0;
    memset(buffer, 0, 80);

    for(;;)
    {
        if (BANKED_RAM[*fdesc] == 0) 
           return bufpos > 0? bufpos : -1;
        buffer[bufpos] = BANKED_RAM[*fdesc];
        ++bufpos;
        *fdesc += 1;
        buffer[bufpos] = 0;
        if (BANKED_RAM[*fdesc] == 10) return bufpos;
    }
}

char arg1[20], arg2[20];

int valof(char *expr)
{
   int value;

   printf("%d\n", sscanf(expr,"%s>%s", arg1, arg2));

   if (sscanf(expr, "%d", &value) == 1)
      return value;
   if (!strcmp(expr, "nf"))
      return NF;
   if (!strcmp(expr, "nr"))
      return NR;
   if (sscanf(expr,"%s>%s", arg1, arg2) == 2)
      return valof(arg1) > valof(arg2);
   if (sscanf(expr,"%s<%s", arg1, arg2) == 2)
      return valof(arg1) < valof(arg2);
   if (sscanf(expr,"%s==%s", arg1, arg2) == 2)
      return valof(arg1) == valof(arg2);

   return 0;
}

void parse()
{
   // bare file cat form
   NR = 0;
   if (sscanf(line, "'%s", FILENAME) == 1)
   {
       fd = loadFile(FILENAME, 1);
       while( readLine(&fd) > -1 )
       {
          printf("%s\n", buffer);
       }
   }
   else if (sscanf(line, "%s '%s", condition, FILENAME))
   {
       fd = loadFile(FILENAME, 1);
       while( readLine(&fd) > -1 )
       {
           ++NR;
           //printf("val: %d\n", valof(condition));
           if (valof(condition))
              printf("%s\n", buffer);
       }
   }

   // full canonical form
   //if (sscanf(line, "%s [ %s ] '%s", condition, action, FILENAME) == 3)
   if (sscanf(line, "%s [ %s ] %s", condition, action, FILENAME) == 3)
   {
       printf("canonical form:\n");
       printf("   condition: %s\n", condition);
       printf("   action   : %s\n", action);
       printf("   filename : %s\n", FILENAME);
   }
}

void main()
{
   cbm_k_bsout(0x8E); // revert to primary case

   //loadFile("logo.bin", 3);
   cbm_k_setnam("petfont.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(3, 0x0f000);

   bgcolor(COLOR_BLACK);
   clrscr();

   login("awk-8", "2021.09.30");

   for(;;)
   {
      printf("%c ", '%');
      gets(line);
      parse();
   }
}