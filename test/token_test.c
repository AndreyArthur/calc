#include "../src/include/token.h"
#include <assert.h>
#include <string.h>

void test_token_init() {
    char value[1] = "\0";
    TokenType type = TOKEN_EOF;
    Token *token = token_init(type, value);

    assert(token->type == type);
    assert(memcmp(token->value, value, 1) == 0);

    token_free(&token);
}

void test_token_free() {
    Token *token = token_init(TOKEN_EOF, "\0");
    token_free(&token);

    assert(token == NULL);
}

int main() {
    test_token_init();
    test_token_free();

    return 0;
}
