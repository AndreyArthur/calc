#ifndef LEXER_H
#define LEXER_H

#include "token.h"
#include <stddef.h>

typedef struct {
    const char *content;
    char current;
    size_t position;
    size_t length;
} Lexer;

Lexer *lexer_init(const char *content);

void lexer_free(Lexer **pointer);

Token **lexer_lex(Lexer *lexer);

#endif
