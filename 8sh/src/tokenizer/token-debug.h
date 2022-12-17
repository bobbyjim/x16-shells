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