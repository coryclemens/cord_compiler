#include "lexer.h"
#include "debug.h"

/**
 * @brief Takes in a raw uint8_t buffer from an input file
 *              and spits out a tokenized buffer from the input
 *
 * @param buf - Pointer to the buffer of raw uint8_ts from input file
 *
 * @return Lexer pointer to a lexer containing buffer of tokens
 */
Lexer* lexer_exec (char* buf) {

  Lexer* lex = lexer_alloc(buf);

  LexerErrorCode lex_err = lexer_create_tokens(lex);

  if (lex_err != LEXER_SUCCESS) {
    fprintf(stderr, "%s: [%s]: Lexer Error Code %s\n", 
      __FILE__, __FUNCTION__, lexer_error_strings[(uint32_t)lex_err]);
  }

  lexer_free_buffer(lex);
  return lex;
}

/**
 * @brief Creates and initializes the lexer object
 *
 * @param buf - Pointer to the buffer of raw chars from input file
 *
 * @return: Pointer to the Lexer object
 */
Lexer* lexer_alloc (char* buf) {
  Lexer* lex = (Lexer*) calloc(1, sizeof(Lexer));
  lex->buf_i = 0;
  lex->buf = buf;
  lex->numTokens = 0;
  lex->buf_size = strlen(buf);
  lex->tokens = NULL;
  lex->lineNum = 1;
  lex->linePos = 1;

  return lex;
}

/**
 * @brief Frees the allocated buffer from the .cd file
 *
 * @param lex - pointer to Lexer object
 *
 * @return void
 */
void lexer_free_buffer (Lexer* lex) {
  free(lex->buf);
  lex->buf = NULL;
  /* Don't free tokens, need to pass it to parser. Still assign NULL ? */
}

/**
 * @brief Entry point for token creation. Determines what kind of token
 *        it could be (literal, id, keyword, symbol, whitespace etc) 
 *        and delegate appropriately.
 *
 * @param lex - pointer to Lexer object
 *
 * @return LexerErrorCode - see error_codes.h
 */
LexerErrorCode lexer_create_tokens (Lexer* lex) {

  LexerErrorCode lexerError = LEXER_SUCCESS;
  TokenErrorCode tokenError = TOKEN_ERROR_NONE;
  char current_char;

  while (lex->buf_i < lex->buf_size) {

    current_char = lex->buf[lex->buf_i];

    /* Check for keywords or just identifiers */
    if (isalpha(current_char)) {
      tokenError = lexer_parse_token(lex, TOKEN_ALPHANUM);
    }
    /* Check for integer literals */
    else if (isdigit(current_char)) {
      tokenError = lexer_parse_token(lex, TOKEN_NUM);
    }
    /* Check for non-graphical (space, newline, etc) */
    else if (!isgraph(current_char)) {
      lexer_advance(lex);

      if (current_char == '\n') {
        (lex->lineNum)++;
        (lex->linePos) = 1;
      }
    }
    /* Check for comments here */
    else if (current_char == '@') {
      lexer_parse_out_comment(lex);
    }
    else if (current_char == ';') {
      lexer_add_token(lex, TOKEN_SEMICOLON, NULL);
      lexer_advance(lex);
    }
    else if (current_char == '=') {
      lexer_add_token(lex, TOKEN_EQUALS, NULL);
      lexer_advance(lex);
    }

    if (tokenError != TOKEN_ERROR_NONE) {
      fprintf(stderr, "%s: [%s]: Token Creation Failure: %s\n", 
        __FILE__, __FUNCTION__, token_error_strings[tokenError]);
      lexerError = LEXER_FAIL_BAD_TOKEN;
      break;
    }
  }

  return lexerError;
}

/**
 * @brief Parses out int literals, ids, and keywords
 *
 * @param lex  - pointer to Lexer object
 * @param type - the kind of token we check for, numeric only, alphnum etc 
 *
 * @return TokenErrorCode - see error_codes.h
 */
TokenErrorCode lexer_parse_token (Lexer* lex, GeneralTokenType type) {
  char* temp_buf = NULL;
  unsigned int bufSize = 0;
  TokenErrorCode errorCode = TOKEN_ERROR_BAD_TOKEN;

  while (char_check_func[type](lexer_peek_ahead(lex, 0)) ||
        (type == TOKEN_ALPHANUM && lexer_peek_ahead(lex, 0) == '_')) {

    if (temp_buf == NULL) {

      /* Allocate for first char and \0 */
      temp_buf = (char*)calloc(2, sizeof(char));

      if (temp_buf != NULL) {
        temp_buf[0] = lex->buf[lex->buf_i];
        temp_buf[1] = '\0';
      }
      else {
        perror("lexer.c::lexer_parse_token(): calloc returned NULL.. \n");
        errorCode = TOKEN_ERROR_FAILED_MEM;
        break;
      }
    }
    else {
      bufSize = (uint32_t)strlen(temp_buf);

      temp_buf = realloc(temp_buf, bufSize + 2);

      if (temp_buf != NULL) {
        temp_buf[bufSize] = lex->buf[lex->buf_i];
        temp_buf[bufSize+1] = '\0';
      }
      else {
        perror("lexer.c::lexer_parse_token(): calloc returned NULL.. \n");
        errorCode = TOKEN_ERROR_FAILED_MEM;
        break;
      }
    }

    switch (type) {
      /* Check if keyword or an identifier */
      case TOKEN_ALPHANUM:
        errorCode = lexer_check_keyword_or_id(lex, temp_buf);
        break;

      /* Check for int literal */
      case TOKEN_NUM:
        errorCode = lexer_check_numeric(lex, temp_buf);
        break;

      default:
        perror("lexer.c::lexer_parse_token(): invalid 'type' in switch.. \n");
        break;
    }

    lexer_advance(lex);
  }

  if (errorCode != TOKEN_ERROR_NONE) {
    fprintf(stderr, "%s: [%s]: Token Creation Failure at %d:%d - \"%s%c\"\n", 
      __FILE__, __FUNCTION__, lex->lineNum, lex->linePos, 
      temp_buf, lexer_peek_ahead(lex, 1));
  }

  temp_buf = NULL;
  
  return errorCode;
}

/**
 * @brief Check for identifier or keyword. Token creation:
 *        - Keywords: we have a keyword match and next char is ' ' or ;
 *        - Identifiers: we don't have a keyword match and next is ' ' or ; 
 *
 * @param lex - pointer to Lexer object
 * @param buf - current temp buffer of the keyword or id we're building
 *
 * @return TokenErrorCode - see error_codes.h
 */
TokenErrorCode lexer_check_keyword_or_id (Lexer* lex, char* buf) {
  /* TODO: Set this error code for failures */
  TokenErrorCode errorCode = TOKEN_ERROR_NONE;

  /* Found a non-alphanumeric, try to process either a keyword or id */
  if ((!isalnum(lexer_peek_ahead(lex, 1))) &&
      (lexer_peek_ahead(lex, 1) != '_')) {

    if (strcmp(buf, keyword_strings[TOKEN_EXIT]) == 0) {
      lexer_add_token(lex, TOKEN_EXIT, NULL);
    }
    else if (strcmp(buf, "int") == 0) {
      lexer_add_token(lex, TOKEN_TYPE, buf);
    }
    else if (0 /* TODO: Add all keywords here */) {

    }
    else {
      /* Not a keyword, add as an identifier */
      lexer_add_token(lex, TOKEN_ID, buf);
    }
  }

  return errorCode;
}

/**
 * @brief Check for numerical literal.
 *        - Create token if next char is ' ' or ;
 *        - Fail token if next char is alphabetical
 *
 * @param lex - pointer to Lexer object
 * @param buf - current temp buffer of the keyword or id we're building
 *
 * @return TokenErrorCode - see error_codes.h
 */
TokenErrorCode lexer_check_numeric (Lexer* lex, char* buf) {
  /* TODO: Set this error code for failures */
  TokenErrorCode errorCode = TOKEN_ERROR_NONE;

  if (isalpha(lexer_peek_ahead(lex, 1))) {
    errorCode = TOKEN_ERROR_BAD_TOKEN;
  }
  else if (!isdigit(lexer_peek_ahead(lex, 1))) {
      lexer_add_token(lex, TOKEN_INT_LITERAL, buf);
  }

  return errorCode;
}

void lexer_parse_out_comment (Lexer* lex) {
  while ((lex->buf[lex->buf_i] != '\n') ||
        (lex->buf_i == lex->buf_size)) {
    lexer_advance(lex);
  }
}

char lexer_peek_ahead (Lexer* lex, uint32_t offset) {

  if (((lex->buf_i + offset) <= lex->buf_size) &&
      (lex->buf[lex->buf_i + offset] != '\0')) {
    return lex->buf[lex->buf_i + offset];
  }
  else {
    return (char)0;
  }
}

void lexer_advance (Lexer* lex) {

  if ((lex->buf_i <= lex->buf_size) &&
      (lex->buf[lex->buf_i] != '\0')) {
    (lex->buf_i)++;
    (lex->linePos)++;
  }
}

void lexer_add_token (Lexer* lex, TokenType type, char* id) {
  lex->numTokens++;

  Token* tok = new_token(type, id);

  lex->tokens = realloc(lex->tokens, lex->numTokens);

  lex->tokens[lex->numTokens-1] = tok;
}

void lexer_free_token_strings (Lexer* lex) {

  for (uint32_t i = 0; i < lex->numTokens; ++i) {
    #if DEBUG
      printf("%d ; %d: lex->tokens[i].type\n", i, lex->tokens[i]->type);
    #endif
    /* If a keyword string is null, means we allocated space for 
       a non keyword string, so free it. If its a keyword or symbol, 
       we just point to the string in keyword_strings */
    if (keyword_strings[lex->tokens[i]->type] == NULL) {
      free(lex->tokens[i]->val);
    }
  }

  free(lex->tokens);
}