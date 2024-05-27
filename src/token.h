#ifndef CORD_TOKEN_C
#define CORD_TOKEN_C

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
  TOKEN_EXIT,
  TOKEN_TYPE,
  TOKEN_ID,
  TOKEN_INT_LITERAL,
  TOKEN_EQUALS,
  TOKEN_SEMICOLON,
  TOKEN_LPAREN,
  TOKEN_RPAREN,

  NUM_TOKEN_TYPES
} TokenType;

typedef enum {
  TOKEN_ALPHANUM,
  TOKEN_NUM,

  NUM_GENERAL_TOKENS
} GeneralTokenType;

extern int (*char_check_func[NUM_GENERAL_TOKENS])(int);

extern char *keyword_strings[NUM_TOKEN_TYPES];

typedef struct
{
  TokenType type;
  char* val;
  /* TODO: uint32_t lineNum; ? */
} Token;

Token* new_token (TokenType type, char *buf);

#endif // !CORD_TOKEN_C
