#ifndef _hash_h
#define _hash_h

#include <stdint.h>
#include <stdbool.h>

#include "str.h"

#define FILLPCT 70

typedef struct hentry PHASH_ENTRY;
typedef struct htbl PERL_HASH;

typedef struct hentry {
   PHASH_ENTRY* hent_next;
   char* hent_key;
   STR*  hent_val;
   uint16_t hent_hash;
};

typedef struct htbl {
   PHASH_ENTRY** tbl_array;
   int    tbl_max;
   int    tbl_fill;
//   int    tbl_riter;  // current root of iterator
//   PHASH_ENTRY*  tbl_either; // current entry of iterator
};

PERL_HASH* hnew();
STR*  hfetch(PERL_HASH* tb, char* key);
void  hsplit(PERL_HASH* tb);
bool  hstore(PERL_HASH* tb, char* key, STR* val);

/*
STR*  hdelete(PERL_HASH* tb);
void  hclear();
void  hfree();
void  hentfree();
*/

//int   hiterinit();
//PHASH_ENTRY* hiternext();
//char* hiterkey();
//STR*  hiterval();

#define COEFFSIZE (16 * 8)      /* size of array below */
static char coeff[] = {
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1,
                61,59,53,47,43,41,37,31,29,23,17,13,11,7,3,1};

#endif

