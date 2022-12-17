#include <stdio.h>
#include <string.h>
#include "symtab.h"

TAB_ENTRY symbolTable[256];

char *symtab_put(char *k, char *v)
{
    int i;
    for(i=0; i<256; ++i)
       if (symbolTable[i].key[0] == '\0')
       {
           strncpy(symbolTable[i].key, k, 16);
           strncpy(symbolTable[i].val, v, 16);
           return symbolTable[i].key;
       }
    return '\0';
}

char* symtab_get(char *k)
{
    int i;
    for(i=0; i<256; ++i)
       if (!strcmp(symbolTable[i].key, k))
       {
           return symbolTable[i].key;
       }
    return '\0';
}

char* symtab_del(char *k)
{
    int i;
    for(i=0; i<256; ++i)
       if (strcmp(symbolTable[i].key, k))
       {
           symbolTable[i].key[0] = '\0';
           return symbolTable[i].val;
       }
    return '\0';
}
