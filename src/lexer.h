#ifndef CORD_LEXER_H
#define CORD_LEXER_H

#include "token.h"
#include "error_codes.h"
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
  char* buf;
  uint32_t buf_i;
  uint32_t buf_size;
  
  Token**  tokens;
  uint32_t numTokens;

  uint32_t lineNum;
  uint32_t linePos;

} Lexer;

Lexer* lexer_exec  (char* buf);
Lexer* lexer_alloc (char* buf);
void   lexer_free_buffer  (Lexer* lex);

LexerErrorCode lexer_create_tokens (Lexer* lex);

TokenErrorCode lexer_parse_token (Lexer* lex, GeneralTokenType type);

TokenErrorCode lexer_check_keyword_or_id( Lexer* lex, char *buf);
TokenErrorCode lexer_check_numeric (Lexer* lex, char *buf);

void lexer_parse_out_comment (Lexer* lex);

char lexer_peek_ahead (Lexer* lex, uint32_t offset);
void lexer_advance (Lexer* lex);

void lexer_add_token (Lexer* lex, TokenType type, char* id);

void lexer_free_token_strings (Lexer* lex);

#endif