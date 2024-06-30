#include "../src/include/evaluator.h"
#include "../src/include/lexer.h"
#include "../src/include/parser.h"
#include "../src/include/token.h"
#include <assert.h>

void test_eval() {
    Lexer *lexer = lexer_init("(2 + 2 * 4) / (3 - -2)");
    Token **tokens = lexer_lex(lexer);
    lexer_free(&lexer);
    Parser *parser = parser_init(tokens);
    Ast *ast = parser_parse(parser);
    parser_free(&parser);

    double evaluated = eval(ast);
    ast_free(&ast);

    assert(evaluated == 2);
}

int main() {
    test_eval();

    return 0;
}
