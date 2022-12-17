#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "compiler.h"
#include "debug.h"
#include "vm.h"

VM vm; 

static void resetStack() {
   vm.stackTop = vm.stack;
}

void initVM() {
}

void freeVM() {
}

void push(Value value) {
  *vm.stackTop = value;
  vm.stackTop++;
}

Value pop() {
  vm.stackTop--;
  return *vm.stackTop;
}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
#define BINARY_OP(op) \
    do { \
      uint16_t b = pop(); \
      uint16_t a = pop(); \
      push(a op b); \
    } while (false)

  uint8_t instruction;
  Value* slot;

  for (;;) {

#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    
    for(slot = vm.stack; slot < vm.stackTop; ++slot) {
       printf("[ ");
       printValue(*slot);  
       printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk, (uint16_t)(vm.ip - vm.chunk->code));
#endif

    switch (instruction = READ_BYTE()) {

      case OP_CONSTANT: {
        Value constant = READ_CONSTANT();
        push(constant);
        break;
      }

      case OP_ADD:    BINARY_OP(+); break;
      case OP_SUBTRACT:    BINARY_OP(-); break;
      case OP_MULTIPLY:    BINARY_OP(*); break;
      case OP_DIVIDE:    BINARY_OP(/); break;
      case OP_NEGATE: push(-pop()); break;
      
      case OP_RETURN: {
        printValue(pop());
        printf("\n");
        return INTERPRET_OK;
      }

      case OP_HCF:
         exit(1);
    }
  }

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP
}

InterpretResult interpret(const char* source) {
   Chunk chunk;
   InterpretResult result;

   initChunk(&chunk);

   if (!compile(source, &chunk)) {
      freeChunk(&chunk);
      return INTERPRET_COMPILE_ERROR;
   }

   vm.chunk = &chunk;
   vm.ip = vm.chunk->code;
   
   result = run();

   freeChunk(&chunk);
   return result; //return INTERPRET_OK;
}

//InterpretResult interpret(Chunk* chunk) {
  //vm.chunk = chunk;
  //vm.ip = vm.chunk->code;
  //return run();
//}
