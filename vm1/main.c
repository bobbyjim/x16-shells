//
//  Ideas stolen from 
//  http://c-jump.com/CIS77/CPU/IsaDesign/lecture.html
//
//
//
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <cbm.h>
#include <peekpoke.h>

#define	OP_SPECIAL		0
#define OP_OR 			1
#define OP_AND			2
#define OP_CMP  		3
#define OP_SUB 			4
#define OP_ADD			5
#define OP_LOD 			6
#define OP_STO			7

#define REG_A 			0	// LOD into these
#define REG_B 			1
#define REG_C 			2 
#define REG_D 			3 

#define MEM_A 			0	// STO into these
#define MEM_B 			1 
#define MEM_C 			2 
#define MEM_D 			3 
#define MEM_BIND		4  
#define MEM_BOFFSIND		5  
#define MEM_OFFSIND		6  
#define MEM_CONSTANT		7  

#define SPECIAL_ZOP		0	// 000 Opcodes
#define SPECIAL_JMP		1
#define SPECIAL_NOT		2 
#define SPECIAL_ILLEGAL		3 

#define ZOP_ILLEGAL0		0	// Zero Operand Instructions
#define ZOP_ILLEGAL1		1 
#define ZOP_ILLEGAL2		2 
#define ZOP_HCF			3 	// Halt, Catch Fire
#define ZOP_ILLEGAL4		4  
#define ZOP_ILLEGAL5		5  
#define ZOP_PUTREG		6       // display register values
#define ZOP_PUTSTR		7       // prints string referenced from A (null terminated)

#define JEQ			0	// Special Jumps
#define JNE			1
#define JLT			2
#define JLE			3
#define JGT			4
#define JGE			5
#define JMP			6
#define JUMP_ILLEGAL		7


#define	SUCCESS			0
#define	ERROR_UNKNOWN_OPCODE	1

uint16_t r[4]; // our registers

uint8_t *ip;
uint16_t *sp;
uint8_t *bytecode;
uint8_t cmp_flag;

typedef struct {
	int op: 3;
	int reg: 2;
	int mod: 3;
} optype;

int interpret() // uint8_t *bytecode)
{
   uint16_t *memptr;

   uint8_t op;
   uint16_t val;
   optype ot;
 
   ip = bytecode;
  
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
			   case ZOP_HCF: printf("      hcf\n"); break;
			   case ZOP_PUTREG: 
			   {
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


int main() 
{
   uint8_t program[20];

   cbm_k_bsout(0x8E); // revert to primary case
   printf("*** x16perl v0.0 ***\n\n");   

   program[0]  = OP_LOD		+ 8*REG_A		+ 32*MEM_CONSTANT;
   program[1]  = 80;
   program[2]  = 0;
   program[3]  = OP_LOD          + 8*REG_B 		+ 32*MEM_CONSTANT;
   program[4]  = 1;
   program[5]  = 2;
   program[6]  = OP_CMP          + 8*REG_A               + 32*REG_B;
   program[9]  = OP_SPECIAL	+ 8*SPECIAL_ZOP 	+ 32*ZOP_PUTREG;
   program[7]  = OP_ADD		+ 8*REG_A		+ 32*REG_B;
   program[8]  = OP_CMP          + 8*REG_A               + 32*REG_B;
   program[9]  = OP_SPECIAL	+ 8*SPECIAL_ZOP 	+ 32*ZOP_PUTREG;
   program[10] = OP_SPECIAL	+ 8*SPECIAL_ZOP		+ 32*ZOP_HCF;

   bytecode = program;

   interpret();

   return 0;
}

