#include "token.h"

const char* keywords[NUM_TOKEN_TYPES] = {
  "exit",
  NULL,
  NULL,
  NULL,
  "=",
  ";",
  "(",
  ")"
};

char* build_token (char* buf, char c) {
  buf = realloc(buf, 1*(sizeof(char) + 2));
  strcat(buf, strcat(&c, "\0"));

  return buf;
}