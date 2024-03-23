#include "include\visitor.h"
#include "include\scope.h"

static AST* builtin_function_print(Visitor* visitor, AST** args, size_t args_size) {

  for (int i = 0; i < args_size; i++) {

    AST* node = visitor_visit(visitor, args[i]);

    // printf("\nINFO: %s\n", ast_type_to_str(node->type));
    switch (node->type) {
    
      case AST_STRING: printf("%s", node->string_value); break;
      case AST_INTEGER: printf("%d", node->integer_value); break;
      case AST_NOOPERATION: break;
      default: printf("%p\n", node); break;
    
    }

  }
  printf("\n");

  return ast_init(AST_NOOPERATION);

}

Visitor* visitor_init() {

  Visitor* visitor = calloc(1, sizeof(Visitor));

  return visitor;

}

AST* visitor_visit(Visitor* visitor, AST* node) { 
  // printf("type=%d\n", node->type);

  switch (node->type) {

    case AST_STRING:        return visitor_visit_string(visitor, node);
    case AST_INTEGER:       return node;
    case AST_COMPOUND:      return visitor_visit_compound(visitor, node);
    case AST_VARIABLE:      return visitor_visit_variable(visitor, node);
    case AST_VARIABLE_DEF:  return visitor_visit_variable_def(visitor, node);
    case AST_FUNCTION_DEF:  return visitor_visit_function_def(visitor, node);
    case AST_FUNCTION_CALL: return visitor_visit_function_call(visitor, node);
    case AST_NOOPERATION:   return node;

  }
  
  printf("Uncaught statement of type `%d`\n", node->type); 
  exit(EXIT_FAILURE);

  return ast_init(AST_NOOPERATION);

}

AST* visitor_visit_compound(Visitor* visitor, AST* node) {
  
  for (int i = 0; i < node->compound_size; i++) 
    visitor_visit(visitor, node->compound_value[i]);
  
  return ast_init(AST_NOOPERATION);

}

AST* visitor_visit_function_def(Visitor* visitor, AST* node) {
  
  scope_add_function_definition(node->scope, node);

  return node;

}

AST* visitor_visit_function_call(Visitor* visitor, AST* node) {

  // printf("\nvisit func call: %s\n", node->function_call_name);
  if (strcmp(node->function_call_name, "print") == SUCCESS) {
    return builtin_function_print(visitor, node->function_call_args, node->function_call_args_size);
  }
  AST* func_def = scope_get_function_definition(node->scope, node->function_call_name);

  if (func_def == NULL) {
    
    printf("Undefined method `%s`\n", node->function_call_name);
    exit(EXIT_FAILURE);

  }

  if (func_def->function_def_args_size != node->function_call_args_size) {

    printf("ERROR: function %s defines %d arguments and the function call %s contained %d | %s\n", 
            func_def->function_def_name, 
            func_def->function_def_args_size, 
            node->function_call_name,
            node->function_call_args_size,
            node->function_call_args[0]->string_value
          );
    exit(EXIT_FAILURE);
    
  }

  for (int i = 0; i < func_def->function_def_args_size; i++) {

    /* Obtain next variable & value each iteration */
    AST* this_var = func_def->function_def_args[i];
    AST* this_value = node->function_call_args[i];
    
    /* Create variable definition to be added to the scope */
    AST* var_def = ast_init(AST_VARIABLE_DEF);
    var_def->variable_def_name = calloc(strlen(this_var->variable_name) + 1, sizeof(char));
    
    /* Copy over the current variable definition's data */
    strcpy(var_def->variable_def_name, this_var->variable_name);
    var_def->variable_def_value = this_value;

    /* Adding the variable definition to the function's scope */
    scope_add_variable_definition(func_def->function_def_body->scope, var_def);

  }

  return visitor_visit(visitor, func_def->function_def_body);

}

AST* visitor_visit_string(Visitor* visitor, AST* node) {
  return node;
}

AST* visitor_visit_variable(Visitor* visitor, AST* node) {
  
  AST* var_def = scope_get_variable_definition(node->scope, node->variable_name);

  if (var_def == NULL) {
    
    printf("Undefined variable: `%s`\n", node->variable_name);
    exit(EXIT_FAILURE);

  }

  return visitor_visit(visitor, var_def->variable_def_value);

}

AST* visitor_visit_variable_def(Visitor* visitor, AST* node) {
  
  scope_add_variable_definition(node->scope, node);

  return node;

}

