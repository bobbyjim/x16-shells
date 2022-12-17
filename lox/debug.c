#include <stdio.h>

#include "debug.h"
#include "value.h"
#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name) {
  uint16_t offset;

  printf("== %s ==\n", name);

  for (offset = 0; offset < chunk->count;) {
    offset = disassembleInstruction(chunk, offset);
  }
}

static uint16_t constantInstruction(const char* name, Chunk* chunk,
                               uint16_t offset) {
  uint8_t constant = chunk->code[offset + 1];
  printf("%-16s %4d '", name, constant);
  printValue(chunk->constants.values[constant]);
  printf("'\n");
  return offset+2;
}

static uint16_t simpleInstruction(const char* name, uint16_t offset) {
   printf("%s\n", name);
   return offset+1;
}

uint16_t disassembleInstruction(Chunk* chunk, uint16_t offset) {
   uint8_t instruction = chunk->code[offset];

   printf( "%04d ", offset );
   /*
   if (offset > 0 && chunk->lines[offset] == chunk->lines[offset-1]) {
     printf("   | ");
   } else {
     printf("%4d ", chunk->lines[offset]);
   }
   */
   
   switch(instruction) {
      case OP_CONSTANT:
         return constantInstruction("op_constant", chunk , offset);
      case OP_ADD:
         return simpleInstruction("op_add", offset);
      case OP_SUBTRACT:
         return simpleInstruction("op_sub", offset);
      case OP_MULTIPLY:
         return simpleInstruction("op_mul", offset);
      case OP_DIVIDE:
         return simpleInstruction("op_div", offset);
      case OP_NEGATE:
         return simpleInstruction("op_negate", offset);
      case OP_RETURN:
         return simpleInstruction("op_return", offset);
      case OP_HCF:
         return simpleInstruction("op_hcf", offset);
         
      default:
         printf("unknown opcode %d\n", instruction);
         return offset+1;
   }
}
