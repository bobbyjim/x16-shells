
#include <stdint.h>

#include "rob_stack.h"
#include "bank.h"

uint8_t newStack(STACK* stack)
{
   stack->bank = ++topBank;
   setBank(stack->bank);
   bankputbyte(0,0);
   return topBank;
}

int top(STACK* stack)
{
   setBank(stack->bank);
   return bankgetbyte(0);
}

int elem(STACK* stack, int index, Value* value)
{
   setBank(stack->bank);
   value->type = bankgetbyte(index);
   
}

int push(STACK* stack, Value* value);
int pop(STACK* stack, Value* value);
int shift(STACK* stack, Value* value);
int unshift(STACK* stack, Value* value);
