#include "token.h"
#include <stdio.h>
#include "debug.h"

char* keyword_strings[NUM_TOKEN_TYPES] = {
  "exit",
  NULL,
  NULL,
  NULL,
  "=",
  ";",
  "(",
  ")"
};

int (*char_check_func[NUM_GENERAL_TOKENS])(int) = {
  isalnum,
  isdigit,
};

Token* new_token (TokenType type, char* buf) {

  Token* tok = (Token*)malloc(sizeof(Token));
  tok->type = type;

  if (buf == NULL) {
    tok->val = keyword_strings[type];
  }
  else {
    tok->val = buf;
  }

  return tok;
}