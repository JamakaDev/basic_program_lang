#include <stdio.h>
#include <string.h>
#include "include/scope.h"

#define SUCCESS 0

Scope* scope_init() {

  Scope* scope = calloc(1, sizeof(Scope));
  
  scope->function_definitions = NULL;
  scope->function_definitions_size = 0;
  
  scope->variable_definitions = NULL;
  scope->variable_definitions_size = 0;

  return scope;

}

AST* scope_add_function_definition(Scope* scope, AST* func_def) {

  scope->function_definitions_size += 1;

  if (scope->function_definitions == NULL) {

    scope->function_definitions = calloc(1, sizeof(AST*));

  }
  else {

    scope->function_definitions = realloc(scope->function_definitions, scope->function_definitions_size * sizeof(AST**));

  }

  scope->function_definitions[scope->function_definitions_size-1] = func_def;

  return func_def;

}

AST* scope_get_function_definition(Scope* scope, const char* func_name) {
  
  for (int i = 0; i < scope->function_definitions_size; i++) {
    
    AST* func_def = scope->function_definitions[i];

    if (strcmp(func_name, func_def->function_def_name) == SUCCESS)
      return func_def;

  }

  return NULL;

}

AST* scope_add_variable_definition(Scope* scope, AST* var_def) {

  scope->variable_definitions_size += 1;

  if (scope->variable_definitions == NULL) {
    
    scope->variable_definitions = calloc(1, sizeof(AST*));
    scope->variable_definitions[0] = var_def;

  } else {
    
    scope->variable_definitions = realloc(scope->variable_definitions, scope->variable_definitions_size * sizeof(AST*));
    scope->variable_definitions[scope->variable_definitions_size - 1] = var_def;

  }

  return var_def;

}

AST* scope_get_variable_definition(Scope* scope, const char* var_name) {

  for (int i = 0; i < scope->variable_definitions_size; i++) {
    
    AST* var_def = scope->variable_definitions[i];

    if (strcmp(var_name, var_def->variable_def_name) == SUCCESS)
      return var_def;

  }

  return NULL;

}
