#include "include/evaluator.h"
#include "include/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_input(int argc, char **argv) {
    int length = argc - 1;
    char **arguments = argv + 1;

    char *help_message =
        "Usage: calc '2 + 2'\nEvaluate math operations to standard output.\n\n "
        "   -h, --help display this message\n\nIf no argument is given, it "
        "opens a REPL.\n";

    if (length >= 2) {
        printf("%s", help_message);
        exit(1);
        return NULL;
    }

    if (length == 0) {
        return NULL;
    }

    char *argument = arguments[0];

    if (strcmp(argument, "-h") == 0 || strcmp(argument, "--help") == 0) {
        printf("%s", help_message);
        exit(0);
        return NULL;
    }

    return arguments[0];
}

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
    char *input = get_input(argc, argv);

    if (input == NULL) {
        repl();
    } else {
        printf("%lg\n", get_result(input));
    }

    return 0;
}
