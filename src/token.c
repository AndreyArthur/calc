#include "include/token.h"
#include <stdlib.h>
#include <string.h>

Token *token_init(TokenType type, const char *value) {
    Token *token = malloc(sizeof(Token));
    token->type = type;
    token->value = strdup(value);
    return token;
}

void token_free(Token **pointer) {
    Token *token = *pointer;
    free(token->value);
    token->value = NULL;
    free(token);
    (*pointer) = NULL;
}
