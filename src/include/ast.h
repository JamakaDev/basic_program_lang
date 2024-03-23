#ifndef AST_H
#define AST_H

#include <stdlib.h>

typedef struct AST_STRUCT
{
  
  enum {

    AST_STRING,
    AST_INTEGER,
    AST_COMPOUND,
    AST_VARIABLE,
    AST_VARIABLE_DEF,
    AST_FUNCTION_DEF,
    AST_FUNCTION_CALL,
    AST_NOOPERATION

  } type;

  /* Scope for each AST node */
  struct SCOPE_STRUCT* scope;
  
  /* AST_COMPONUD */
  struct AST_STRUCT** compound_value;
  size_t compound_size;

  /* AST_FUNCTION_DEF */
  struct AST_STRUCT* function_def_body;
  char* function_def_name;
  struct AST_STRUCT** function_def_args;
  size_t function_def_args_size;
  
  /* AST_FUNCTION_CALL */
  char* function_call_name;
  struct AST_STRUCT** function_call_args;
  size_t function_call_args_size;
  
  /* AST_INTEGER */
  int integer_value;

  /* AST_STRING */
  char* string_value;

  /* AST_VARIABLE */
  char* variable_name;

  /* AST_VARIABLE_DEF */
  char* variable_def_name;
  char* variable_def_type;
  struct AST_STRUCT* variable_def_value;

} AST;

AST* ast_init(int type);
char* ast_type_to_str(int type);

#endif