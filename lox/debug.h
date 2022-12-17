#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
uint16_t disassembleInstruction(Chunk* chunk, uint16_t offset);

#endif
