#include "include\lexer.h"
#include "include\parser.h"
#include "include\visitor.h"
#include "include\io.h"


void printTokens(Lexer* lexer);

enum {
  PRGM_NAME,
  FILE_NAME
}ARGV;

int main(int argc, char* argv[]){

  char* file_contents = get_file_contents(argv[FILE_NAME]);
  
  Lexer* lexer = lexer_init(file_contents);

  
  // printTokens(lexer);

  Parser* parser = parser_init(lexer);
  AST* root_node = parser_parse(parser, parser->scope);
  Visitor* visitor = visitor_init();
  visitor_visit(visitor, root_node);

  
  return 0;

}


void printTokens(Lexer* lexer) {

  Token* token = lexer_get_next_token(lexer);

  while (token != NULL && token->type != TOKEN_EOF) {

    printf("TOKEN(%s, %s)\n", token_type_to_str(token->type), token->value);
    token = lexer_get_next_token(lexer);

  }

  return;
}