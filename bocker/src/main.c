
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "universal.h"
#include "container.h"
#include "image.h"

#define  STATE_READ     0
#define  STATE_DONE     255

#define  PROMPT         cprintf("\r\n%u %c ", _heapmemavail(), '%')
#define  SWITCH(ptr)    topicString = ptr
#define  CASE(ptr)      if(!strcmp(topicString,ptr))

char line[80];
char *argv[40];
unsigned char argc = 0;

char *topicString;

void prompt() 
{
   PROMPT;
   //cputs("% ");
}

void readLine()
{
   int len;
   char *token;

   fgets(line, sizeof(line), stdin);

   token = strtok( line, " " );
   argc = 0;
   while (token != NULL) {
      argv[ argc++ ] = token;
      token = strtok(NULL, " ");
   }
   //
   // Trim whitespace.
   //
   len = strcspn(argv[argc-1], "\n");  // find position of newline character
   argv[argc-1][len] = '\0';  // replace newline character with null terminator

   //
   // Now we've got argc and argv populated.
   //
}

unsigned char interpretLine()
{
   SWITCH(argv[0]);
   CASE("ps") container_ps();
   CASE("image") image_root();
   CASE("container") container_root();

   return STATE_READ;
}

void main()
{
   unsigned char state;

   cbm_k_bsout(0x8E); // revert to primary case

   //
   //  Load the PET font (I think it looks better)
   //
   cbm_k_setnam("petfont.bin");
   cbm_k_setlfs(0,8,0);
   cbm_k_load(3, 0x0f000);

   login("bocker", "bock");
   _randomize(); // stdlib.h

   for(;state != STATE_DONE;) 
   {
      prompt();
      readLine();
      state = interpretLine();
   }
}
