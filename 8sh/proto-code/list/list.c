
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

int freelist = 256;
ENTRY list[256];

int findEntry(char* key)
{
   int i = -1;
   while(++i<256)
   {
      if( list[i].key != NULL && ! strcmp(list[i].key, key) )
      {
         return i;
      }
   }
   return -1;
}

VALUE* dynamicGetValue(char* key)
{
   int i = -1;
   i = findEntry(key);

   if (i == -1) 
      i = putEntry(key, "0");

   if (i > -1)
      return list[i].val;

   return "out of variable space";
}

int deleteEntry(char* key)
{
   int i = findEntry(key);
   if (i > -1) // found it
   { 
      list[i].key = NULL;
      ++freelist;
   }
   return i;
}

void initList()
{
   int i = -1;
   while(++i<256)
   {
      list[i].key = NULL;
   }
   freelist = 256;
}

void printEntry(int i)
{
   if (list[i].key != NULL)
   {
      printf("entry: %d\n", i);
      printf("key:   %s\n", list[i].key);
      printf("val:   %s\n", list[i].val);
   }
}

int findFree()
{
   int i = -1;
   while(++i<256)
   {
      if( list[i].key == NULL )
      {
         return i;
      }
   }
   return -1;
}


int putEntry(char* key, VALUE* val)
{
   int i;

   if (freelist == 0) return 0;

   i = findEntry(key);
   if (i == -1) i = findFree();

   if (i > -1) // found a spot
   {
      list[i].key = realloc(list[i].key, strlen(key)+1);
      list[i].val->sval = realloc(list[i].val->sval, strlen(val->sval)+1);
      strcpy(list[i].key, key);
      strcpy(list[i].val->sval, val->sval); 
      --freelist;
      return i;
   }
   
   printf("out of variable space.\n");

   return -1; 
}

void dumpList()
{
   int i = -1;
   printf("free slots: %d\n", freelist);
   while(++i<256)
   {
      printEntry(i);
   }
}


/*
int main(void)
{
   initList();
   putEntry("hi", "there");
   printf("dynamic test value: %s\n", dynamicGetValue("this is a dynamic test"));
   dumpList();
   return 0;
}
*/
