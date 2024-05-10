#ifndef CORD_LEXER_H
#define CORD_LEXER_H

#include "token.h"
#include "error_codes.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
  char* buf;
  uint32_t buf_i;
  uint32_t buf_size;

  char c;
  
  Token*   tokens;
  uint32_t numTokens;

} Lexer;

Token* lexer_exec   (char* buf);
Lexer* create_lexer (char* buf);
void   free_lexer   (Lexer* lex);
LexerErrorCode lexer_create_tokens(Lexer* lex);

#endif