#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct {
    Token **tokens;
    Token *current;
    size_t position;
    size_t length;
} Parser;

Parser *parser_init(Token **tokens);

void parser_free(Parser **pointer);

Ast *parser_parse(Parser *parser);

#endif
