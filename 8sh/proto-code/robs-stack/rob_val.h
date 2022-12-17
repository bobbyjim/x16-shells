#ifndef _rob_val_h_
#define _rob_val_h_

typedef struct
{
	char type;
	enum {
	   STR* str;
	   long num;
	} as;
} VAL;

#endif
