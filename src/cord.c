#include "cord.h"
#include "file_util.h"
#include "lexer.h"
#include "debug.h"

CompilerErrorCode compile_cord_file (char* fileName) {
  CompilerErrorCode errorCode = COMPILER_SUCCESS;

  /* Create lexer/tokenizer, and pass in */
  Lexer* lex = lexer_exec (createBufFromFile(fileName));

  for (uint32_t i = 0; i < lex->numTokens; ++i) {
    printf("Token %d: %s - %s\n",
      i, lex->tokens[i]->val, debug_token_type_strings[lex->tokens[i]->type]);
  }

  lexer_free_token_strings (lex);
  free (lex);

  return errorCode;
}
