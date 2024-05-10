#ifndef CORD_TOKEN_C
#define CORD_TOKEN_C

#include <stdlib.h>
#include <string.h>

typedef enum {
  TOKEN_EXIT,
  TOKEN_TYPE,
  TOKEN_ID_LITERAL,
  TOKEN_INT_LITERAL,
  TOKEN_EQUALS,
  TOKEN_SEMICOLON,
  TOKEN_LPAREN,
  TOKEN_RPAREN,

  NUM_TOKEN_TYPES
} TokenType;

extern const char* keywords[NUM_TOKEN_TYPES];

typedef struct
{
  TokenType type;
  char* val;
  /* TODO: uint32_t lineNum; ? */
} Token;

char* build_token (char* buf, char c);

#endif // !CORD_TOKEN_C
