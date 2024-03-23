#ifndef VISITOR_H
#define VISITOR_H
#include "ast.h"
#include "lexer.h"

typedef struct VISITOR_STRUCT {
  
}Visitor;

Visitor* visitor_init();

AST* visitor_visit(Visitor* visitor, AST* node);

AST* visitor_visit_compound(Visitor* visitor, AST* node);

AST* visitor_visit_function_def(Visitor* visitor, AST* node);

AST* visitor_visit_function_call(Visitor* visitor, AST* node);

AST* visitor_visit_string(Visitor* visitor, AST* node);

AST* visitor_visit_variable(Visitor* visitor, AST* node);

AST* visitor_visit_variable_def(Visitor* visitor, AST* node);

#endif