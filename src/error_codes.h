#ifndef CORD_ERROR_CODE_H
#define CORD_ERROR_CODE_H

typedef enum {
  COMPILER_SUCCESS,
  COMPILER_FILE_READ_ERROR,
  COMPILER_LEXER_TOKENIZE_ERROR,
  COMPILER_PARSER_ERROR,
  
  COMPILER_NUM_ERRORS
} CompilerErrorCode;

typedef enum {
  LEXER_SUCCESS,
  LEXER_FAIL_BAD_TOKEN,
  
  LEXER_ENUM_ERRORS
} LexerErrorCode;

extern const char* lexer_error_strings[LEXER_ENUM_ERRORS];

typedef enum {
  TOKEN_ERROR_NONE,
  TOKEN_ERROR_BAD_TOKEN,

  TOKEN_ERROR_FAILED_MEM,

  TOKEN_ENUM_ERRORS
} TokenErrorCode;

extern const char* token_error_strings[TOKEN_ENUM_ERRORS];

#endif
