/*
  
    AWK-8: an AWKlike program for 8 bit 'retro' systems.
    Copyright (C) 2021 Robert Eaglestone

    This file is part of AWK-8.

    AWK-8 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    AWK-8 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AWK-8.  If not, see <https://www.gnu.org/licenses/>.

*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <cx16.h>

#include "scanner.h"
#include "token-debug.h"

Token *current;

char   *scanner_start_position;    
char   *scanner_current_position;  
uint8_t scanner_line;              

int isAlnumdot(char c) 
{
   return isalnum(c) || c == '.' || c == 164; // 164 is PETSCII '_'
}

int isAtEnd() 
{
   return *scanner_current_position == '\0';
}

char advance() 
{
   return *(scanner_current_position++);
}

char match(char expected) 
{
  if (isAtEnd()) return 0;
  if (*scanner_current_position != expected) return 0;
  ++scanner_current_position;
  return 1;
}

char matchNotAlnum() {
  if (isAtEnd()) return 0;
  if (isalnum(*scanner_current_position)) return 0; 
  ++scanner_current_position;
  return *(scanner_current_position-1);
}

/************************************************************

 		makeToken: build a token of the given type at 
     the current token position.

*************************************************************/
TokenType makeToken(TokenType token_type)
{
   RAM_BANK = TOKEN_BANK;
   current->type = token_type;
   current->start_position = scanner_start_position;
   current->length = scanner_current_position - scanner_start_position;
   current->line = scanner_line;
   return token_type; 
}

TokenType errorToken(TokenType errorTokenType)
{
   makeToken(errorTokenType);
   current->start_position = 0;
   current->length = 0;
   return errorTokenType;
}

static TokenType checkKeyword(
		int start, 
		int length,
      const char* rest, 
		TokenType type)
{
  if (scanner_current_position - scanner_start_position == start + length 
   && memcmp(scanner_start_position+start,rest,length) == 0) {
    return type;
  }
  // else
  return TOKEN_IDENTIFIER;
}

static TokenType checkRelatedKeywords(
	int start, 
	int length, 
	const char* rest,
	TokenType type,
	TokenType typeMinusOne)
{
   TokenType t2 = checkKeyword(start,length,rest,type);

   printf("check related keywords:  %s\n", rest);

   if (t2 == TOKEN_IDENTIFIER)
      return checkKeyword(start,length-1,rest,typeMinusOne);
   
/*
  if (scanner_current_position - scanner_start_position == start + length 
	&& memcmp(scanner_start_position+start,rest,length) == 0) {
    return type;
  }
  else 
  if (scanner_current_position - scanner_start_position == start + length - 1
	&& memcmp(scanner_start_position+start,rest,length-1) == 0) {
    return typeMinusOne;
  }
  // else
  return TOKEN_IDENTIFIER;
  */
}

TokenType string(char terminator) 
{
  while (*scanner_current_position != terminator && !isAtEnd()) 
  {
    if (*scanner_current_position == '\n') 
       ++scanner_line;
    advance();
  }

  if (isAtEnd()) /*return*/ errorToken(TOKEN_ERROR_UNTERMINATED_STRING);

  // The closing quote.
  advance();
  return makeToken(TOKEN_STRING);
}

//
//  This alphabetical thing is of some type.  Find out what.
//
static TokenType identifierType()
{ 
   char c;

   switch (*scanner_start_position) 
   {
      case 'b': return checkKeyword(1, 4, "reak",  TOKEN_BREAK);
      case 'd': return checkKeyword(1, 3, "one",   TOKEN_ENDBLOCK); // "done"
      case 'e': 
	       if (checkKeyword(1, 3, "lse",   TOKEN_ELSE) == TOKEN_ELSE)
	          return TOKEN_ELSE;
  	     return checkKeyword(1, 1, "q", TOKEN_S_EQ);

      case 'f': return checkKeyword(1, 2, "or",    TOKEN_FOR);
      case 'g': return checkRelatedKeywords(1, 2, "te", TOKEN_S_GTE, TOKEN_S_GT);
      case 'i': return checkKeyword(1, 1, "f",     TOKEN_IF);
      case 'l': return checkRelatedKeywords(1, 2, "te", TOKEN_S_LTE, TOKEN_S_LT);
      
      case 'n': 
	       if (checkKeyword(1, 2, "il",    TOKEN_NIL) == TOKEN_NIL)
	          return TOKEN_NIL;
	       return checkKeyword(1, 1, "e", TOKEN_S_NE);

      case 'o': return checkKeyword(1, 1, "f",     TOKEN_OF);
      case 'p': return checkKeyword(1, 4, "rint",  TOKEN_PRINT);

      case 'q': c = matchNotAlnum(); // quote string
         if (c != 0) return string(c);
         break;

      case 'r': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
      case 's': return checkKeyword(1, 2, "ub",    TOKEN_FUN);
      case 't': return checkKeyword(1, 3, "ime",   TOKEN_GETTIME);

      case 'u': return checkKeyword(1, 4, "ntil",  TOKEN_UNTIL);
      case 'v': return checkKeyword(1, 2, "ar",    TOKEN_VAR);
      case 'w': return checkKeyword(1, 4, "hile",  TOKEN_WHILE);
  }
  return TOKEN_IDENTIFIER;
}

TokenType identifier() 
{
  while (isAlnumdot(*scanner_current_position)) 
     advance();

  return makeToken(identifierType());
}

TokenType dollarVariable() 
{
  char c = advance(); // advance to first character, which we've already checked.
  c = advance(); // now advance to next character.
  while (isAlnumdot(*scanner_current_position)) 
     advance();

  return makeToken(TOKEN_IDENTIFIER);
}

TokenType arraySize() 
{
   char c = advance(); // eat #
   c = advance();      // to first character.
   while (isAlnumdot(*scanner_current_position)) 
      advance();

   return makeToken(TOKEN_SIZE_OF_VAR);
}

TokenType number() 
{
  while (isdigit(*scanner_current_position)) 
     advance();

  // Look for a fractional part.
  if (*scanner_current_position == '.' && isdigit(*(scanner_current_position+1)) )
  {
    advance(); // consume the "."

    while (isdigit(*scanner_current_position)) 
       advance();
  }

  return makeToken(TOKEN_NUMBER);
}

/************************************************************

 		Scan a token

*************************************************************/
TokenType scanToken()
{
   char c;

   RAM_BANK = SOURCE_BANK;
  
   //skipWhitespace();
   while(isspace(*scanner_current_position)) 
      advance();
   if (*scanner_current_position == '#') // comment to EOL
      while(*scanner_current_position != '\n' && !isAtEnd()) 
         advance();

   scanner_start_position = scanner_current_position; 

   if (isAtEnd()) return makeToken(TOKEN_EOF);

   c = advance();

   if (isalpha(c)) return identifier();
   if (isdigit(c)) return number();

   //
   //  All the non-alpha non-digit stuff gets figured out here.
   //
   switch(c) 
   {
      // one-char tokens
      case '(': return makeToken(TOKEN_LEFT_PAREN);
      case ')': return makeToken(TOKEN_RIGHT_PAREN);
      case ':': return makeToken(TOKEN_COLON);
      case ';': return makeToken(TOKEN_SEMICOLON);
      case ',': return makeToken(TOKEN_COMMA);
      case '?': return makeToken(TOKEN_PRINT);
      case '^': return makeToken(TOKEN_UP);
      case '%': return makeToken(TOKEN_MOD);
      case PETSCII_LEFT_ARROW: return makeToken(TOKEN_ASSIGN);

      // strings
      case '"':  return string('"');
      case '\'': return string('\'');

      // potential two-char tokens
      case '=': return makeToken(match('=') ? TOKEN_EQUAL        : TOKEN_ASSIGN);
      case '!': return makeToken(match('=') ? TOKEN_BANG_EQUAL  	: TOKEN_BANG	);
      case '<': return makeToken(match('=') ? TOKEN_LESS_EQUAL  	: TOKEN_LESS	);
      case '>': return makeToken(match('=') ? TOKEN_GREATER_EQUAL 	: TOKEN_GREATER	);
      case '-': return makeToken(match('=') ? TOKEN_MINUS_EQUAL 	: TOKEN_MINUS 	);
      case '+': return makeToken(match('=') ? TOKEN_PLUS_EQUAL  	: TOKEN_PLUS	);
      case '*': return makeToken(match('=') ? TOKEN_STAR_EQUAL 		: TOKEN_STAR	);
      case '/': return makeToken(match('=') ? TOKEN_SLASH_EQUAL 	: TOKEN_SLASH 	);
      case '&': return makeToken(match('&') ? TOKEN_AND    		: TOKEN_AMP   	);
      case '.': return makeToken(match('.') ? TOKEN_DOT_DOT 		: TOKEN_DOT   	);
      case PETSCII_PIPE: return makeToken(match(PETSCII_PIPE)? TOKEN_OR : TOKEN_PIPE  	);

      // registers
      case PETSCII_SPADE:	return makeToken( TOKEN_REGISTER );
      case PETSCII_HEART:	return makeToken( TOKEN_REGISTER );
      case PETSCII_CLUB:	return makeToken( TOKEN_REGISTER );
      case PETSCII_DIAMOND:	return makeToken( TOKEN_REGISTER );

      // variables
      case '$': 
	       if (isalpha(*(scanner_current_position+1))) 
            return dollarVariable();
	       else
            return makeToken(TOKEN_DOLLAR);
    }
   return errorToken(TOKEN_ERROR_UNEXPECTED_CHAR);
}

/************************************************************

 		Scanner API

*************************************************************/
void initTokenDebug()
{
    //
    //  Load the TOKENS strings file.
    //
    //RAM_BANK = TOKEN_STRINGS_BANK;
    //cbm_k_setnam("tokens.bin");
    //cbm_k_setlfs(0,8,0);
    //cbm_k_load(0, 0xa000);
}

void initScanner() 
{
   RAM_BANK = TOKEN_BANK;
   current = ((Token *) 0xA000); // or wherever it should start
   current->type = 0;
   current->start_position = 0;
   current->length = 0;
   current->line = 0;

   scanner_start_position   = ((char *) 0xA000);  // or wherever it should start
   scanner_current_position = ((char *) 0xA000);  // or wherever it should start
   scanner_line             = 1;
}

void scan()
{
   int line = -1;
   initScanner();

   for (;;) 
   {
      TokenType type = scanToken();

      if (current->line != line) 
      {
         printf(" %3u ", current->line);
         line = current->line;
      }
      else
      {
         printf("   | ");
      }

      printf(" @   %x   :   %3d   %s\n", current, current->type, tokenName[current->type]);
//      printf(" @   %x   :   %3d\n", current, current->type);

      if (current->type == TOKEN_EOF) break;
      ++current; // advance to next token slot
   }
   printf(" scan done\n");
}

