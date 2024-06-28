#ifndef LEXER_H
#define LEXER_H

typedef struct {
    const char *content;
    char current;
    unsigned long position;
    unsigned long length;
} Lexer;

Lexer *lexer_init(const char *content);

void lexer_free(Lexer **pointer);

#endif
