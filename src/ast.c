#include "include\ast.h"

AST* ast_init(int type) {
  
  AST* ast = calloc(1, sizeof(AST));
  ast->type = type;

  /* AST Scope */
  ast->scope = NULL;

  /* AST_STRING */
  ast->string_value = NULL;
  
  /* AST_VARIABLE */
  ast->variable_name = NULL;

  /* AST_VARIABLE_DEF */
  ast->variable_def_name = NULL;
  ast->variable_def_value = NULL;
  
  /* AST_FUNCTION_DEF */
  ast->function_def_body = NULL;
  ast->function_def_name = NULL;
  ast->function_def_args = NULL;
  ast->function_def_args_size = 0;

  /* AST_FUNCTION_CALL */
  ast->function_call_name = NULL;
  ast->function_call_args = NULL;
  ast->function_call_args_size = 0;

  /* AST_COMPONUD */
  ast->compound_value = NULL;
  ast->compound_size = 0;

  return ast;  
  
}

char* ast_type_to_str(int type) {
  
  switch (type) {

    case AST_STRING:        return "STRING";
    case AST_COMPOUND:      return "COMPOUND";
    case AST_VARIABLE:      return "VARIABLE";
    case AST_VARIABLE_DEF:  return "VARIABLE_DEF";
    case AST_FUNCTION_CALL: return "FUNCTION_CALL";
    case AST_NOOPERATION:   return "NOOPERATION";


  }
  return "UNKNOWN";

}
