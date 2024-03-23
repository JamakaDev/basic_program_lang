#ifndef TOKEN_H
#define TOKEN_H


typedef struct TOKEN_STRUCT
{
  char* value;
  
  enum {

    TOKEN_ID,
    TOKEN_SEMI,
    TOKEN_COMMA,
    TOKEN_EQUALS,
    TOKEN_STRING,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_INTEGER,
    TOKEN_EOF

  } type;


}Token;

Token* token_init(int type, char* value);
char*  token_type_to_str(int type);

#endif