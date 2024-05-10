#include "lexer.h"

/**
 * @brief Takes in a raw uint8_t buffer from an input file
 *              and spits out a tokenized buffer from the input
 *
 * @param buf - Pointer to the buffer of raw uint8_ts from input file
 *
 * @return Token pointer to a buffer of tokens for parsing
 */
Token* lexer_exec (char* buf) {

  Lexer* lex = create_lexer(buf);

  LexerErrorCode lex_err = lexer_create_tokens(lex);

  if (lex_err != LEXER_SUCCESS) {
    fprintf(stderr, "%s: [%s]: Lexer Error Code %d\n", 
      __FILE__, __FUNCTION__, (uint32_t)lex_err);
  }

  Token* tokens = lex->tokens;
  free_lexer(lex);
  return tokens;
}

/**
 * @brief Creates and initializes the lexer object
 *
 * @param buf - Pointer to the buffer of raw chars from input file
 *
 * @return: Pointer to the Lexer object
 */
Lexer* create_lexer (char* buf) {
  Lexer* lex = (Lexer*) calloc(sizeof(Lexer), 1);
  lex->buf_i = 0;
  lex->buf = buf;
  lex->numTokens = 0;
  lex->buf_size = strlen(buf);
  lex->c = buf[lex->buf_i];

  return lex;
}

/**
 * @brief Frees all allocated data regarding Lexer object
 *
 * @param lex - pointer to Lexer object
 *
 * @return void
 */
void free_lexer (Lexer* lex) {
  free(lex->buf);
  lex->buf = NULL;
  /* Don't free tokens, need to pass it to parser. Still assign NULL ? */
  lex->tokens = NULL;
  free(lex);
  
}

/**
 * @brief Entry point for 
 *
 * @param lex - pointer to Lexer object
 *
 * @return LexerErrorCode - see error_codes.h
 */
LexerErrorCode lexer_create_tokens (Lexer* lex) {

  LexerErrorCode retCode = LEXER_SUCCESS;

  for (uint32_t i = 0; i < lex->buf_size; ++i) {
    if (isalpha(lex->c)) {
      
    }
  }

  return retCode;
}