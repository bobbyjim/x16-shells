#ifndef value_h
#define value_h

#include "common.h"

typedef uint16_t Value;
typedef unsigned char Byte;

typedef struct {
   uint16_t capacity;
   uint16_t count;
   Value* values;
} ValueArray;

void initValueArray(ValueArray* array);
void writeValueArray(ValueArray* array, Value value);
void freeValueArray(ValueArray* array);
void printValue(Value value);

#endif

