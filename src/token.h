#ifndef CORD_TOKEN_C
#define CORD_TOKEN_C

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

typedef struct
{
  TokenType type;
  char* val;
  /* TODO: uint32_t lineNum; ? */
} Token;

#endif // !CORD_TOKEN_C
