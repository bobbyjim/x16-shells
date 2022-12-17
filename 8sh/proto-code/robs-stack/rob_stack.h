#ifndef _rob_stack_h_
#define _rob_stack_h_

#include <stdint.h>

typedef struct
{
   uint8_t bank;
} STACK;

uint8_t topBank = 19;

uint8_t newStack(STACK* stack);
int top(STACK* stack, Value* value);
int elem(STACK* stack, uint8_t index, Value* value);
int push(STACK* stack, Value* value);
int pop(STACK* stack, Value* value);
int shift(STACK* stack, Value* value);
int unshift(STACK* stack, Value* value);

#endif
