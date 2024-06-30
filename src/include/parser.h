#ifndef PARSER_H
#define PARSER_H

#include "ast.h"
#include "lexer.h"
#include "token.h"

typedef struct {
    Token **tokens;
    Token *current;
    unsigned long position;
    unsigned long length;
} Parser;

Parser *parser_init(Lexer *lexer);

void parser_free(Parser **pointer);

Ast *parser_parse(Parser *parser);

#endif
