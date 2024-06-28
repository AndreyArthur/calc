#include "../src/include/ast.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void test_ast_string() {
    Ast *ast = (Ast *)ast_infix_init(
        (Ast *)ast_infix_init((Ast *)ast_number_init(34.567), "+",
                              (Ast *)ast_number_init(2)),
        "*", (Ast *)ast_prefix_init("-", (Ast *)ast_number_init(5)));

    char *string = ast_string(ast);

    assert(strcmp(string, "((34.567 + 2) * (-5))") == 0);

    ast_free(&ast);
    free(string);
}

void test_ast_free() {
    Ast *ast = (Ast *)ast_infix_init(
        (Ast *)ast_infix_init((Ast *)ast_number_init(34.567), "+",
                              (Ast *)ast_number_init(2)),
        "*", (Ast *)ast_prefix_init("-", (Ast *)ast_number_init(5)));

    ast_free(&ast);

    assert(ast == NULL);
}

int main() {
    test_ast_string();
    test_ast_free();

    return 0;
}
