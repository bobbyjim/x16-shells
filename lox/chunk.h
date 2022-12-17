#ifndef chunk_h
#define chunk_h

#include "common.h"
#include "value.h"


#define   OP_HCF	0
#define   OP_CONSTANT	1
#define   OP_ADD	2	
#define   OP_SUBTRACT	3
#define   OP_MULTIPLY	4	
#define   OP_DIVIDE	5	
#define   OP_XOR        6
#define	  OP_POW	7
#define   OP_NEGATE	8
#define   OP_RETURN	9

typedef struct {
   uint16_t count;
   uint16_t capacity;
   uint8_t* code;
   uint16_t* lines; // embarrassingly inefficient with memory
   ValueArray constants;
} Chunk;

void initChunk(Chunk* chunk);
void freeChunk(Chunk* chunk);
void writeChunk(Chunk* chunk, uint8_t byte); //, uint16_t line);
uint16_t addConstant(Chunk* chunk, Value value);


#endif

