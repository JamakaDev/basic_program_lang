#include "include\lexer.h"

static int isLexerContentNull(Lexer* lexer) {

  return (
    (lexer->chr == '\0') &&
    (lexer->idx >= strlen(lexer->contents))
  );
}

static int isWhiteSpaceOrNewLine(char chr) {

  return (
    (chr == ' ')  || 
    (chr == '\n')
  );

}

Lexer* lexer_init(char* contents) {

  Lexer* lexer = calloc(1, sizeof(Lexer));
  lexer->idx = 0;
  lexer->contents = contents;
  lexer->chr = contents[lexer->idx];
  
  return lexer;

}

void lexer_advance(Lexer* lexer) {

  if (!isLexerContentNull(lexer)) {
    
    lexer->idx += 1;
    lexer->chr = lexer->contents[lexer->idx];

  }
  
  return;

}

Token* lexer_advance_with_token(Lexer* lexer, Token* token) {

  lexer_advance(lexer);
  
  return token;

}

char* lexer_chr_to_string(Lexer* lexer) {

  char* str = calloc(2, sizeof(char));
  
  str[0] = lexer->chr;
  str[1] = '\0';
  
  return str;

}

Token* lexer_collect_id(Lexer* lexer) {

  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while (isalnum(lexer->chr)) {

    char* buffer = lexer_chr_to_string(lexer);
    value = realloc(value, (strlen(value) + strlen(buffer) + 1) * sizeof(char));
    strcat(value, buffer);
    lexer_advance(lexer);

  }
  
  return token_init(TOKEN_ID, value);

}

Token* lexer_collect_integer(Lexer* lexer) {

  char* value = calloc(1, sizeof(char));
  value[0] = '\0';
  while (isdigit(lexer->chr)) {

    char* buffer = lexer_chr_to_string(lexer);
    value = realloc(value, (strlen(value) + strlen(buffer) + 1) * sizeof(char));
    strcat(value, buffer);
    lexer_advance(lexer);

  }

  // lexer_advance(lexer);

  return token_init(TOKEN_INTEGER, value);
 
}

Token* lexer_collect_string(Lexer* lexer) {

  lexer_advance(lexer);

  char* value = calloc(1, sizeof(char));
  value[0] = '\0';

  while (lexer->chr != '"') {

    char* buffer = lexer_chr_to_string(lexer);
    value = realloc(value, (strlen(value) + strlen(buffer) + 1) * sizeof(char));
    strcat(value, buffer);
    lexer_advance(lexer);

  }

  lexer_advance(lexer);
  
  return token_init(TOKEN_STRING, value);

}

Token* lexer_get_next_token(Lexer* lexer) {

  while (!isLexerContentNull(lexer)) {

    if (isWhiteSpaceOrNewLine(lexer->chr))
      lexer_skip_whitespace(lexer);

    if (isdigit(lexer->chr))
      return lexer_collect_integer(lexer);

    if (isalnum(lexer->chr))
      return lexer_collect_id(lexer);
    
    if (lexer->chr == '"')
      return lexer_collect_string(lexer);

    switch (lexer->chr) {

      case ';': return lexer_advance_with_token(lexer, token_init(TOKEN_SEMI,   lexer_chr_to_string(lexer)));
      case ',': return lexer_advance_with_token(lexer, token_init(TOKEN_COMMA,  lexer_chr_to_string(lexer)));
      case '=': return lexer_advance_with_token(lexer, token_init(TOKEN_EQUALS, lexer_chr_to_string(lexer)));
      case '(': return lexer_advance_with_token(lexer, token_init(TOKEN_LPAREN, lexer_chr_to_string(lexer)));
      case ')': return lexer_advance_with_token(lexer, token_init(TOKEN_RPAREN, lexer_chr_to_string(lexer)));
      case '{': return lexer_advance_with_token(lexer, token_init(TOKEN_LBRACE, lexer_chr_to_string(lexer)));
      case '}': return lexer_advance_with_token(lexer, token_init(TOKEN_RBRACE, lexer_chr_to_string(lexer)));

    }

  }
  
  return token_init(TOKEN_EOF, "\0");

}

void lexer_skip_whitespace(Lexer* lexer) {

  while (isWhiteSpaceOrNewLine(lexer->chr)) {
    
    lexer_advance(lexer);

  }
  
  return;

}



