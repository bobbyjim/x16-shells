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
#ifndef _TOKEN_DEBUG_H
#define _TOKEN_DEBUG_H

//
//  These strings belong in a RAM bank
//  There's room for 256 strings at 32 bytes per string. 
//
#define TOKEN_NAME(i)     (tokenName[i])

char *tokenName[] = 
{
    "eof",
    "string",
    "number",
    "(",        // 3
    ")",
    "[",
    "]",
    ",",
    ".",
    "-",
    "+",
    ";",
    "/",
    "*",        // 13
    "!",
    "=",
    "==",
    ">",
    "<",
    "identifier",
    ":",        // 20
    "|",
    "`",        // left arrow
    "^",        // up
    "&",
    "$",
    "%",
    "mod",
    "..",       // 28
    "-=",
    "+=",
    "*=",
    "!=",
    ">=",
    "<=",
    "/=",
    "ne",       // 36
    "gt",
    "gte",
    "eq",
    "lte",
    "lt",
    "or",        // 42
    "if",
    "of",
    "and",
    "else",      // 46
    "",
    "return",
    "for",
    "fun",       // 50
    "nil",  
    "var",
    "while",
    "until",
    "break",
    "end block", // 56
    "",
    "",
    "size of var",  // 59
    "register",
    "print",
    "get time"
};

#define ERROR_TOKEN_NAME(i)     (errorTokenName[i-224])

char *errorTokenName[] = // token offset = 224
{
    "unterm. string",
    "unexpected char",
    "?no end of paren",
    "?no end of expr",
    "too many consts.",
    "expr'n expected",
    "';' expected",
    "expected varname"
};

#endif