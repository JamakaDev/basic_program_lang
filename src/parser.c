#include "include\parser.h"
#include "include\scope.h"

#define ef else if


Parser* parser_init(Lexer* lexer) {

  Parser* parser = calloc(1, sizeof(Parser));
  
  parser->lexer = lexer;
  parser->curr_token = lexer_get_next_token(lexer);
  parser->prev_token = parser->curr_token;
  parser->scope = scope_init();

  return parser;

}

AST* parser_eat(Parser* parser, int token_type) {

  if (parser->curr_token->type == token_type) {

    parser->prev_token = parser->curr_token;
    parser->curr_token = lexer_get_next_token(parser->lexer);

  }
  else {

    printf(
      "Unexpected token `%s`, with type %d\nExpected %s",
      parser->curr_token->value,
      parser->curr_token->type,
      token_type_to_str(token_type)
    );
    
    exit(EXIT_FAILURE);
    
  }
  return (AST*)0;
}

AST* parser_parse(Parser* parser, Scope* scope) {

  return parser_parse_statements(parser, parser->scope);

}

AST* parser_parse_id(Parser* parser, Scope* scope) {

  if (strcmp(parser->curr_token->value, "var") == SUCCESS) {
    return parser_parse_variable_def(parser, parser->scope);
  } 
  else if (strcmp(parser->curr_token->value, "func") == SUCCESS) {
    return parser_parse_function_def(parser, parser->scope);
  }
  return parser_parse_variable(parser, parser->scope);

}

AST* parser_parse_expression(Parser* parser, Scope* scope) {

  switch (parser->curr_token->type) {

    case TOKEN_ID:      return parser_parse_id(parser, parser->scope);
    case TOKEN_STRING:  return parser_parse_string(parser, parser->scope);
    case TOKEN_INTEGER: return parser_parse_integer(parser, parser->scope);
  
  }

  return ast_init(AST_NOOPERATION);

}

AST* parser_parse_factor(Parser* parser, Scope* scope) {

  return (void*)0;
}

AST* parser_parse_function_call(Parser* parser, Scope* scope) {

  AST* func_call = ast_init(AST_FUNCTION_CALL);
  func_call->function_call_name = parser->prev_token->value;
  func_call->function_call_args = calloc(1, sizeof(AST*));

  parser_eat(parser, TOKEN_LPAREN);
  
  AST* expression = parser_parse_expression(parser, parser->scope);
  if (expression->type != AST_NOOPERATION) {

    func_call->function_call_args[0] = expression;
    func_call->function_call_args_size += 1;

  }

  while (parser->curr_token->type == TOKEN_COMMA) {
    
    parser_eat(parser, TOKEN_COMMA);

    AST* expression = parser_parse_expression(parser, parser->scope);
    if (expression->type != AST_NOOPERATION) {

      func_call->function_call_args_size += 1;
      func_call->function_call_args = realloc(
                                              func_call->function_call_args,
                                              func_call->function_call_args_size * sizeof(AST*)
                                            );
      func_call->function_call_args[func_call->function_call_args_size-1] = expression;

    }

  }

  parser_eat(parser, TOKEN_RPAREN);

  func_call->scope = scope;

  return func_call;

}

AST* parser_parse_function_def(Parser* parser, Scope* scope) {

  AST* ast = ast_init(AST_FUNCTION_DEF);

  parser_eat(parser, TOKEN_ID); /* function keyword */

  char* function_name = parser->curr_token->value;
  ast->function_def_name = calloc(strlen(function_name)+1, sizeof(char));
  strcpy(ast->function_def_name, function_name);
  
  parser_eat(parser, TOKEN_ID); /* function name */
  
  parser_eat(parser, TOKEN_LPAREN); /* ( */
    
  if (parser->curr_token->type != TOKEN_RPAREN) {
    
    ast->function_def_args = calloc(1, sizeof(AST*));
    AST* arg = parser_parse_variable(parser, scope);
    ast->function_def_args[ast->function_def_args_size] = arg;
    ast->function_def_args_size += 1;

    while (parser->curr_token->type == TOKEN_COMMA) {
      
      parser_eat(parser, TOKEN_COMMA); /* , */

      ast->function_def_args_size += 1;

      ast->function_def_args = realloc(ast->function_def_args, ast->function_def_args_size * sizeof(AST*));
      
      AST* arg = parser_parse_variable(parser, scope);
      ast->function_def_args[ast->function_def_args_size - 1] = arg;

    }
    // printf("parser_parse_function_def(): Line %d\n", __LINE__); 

  }

  parser_eat(parser, TOKEN_RPAREN); /* ) */
  
  parser_eat(parser, TOKEN_LBRACE); /* { */

  ast->function_def_body = parser_parse_statements(parser, parser->scope);

  parser_eat(parser, TOKEN_RBRACE); /* } */

  ast->scope = scope;

  return ast;

}

AST* parser_parse_integer(Parser* parser, Scope* scope) {
  
  AST* integer = ast_init(AST_INTEGER);
  
  integer->integer_value = atoi(parser->curr_token->value);
  integer->scope = scope;

  parser_eat(parser, TOKEN_INTEGER);
  
  return integer;

}

AST* parser_parse_statement(Parser* parser, Scope* scope) {

  switch (parser->curr_token->type) {

    case TOKEN_ID: return parser_parse_id(parser, parser->scope);
  }

  return ast_init(AST_NOOPERATION);
}

AST* parser_parse_statements(Parser* parser, Scope* scope) {

  AST* compound = ast_init(AST_COMPOUND);
  compound->scope = scope;
  compound->compound_value = calloc(1, sizeof(AST*));
  
  AST* statement = parser_parse_statement(parser, parser->scope);
  statement->scope = scope;
  compound->compound_value[0] = statement;
  compound->compound_size += 1;
  
  while (parser->curr_token->type == TOKEN_SEMI) {
    
    parser_eat(parser, TOKEN_SEMI);

    AST* statement = parser_parse_statement(parser, parser->scope);

    if (statement) {
      compound->compound_size += 1;
      compound->compound_value = realloc(
          compound->compound_value, 
          compound->compound_size * sizeof(AST*)
      );
      compound->compound_value[compound->compound_size-1] = statement;
    }

  }


  return compound;

}

AST* parser_parse_string(Parser* parser, Scope* scope) {

  AST* ast_string = ast_init(AST_STRING);
  
  ast_string->string_value = parser->curr_token->value;
  ast_string->scope = scope;

  parser_eat(parser, TOKEN_STRING);
  
  return ast_string;

}

AST* parser_parse_term(Parser* parser, Scope* scope) {

  return (void*)0;
}

AST* parser_parse_variable(Parser* parser, Scope* scope) {

  char* token_value = parser->curr_token->value;

  parser_eat(parser, TOKEN_ID); /* var name or function call name*/

  if (parser->curr_token->type == TOKEN_LPAREN) 
    return parser_parse_function_call(parser, parser->scope);

  AST* ast_variable = ast_init(AST_VARIABLE);
  ast_variable->variable_name = token_value;
  ast_variable->scope = scope;

  return ast_variable;
}

AST* parser_parse_variable_def(Parser* parser, Scope* scope) {

  AST* var_def = ast_init(AST_VARIABLE_DEF);
  int variable_def_type = -1;
  parser_eat(parser, TOKEN_ID); /* var -> variable */

  if (strcmp(parser->curr_token->value, "int") == SUCCESS)
    variable_def_type = AST_INTEGER;
  ef (strcmp(parser->curr_token->value, "str") == SUCCESS)
    variable_def_type = AST_STRING;
  else
    variable_def_type = parser->curr_token->type;

  parser_eat(parser, TOKEN_ID); /* str -> string (variable type) */
  
  char* variable_def_name = parser->curr_token->value;
  parser_eat(parser, TOKEN_ID); /* variable name */
  
  parser_eat(parser, TOKEN_EQUALS);

  // printf("INFO: value=%-10s | type=%d\n", parser->curr_token->value, variable_def_type);
  var_def->variable_def_value = parser_parse_expression(parser, parser->scope);
  var_def->variable_def_name = variable_def_name;
  // variable_def_type == AST_STRING 
  //   ? printf("%s=%s\n",variable_def_name, var_def->variable_def_value->string_value) 
  //   : printf("%s=%d\n",variable_def_name, var_def->variable_def_value->integer_value);
  
  var_def->variable_def_value->type = variable_def_type;
  var_def->scope = scope;

  return var_def;
  
}


