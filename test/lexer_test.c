#include "../src/include/lexer.h"
#include <assert.h>
#include <stddef.h>

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

int main() {
    test_lexer_init();
    test_lexer_free();

    return 0;
}
