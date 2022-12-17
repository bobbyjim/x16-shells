#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cbm.h>
#include <peekpoke.h>

#include "registers.h"
#include "interpreter.h"

uint8_t cmp_flag;

int interpret(VM *vm) // uint8_t *bytecode)
{
   uint16_t *memptr;
   uint8_t op;
   uint16_t val;
   optype ot;

   uint8_t *ip = vm->bytecode;
   uint16_t *r = vm->r;
 
   for(;;)
   {
      op = *ip; ++ip;
      ot = (optype) op;
      printf("op[%d] reg[%d] mod[%d]     ", ot.op, ot.reg, ot.mod);

      // 
      // Decode RValue
      // 
      if (ot.op > 0 && ot.mod < 4) val = r[ot.mod];
      else  // TODO: handle offset indirect modes
      {
         val = *ip; ++ip;
         val += 256 * *ip; ++ip;
      }

      switch(ot.op) 
      {
	case OP_OR:   printf("or\n");  r[ot.reg] |= val; break;
	case OP_AND:  printf("and\n"); r[ot.reg] &= val; break;
	case OP_CMP:  printf("cmp\n"); cmp_flag = (r[ot.reg] < val)? -1 : (r[ot.reg] > val); break;
	case OP_SUB:  printf("sub\n"); r[ot.reg] -= val; break;
	case OP_ADD:  printf("add\n"); r[ot.reg] += val; break;
	case OP_LOD:  printf("lod\n"); r[ot.reg] = val; break;
	//case OP_STO:  printf("sto\n"); break;
	case OP_SPECIAL:
		printf("special:\n");
		switch(ot.reg)
		{
		   case SPECIAL_ZOP:	printf("   zop\n");
			switch(ot.mod)
			{
                           case ZOP_NOP: printf("      nop\n"); break;
			   case ZOP_HCF: printf("      hcf\n"); exit(0); // break;
			   case ZOP_PUTREG: 
			   {
                              printf("      putreg\n");
			      printf("      a[%04x] b[%04x] c[%04x] d[%04x] f[%02x]\n", 
                                 r[0],r[1],r[2],r[3],cmp_flag); 

                              break;
 			   }
     			   case ZOP_PUTSTR:
			   {
			      memptr = &(r[0]);
			      printf("%X %s\n", memptr, *memptr);
			      break;
     			   }
			}
                        break;

		   case SPECIAL_JMP:	printf("   jmp\n");

			// first, calculate target address
			val = *ip; ++ip;
			val += 256 * *ip; ++ip;

			// now figure out what sort of jump we have
			switch(ot.mod)
			{
			   case JEQ: printf("      jeq\n"); if (cmp_flag==0) ip = val; break;
			   case JNE: printf("      jne\n"); if (cmp_flag!=0) ip = val; break;
			   case JLT: printf("      jlt\n"); if (cmp_flag< 0) ip = val; break;
			   case JLE: printf("      jle\n"); if (cmp_flag<=0) ip = val; break;
			   case JGT: printf("      jgt\n"); if (cmp_flag> 0) ip = val; break;
			   case JGE: printf("      jge\n"); if (cmp_flag>=0) ip = val; break;
			   case JMP: printf("      jmp\n"); ip = val; break;
			   default: return ERROR_UNKNOWN_OPCODE;
			}
                        break;

		   case SPECIAL_NOT:	printf("   not\n"); break;
		   default: return ERROR_UNKNOWN_OPCODE;
		}
		return SUCCESS;
		break;
	
         default: return ERROR_UNKNOWN_OPCODE;
      }
   }
   return SUCCESS; 
}
