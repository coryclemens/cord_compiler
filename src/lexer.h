#ifndef CORD_LEXER_H
#define CORD_LEXER_H

#include "token.h"
#include "error_codes.h"

typedef struct
{
  char* buf;
  int buf_i;
  Token* tokens;
  int numTokens;

} Lexer;

Token* lexer_exec   (char* buf);
Lexer* create_lexer (char* buf);
void   free_lexer   (Lexer* lex);
LexerErrorCode lexer_create_tokens(Lexer* lex);

#endif