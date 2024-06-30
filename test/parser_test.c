#include "../src/include/parser.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_parser_init() {
    Lexer *lexer = lexer_init("2 + 2");
    Token **tokens = lexer_lex(lexer);
    lexer_free(&lexer);
    Parser *parser = parser_init(tokens);

    assert(parser->tokens[0] == parser->current);
    assert(parser->length == 4);
    assert(parser->position == 0);
    assert(parser->current->type == TOKEN_NUMBER);
    assert(strcmp(parser->current->value, "2") == 0);

    parser_free(&parser);
}

void test_parser_free() {
    Lexer *lexer = lexer_init("2 + 2");
    Token **tokens = lexer_lex(lexer);
    lexer_free(&lexer);
    Parser *parser = parser_init(tokens);

    parser_free(&parser);

    assert(parser == NULL);
}

void test_parser_parse() {
    Lexer *lexer = lexer_init("(2 + 2 * 4) / (3 - 2)");
    Token **tokens = lexer_lex(lexer);
    lexer_free(&lexer);
    Parser *parser = parser_init(tokens);
    Ast *ast = parser_parse(parser);
    parser_free(&parser);

    char *string = ast_string(ast);
    ast_free(&ast);

    assert(strcmp(string, "((2 + (2 * 4)) / (3 - 2))") == 0);

    free(string);
}

int main() {
    test_parser_init();
    test_parser_free();
    test_parser_parse();

    return 0;
}
