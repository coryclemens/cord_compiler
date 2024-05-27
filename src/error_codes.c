#include "error_codes.h"

const char* lexer_error_strings[LEXER_ENUM_ERRORS] = {
  "LEXER_SUCCESS",
  "LEXER_FAIL_BAD_TOKEN"
};

const char* token_error_strings[TOKEN_ENUM_ERRORS] = {
  "TOKEN_ERROR_NONE",
  "TOKEN_ERROR_BAD_TOKEN",
  "TOKEN_ERROR_FAILED_MEM"
};