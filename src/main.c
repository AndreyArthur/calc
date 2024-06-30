#include "include/evaluator.h"
#include "include/parser.h"
#include <stdio.h>

double get_result(const char *content) {
    Lexer *lexer = lexer_init(content);
    Token **tokens = lexer_lex(lexer);
    lexer_free(&lexer);

    Parser *parser = parser_init(tokens);
    Ast *ast = parser_parse(parser);
    parser_free(&parser);

    double result = eval(ast);
    ast_free(&ast);

    return result;
}

void repl() {
    printf("Welcome to the calc REPL! Type in math expressions.\n");

    for (;;) {
        printf(">> ");

        char buffer[1024];

        scanf(" %1023[^\n]", buffer);

        printf("%lg\n", get_result(buffer));
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        repl();
        return 0;
    }

    printf("%lg\n", get_result(argv[1]));

    return 0;
}
