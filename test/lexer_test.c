#include "../src/include/lexer.h"
#include <assert.h>
#include <stddef.h>
#include <string.h>

void test_lexer_init() {
    char *content = "hello";
    Lexer *lexer = lexer_init(content);

    assert(lexer->content == content);
    assert(lexer->length == 5);
    assert(lexer->current == 'h');
    assert(lexer->position == 0);

    lexer_free(&lexer);
}

void test_lexer_free() {
    char *content = "hello";
    Lexer *lexer = lexer_init(content);

    lexer_free(&lexer);

    assert(lexer == NULL);
}

void test_lexer_lex() {
    char *content = "2.2 + 1 - 10 * 20 / (40.6 - 2.6) @";
    Lexer *lexer = lexer_init(content);

    Token *expectations[] = {
        token_init(TOKEN_NUMBER, "2.2"),    token_init(TOKEN_PLUS, "+"),
        token_init(TOKEN_NUMBER, "1"),      token_init(TOKEN_MINUS, "-"),
        token_init(TOKEN_NUMBER, "10"),     token_init(TOKEN_ASTERISK, "*"),
        token_init(TOKEN_NUMBER, "20"),     token_init(TOKEN_SLASH, "/"),
        token_init(TOKEN_OPEN_PAREN, "("),  token_init(TOKEN_NUMBER, "40.6"),
        token_init(TOKEN_MINUS, "-"),       token_init(TOKEN_NUMBER, "2.6"),
        token_init(TOKEN_CLOSE_PAREN, ")"), token_init(TOKEN_ILLEGAL, "@"),
        token_init(TOKEN_EOF, "\0")};
    int length = sizeof(expectations) / sizeof(Token *);

    Token **tokens = lexer_lex(lexer);

    for (int index = 0; index < length; index++) {
        Token *token = tokens[index];
        assert(token->type == expectations[index]->type);
        assert(strcmp(token->value, expectations[index]->value) == 0);
        token_free(&token);
        token_free(&expectations[index]);
    }

    lexer_free(&lexer);
}

int main() {
    test_lexer_init();
    test_lexer_free();
    test_lexer_lex();

    return 0;
}
