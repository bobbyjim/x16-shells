#ifndef scanner_h
#define scanner_h

#define TOKEN_MINUS		0
#define TOKEN_PLUS		1
#define TOKEN_POW               2
#define TOKEN_SLASH		3
#define TOKEN_STAR		4
#define TOKEN_XOR		5

#define TOKEN_LEFT_PAREN 	16
#define TOKEN_RIGHT_PAREN 	17
#define TOKEN_COMMA		18
#define TOKEN_DOT		19
#define TOKEN_SEMICOLON		20
#define TOKEN_LEFT_BRACKET      21
#define TOKEN_RIGHT_BRACKET     22

#define TOKEN_BANG		32
#define TOKEN_BANG_EQUAL	33
#define TOKEN_EQUAL		34
#define TOKEN_EQUAL_EQUAL	35
#define TOKEN_GREATER		36
#define TOKEN_GREATER_EQUAL	37
#define TOKEN_LESS		38
#define TOKEN_LESS_EQUAL	39

#define TOKEN_IDENTIFIER	48
#define TOKEN_STRING		49
#define TOKEN_NUMBER		50

#define TOKEN_AND		64
#define TOKEN_CLASS		65
#define TOKEN_ELSE		66
#define TOKEN_FOR		67
#define TOKEN_FUN		68
#define TOKEN_IF		69
#define TOKEN_NIL		70
#define TOKEN_OR		71
#define TOKEN_PRINT		72
#define TOKEN_RETURN		73
#define TOKEN_SUPER		74
#define TOKEN_THIS		75
#define TOKEN_VAR		76
#define TOKEN_WHILE             77

#define TOKEN_ERROR		254
#define TOKEN_EOF		255



typedef struct {
  uint8_t type;
  uint8_t length;
//  uint16_t line;
  const char* start;
} Token;

void initScanner(const char* source);
Token scanToken();

#endif
