#include "include/token.h"
#include <assert.h>
#include <stdio.h>

int main() {
    Token *token = token_init(TOKEN_NUMBER, "24");
    printf("%d %s\n", token->type, token->value);
    token_free(&token);

    assert(token == NULL);
    return 0;
}
