
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "phash.h"
#include "str.h"
#include "util.h"


PERL_HASH* hnew()
{
   PERL_HASH* tb = (PERL_HASH*) malloc(sizeof(PERL_HASH));
   
   tb->tbl_array = (PHASH_ENTRY**) malloc(8 * sizeof(PHASH_ENTRY*));
   tb->tbl_fill = 0;
   tb->tbl_max  = 7;
//   hiterint(tb);  // so each() will start off right
   bzero((char*)tb->tbl_array, 8 * sizeof(PHASH_ENTRY*));
   return tb;
}

uint16_t calcHash(char* key)
{
   char* s;
   uint16_t hash;
   int i;
   for (s=key,	i=0,	hash=0;
     /* while */ *s && i < COEFFSIZE;
	++s,	++i,	hash *= 5) {
      hash += *s * coeff[i];
   }
   return hash;
}

STR* hfetch(PERL_HASH* tb, char* key)
{
   uint16_t hash;
   PHASH_ENTRY* entry;
 
   if (!tb) return Nullstr;
   hash = calcHash(key);
   entry = tb->tbl_array[hash & tb->tbl_max];
   for(; entry; entry = entry->hent_next) {
      if (entry->hent_hash != hash) // strings cannot be equal
         continue;
      if (strcmp(entry->hent_key, key)) // is this it?
         continue;
      return entry->hent_val;
   }
   return Nullstr;
}

void hsplit(PERL_HASH* tb)
{
    int oldsize = tb->tbl_max + 1;
    int newsize = oldsize * 2;
    int i;
    PHASH_ENTRY **a;
    PHASH_ENTRY **b;
    PHASH_ENTRY *entry;
    PHASH_ENTRY **oentry;

    a = (PHASH_ENTRY**) realloc((char*)tb->tbl_array, newsize * sizeof(PHASH_ENTRY*));
    bzero((char*)&a[oldsize], (newsize - oldsize) * sizeof(PHASH_ENTRY*)); /* zero second half */
    tb->tbl_max = --newsize;
    tb->tbl_array = a;

    for (i=0; i<oldsize; ++i,++a) {
        if (!*a)                                /* non-existent */
            continue;
        b = a+oldsize;
        for (oentry = a, entry = *a; entry; entry = *oentry) {
            if ((entry->hent_hash & newsize) != i) {
                *oentry = entry->hent_next;
                entry->hent_next = *b;
                if (!*b)
                    tb->tbl_fill++;
                *b = entry;
                continue;
            }
            else
                oentry = &entry->hent_next;
        }
        if (!*a)                                /* everything moved */
            tb->tbl_fill--;
    }
}

bool hstore(PERL_HASH* tb, char* key, STR* val)
{
   int i;
   uint16_t hash;
   PHASH_ENTRY* entry;
   PHASH_ENTRY** oentry;

   if (!tb) return false;
   hash = calcHash(key);
   oentry = &(tb->tbl_array[hash & tb->tbl_max]);
   i = 1;
   for (entry = *oentry; entry; i=0, entry = entry->hent_next) {
        if (entry->hent_hash != hash)           /* strings can't be equal */
            continue;
        if (strcmp(entry->hent_key,key)) /* is this it? */
            continue;
        free((char*)entry->hent_val);
        entry->hent_val = val;
        return true;
    }
    entry = (PHASH_ENTRY*) malloc(sizeof(PHASH_ENTRY));

    entry->hent_key = savestr(key);
    entry->hent_val = val;
    entry->hent_hash = hash;
    entry->hent_next = *oentry;
    *oentry = entry;

    if (i) {                            /* initial entry? */
        tb->tbl_fill++;
        if ((tb->tbl_fill * 100 / (tb->tbl_max + 1)) > FILLPCT)
            hsplit(tb);
    }

    return false;
}

