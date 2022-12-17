#ifndef _SYMTAB_H_
#define _SYMTAB_H_

typedef struct {
    char key[16];
    char val[16];
} TAB_ENTRY;

char* symtab_put(char *k, char *v);
char* symtab_get(char *k);
char* symtab_del(char *k);

#endif
