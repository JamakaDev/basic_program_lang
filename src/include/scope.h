#ifndef SCOPE_H
#define SCOPE_H

#include "ast.h"

typedef struct SCOPE_STRUCT
{
  AST**  function_definitions;
  size_t function_definitions_size;

  AST**  variable_definitions;
  size_t variable_definitions_size;

}Scope;

Scope* scope_init();

AST* scope_add_function_definition(Scope* scope, AST* func_def);

AST* scope_get_function_definition(Scope* scope, const char* func_name);

AST* scope_add_variable_definition(Scope* scope, AST* var_def);

AST* scope_get_variable_definition(Scope* scope, const char* var_name);

#endif