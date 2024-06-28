#include "include/lexer.h"
#include <stdlib.h>
#include <string.h>

Lexer *lexer_init(const char *content) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->content = content;
    lexer->length = strlen(content);
    lexer->position = 0;
    lexer->current = lexer->content[lexer->position];
    return lexer;
}

void lexer_free(Lexer **pointer) {
    free(*pointer);
    *pointer = NULL;
}
