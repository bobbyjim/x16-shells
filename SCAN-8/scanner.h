/*
  
    SCAN-8: a tokenizer for 8 bit systems.
    Copyright (C) 2021 Robert Eaglestone

    This file is part of SCAN-8.

    SCAN-8 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    SCAN-8 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with SCAN-8.  If not, see <https://www.gnu.org/licenses/>.

*/

#ifndef _scanner_h
#define _scanner_h

#include <stdint.h>

#define TokenType           uint8_t

#define SOURCE_BANK         2
#define TOKEN_BANK          3
#define TOKEN_STRINGS_BANK  4

//
//  Five byte token
//
typedef struct {
   TokenType type;
   uint8_t   length;
   char     *start_position;
   uint8_t   line;
} Token;

//
//  API
//
void        initTokenDebug();
void 		initScanner();
void 		scan();


#define PETSCII_LEFT_ARROW	95
#define PETSCII_PIPE    	221
#define	PETSCII_SPADE		193
#define	PETSCII_HEART		211
#define PETSCII_DIAMOND		218
#define PETSCII_CLUB		216


//
// This used to be "65", but I think 0 is better?
//
#define TOKEN_EOF               0
//
// Tokens with a length
//
#define TOKEN_STRING            1
#define TOKEN_NUMBER            2
//
//  one character length tokens
//
#define TOKEN_LEFT_PAREN        3
#define TOKEN_RIGHT_PAREN       4
#define TOKEN_LEFT_BRACE        5
#define TOKEN_RIGHT_BRACE       6
#define TOKEN_COMMA             7
#define TOKEN_DOT               8
#define TOKEN_MINUS             9
#define TOKEN_PLUS              10
#define TOKEN_SEMICOLON         11
#define TOKEN_SLASH             12
// 
#define TOKEN_STAR              13
#define TOKEN_BANG              14
#define TOKEN_ASSIGN            15
#define TOKEN_EQUAL             16
#define TOKEN_GREATER           17
#define TOKEN_LESS              18
#define TOKEN_IDENTIFIER        19
// 
#define TOKEN_COLON             20
#define TOKEN_PIPE		        21
#define TOKEN_LEFT_ARROW	    22
#define TOKEN_UP		        23
#define TOKEN_AMP               24
#define TOKEN_DOLLAR		    25
#define TOKEN_PERCENT		    26
#define TOKEN_MOD		        27
// 
#define TOKEN_DOT_DOT           28
#define TOKEN_MINUS_EQUAL       29
#define TOKEN_PLUS_EQUAL        30
#define TOKEN_STAR_EQUAL	    31
#define TOKEN_BANG_EQUAL        32
#define TOKEN_GREATER_EQUAL     33
#define TOKEN_LESS_EQUAL        34
#define TOKEN_SLASH_EQUAL	    35
// 
#define TOKEN_S_NE		        36
#define TOKEN_S_GT		        37
#define TOKEN_S_GTE		        38
#define TOKEN_S_EQ		        39
#define TOKEN_S_LTE		        40
#define TOKEN_S_LT		        41
//
#define TOKEN_OR                42
#define TOKEN_IF                43
#define TOKEN_OF 		        44
#define TOKEN_AND               45
//
#define TOKEN_ELSE              46
// 47
#define TOKEN_RETURN            48
#define TOKEN_FOR               49
//
#define TOKEN_FUN               50
#define TOKEN_NIL               51
#define TOKEN_VAR               52
#define TOKEN_WHILE             53
#define TOKEN_UNTIL		        54
#define TOKEN_BREAK             55
#define TOKEN_ENDBLOCK          56
//
// 57
// 58
//
#define TOKEN_SIZE_OF_VAR	    59
#define TOKEN_REGISTER		    60
// 
#define TOKEN_PRINT             61
#define TOKEN_GETTIME		    62
//
//
// --------------- ERROR TOKENS -------------------
//
#define TOKEN_START_OF_ERRORS			        224
//
#define TOKEN_ERROR_UNTERMINATED_STRING		    224
#define TOKEN_ERROR_UNEXPECTED_CHAR		        225
#define TOKEN_ERROR_EXPECT_END_PAREN            226
#define TOKEN_ERROR_EXPECT_END_OF_EXPR          227
#define TOKEN_ERROR_TOO_MANY_CONSTANTS          228
#define TOKEN_ERROR_EXPRESSION_EXPECTED         229
#define TOKEN_ERROR_SEMICOLON_EXPECTED		    230
#define TOKEN_ERROR_EXPECT_VARIABLE_NAME	    231
//
#define TOKEN_ERROR_HALT_CATCH_FIRE		        255

#endif
