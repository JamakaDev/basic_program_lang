#ifndef LEXER_H
#define LEXER_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "token.h"
#include "types.h"


typedef struct LEXER_STRUCT
{
    char   chr;
    uint64 idx;
    char* contents;

} Lexer;

Lexer* lexer_init(char* contents);

void   lexer_advance(Lexer* lexer);

Token* lexer_advance_with_token(Lexer* lexer, Token* token);

char* lexer_chr_to_string(Lexer* lexer);

Token* lexer_collect_id(Lexer* lexer);

Token* lexer_collect_integer(Lexer* lexer);

Token* lexer_collect_string(Lexer* lexer);

Token* lexer_get_next_token(Lexer* lexer);

void   lexer_skip_whitespace(Lexer* lexer);


#endif