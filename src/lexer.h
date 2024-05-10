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
  
  Token*   tokens;
  uint32_t numTokens;

} Lexer;

Token* lexer_exec  (char* buf);
Lexer* lexer_alloc (char* buf);
void   lexer_free  (Lexer* lex);

LexerErrorCode lexer_create_tokens (Lexer* lex);
void lexer_parse_for_id (Lexer* lex);
void lexer_parse_for_digit (Lexer* lex);

char lexer_peek_ahead (Lexer* lex, uint32_t offset);
void lexer_advance (Lexer* lex);

#endif