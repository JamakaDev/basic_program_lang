#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "ast.h"
#include "scope.h"


typedef struct PARSER_STRUCT {
  
  Lexer* lexer;
  Token* curr_token;
  Token* prev_token;
  Scope* scope;

}Parser;

Parser* parser_init(Lexer* lexer);

AST* parser_eat(Parser* parser, int token_type);

AST* parser_parse(Parser* parser, Scope* scope);

AST* parser_parse_id(Parser* parser, Scope* scope);

AST* parser_parse_expression(Parser* parser, Scope* scope);

AST* parser_parse_factor(Parser* parser, Scope* scope);

AST* parser_parse_function_call(Parser* parser, Scope* scope);

AST* parser_parse_function_def(Parser* parser, Scope* scope);

AST* parser_parse_integer(Parser* parser, Scope* scope);

AST* parser_parse_statement(Parser* parser, Scope* scope);

AST* parser_parse_statements(Parser* parser, Scope* scope);

AST* parser_parse_string(Parser* parser, Scope* scope);

AST* parser_parse_term(Parser* parser, Scope* scope);

AST* parser_parse_variable(Parser* parser, Scope* scope);

AST* parser_parse_variable_def(Parser* parser, Scope* scope);


#endif