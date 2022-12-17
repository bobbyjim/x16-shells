#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cbm.h>
#include <cx16.h>
#include <peekpoke.h>

#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

static void repl() {

   char line[80];
   for(;;) {
      printf("> ");
      
      if (!fgets(line,sizeof(line),stdin)) {
         printf("\n");
         break;
      }
      interpret(line);
   }
}

int main() { // int argc, char* argv[]) {

   cbm_k_bsout(0x8E); // revert to primary case
   printf("*** x16perl v0.0 ***");
   initVM();
   repl();
   freeVM();
}

