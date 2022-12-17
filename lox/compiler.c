#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"
#include "vm.h"

typedef struct {
   Token current;
   Token previous;
   bool hadError;
   bool panicMode;
} Parser;

// Precendence Levels
#define PREC_NONE		0
#define PREC_ASSIGNMENT		1
#define	PREC_OR			2
#define PREC_AND		3
#define PREC_EQUALITY		4
#define PREC_COMPARISON		5
#define PREC_TERM		6
#define PREC_FACTOR		7
#define PREC_UNARY		8
#define PREC_CALL		9
#define PREC_PRIMARY		10

typedef void (*ParseFn)();

typedef struct {
   ParseFn prefix;
   ParseFn infix;
   uint8_t precedence;
} ParseRule;

Parser parser;

Chunk* compilingChunk;

static Chunk* currentChunk() {
   return compilingChunk;
}



static void errorAt(Token* token, const char* message) {
  if (parser.panicMode) return;
  parser.panicMode = true;
  //fprintf(stderr, "[line %d] Error", token->line);
  fprintf(stderr, "Error"); 

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing.
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.hadError = true;
}

static void error(const char* message) {
  errorAt(&parser.previous, message);
}

static void errorAtCurrent(const char* message) {
  errorAt(&parser.current, message);
}

static void advance() {
   parser.previous = parser.current;

   for(;;) {
      parser.current = scanToken();
      if (parser.current.type != TOKEN_ERROR) break;

      errorAtCurrent(parser.current.start);
   }
}

static void consume(int type, const char* message) {
   if (parser.current.type == type) {
      advance();
      return;
   }
   errorAtCurrent(message);
}

static void emitByte(uint8_t byte) {
   writeChunk(currentChunk(), byte); //, parser.previous.line);
}

static void emitBytes(uint8_t byte1, uint8_t byte2) {
  emitByte(byte1);
  emitByte(byte2);
}

static void emitReturn() {
  emitByte(OP_RETURN);
}

static uint8_t makeConstant(Value value) {
  int constant = addConstant(currentChunk(), value);
  if (constant > UINT8_MAX) {
    error("Too many constants in one chunk.");
    return 0;
  }

  return (uint8_t)constant;
}

static void emitConstant(Value value) {
  emitBytes(OP_CONSTANT, makeConstant(value));
}

static void endCompiler() {
   emitReturn();
}

/*
static void expression();
static ParseRule* getRule(uint8_t type);
static void parsePrecedence(uint8_t precedence);

static void binary() {
   int operatorType = parser.previous.type;
 
   ParseRule* rule = getRule(operatorType);
   parsePrecedence(rule->precedence+1);

   switch (operatorType) {
    case TOKEN_PLUS:          emitByte(OP_ADD); break;
    case TOKEN_MINUS:         emitByte(OP_SUBTRACT); break;
    case TOKEN_STAR:          emitByte(OP_MULTIPLY); break;
    case TOKEN_SLASH:         emitByte(OP_DIVIDE); break;
    case TOKEN_XOR:	      emitByte(OP_XOR); break;
    case TOKEN_POW:           emitByte(OP_POW); break;
    default:
      return; // Unreachable.
  }
}

static void grouping() {
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
}
*/

static void number() {
   int value = atoi(parser.previous.start); //, NULL); // danger!
   emitConstant(value);
}

/*
static void unary() {
  TokenType operatorType = parser.previous.type;

  // Compile the operand.
  parsePrecedence(PREC_UNARY);

  // Emit the operator instruction.
  switch (operatorType) {
    case TOKEN_MINUS: emitByte(OP_NEGATE); break;
    default:
      return; // Unreachable.
  }
}

static void parsePrecedence(uint8_t precedence) {
   advance();
  ParseFn prefixRule = getRule(parser.previous.type)->prefix;
  if (prefixRule == NULL) {
    error("Expect expression.");
    return;
  }

  prefixRule();

  while (precedence <= getRule(parser.current.type)->precedence) {
    advance();
    ParseFn infixRule = getRule(parser.previous.type)->infix;
    infixRule();
  }
}

static ParseRule* getRule(uint8_t type) {
   return &rules[type];
}

static void expression() {
   parsePrecedence(PREC_ASSIGNMENT);
}
*/

bool compile(const char* source, Chunk* chunk) {
  initScanner(source);
  compilingChunk = chunk;

  parser.hadError = false; 
  parser.panicMode = false;

  advance();
  //expression();
  consume(TOKEN_EOF, "Expect end of expression.");
  endCompiler();
  return !parser.hadError;
}

