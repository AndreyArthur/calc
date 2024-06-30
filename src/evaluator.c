#include "include/ast.h"

double eval(Ast *ast) {
    switch (ast->type) {
    case AST_NUMBER:
        return ((AstNumber *)ast)->value;
    case AST_PREFIX: {
        AstPrefix *prefix = (AstPrefix *)ast;
        double right = eval(prefix->right);
        switch (prefix->operation[0]) {
        case '-':
            return -right;
        default:
            return right;
        }
    }
    case AST_INFIX: {
        AstInfix *infix = (AstInfix *)ast;
        double left = eval(infix->left);
        double right = eval(infix->right);
        switch (infix->operation[0]) {
        case '+':
            return left + right;
        case '-':
            return left - right;
        case '*':
            return left * right;
        case '/':
            return left / right;
        default:
            return left + right;
        }
    }
    }

    return 0;
}
