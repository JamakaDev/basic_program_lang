#include <stdlib.h>

#include "include/token.h"



Token* token_init(int type, char* value) {

  Token* token = calloc(1, sizeof(Token));

  token->type = type;
  token->value = value;

  return token;

}

char* token_type_to_str(int type) {
  

  switch (type) {
    
    case TOKEN_ID:      return "ID";
    case TOKEN_SEMI:    return "SEMI";
    case TOKEN_COMMA:    return "COMMA";
    case TOKEN_EQUALS:  return "EQUALS";
    case TOKEN_STRING:  return "STRING";
    case TOKEN_LPAREN:  return "LPAREN";
    case TOKEN_RPAREN:  return "RPAREN";
    case TOKEN_INTEGER: return "INTEGER";
    case TOKEN_EOF:     return "EOF";

  }  

  return "UNKNOWN";

}