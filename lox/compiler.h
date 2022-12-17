#ifndef compiler_h
#define compiler_h

#include "vm.h"

bool compile(const char* source, Chunk* chunk);

#define TokenType uint8_t

#endif
