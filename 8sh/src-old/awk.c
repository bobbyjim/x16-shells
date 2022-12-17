
#include <conio.h>
#include <string.h>

extern char* lineInputBuffer;

void awk() // lineInputBuffer
{
   char* token = strtok(lineInputBuffer, " ");

   // is it null?
   if (token == NULL || strlen(token) == 0)
   {
      cprintf("awk / nothing here.");
      return;
   }

   // is it a pattern?
   if (token[0] == ':')
      cprintf("awk / pattern: %s\n", token);
   else
      cprintf("awk / action: %s\n", token);
}

