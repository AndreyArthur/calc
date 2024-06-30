#ifndef LEXER_H
#define LEXER_H

#include "token.h"

typedef struct {
    const char *content;
    char current;
    unsigned long position;
    unsigned long length;
} Lexer;

Lexer *lexer_init(const char *content);

void lexer_free(Lexer **pointer);

Token **lexer_lex(Lexer *lexer);

#endif
