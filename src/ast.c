#include "include/ast.h"
#include "include/buffer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ast_free(Ast **pointer) {
    switch ((*pointer)->type) {
    case AST_NUMBER:
        return ast_number_free((AstNumber **)pointer);
    case AST_PREFIX:
        return ast_prefix_free((AstPrefix **)pointer);
    case AST_INFIX:
        return ast_infix_free((AstInfix **)pointer);
    }
}

char *ast_string(Ast *ast) {
    switch (ast->type) {
    case AST_NUMBER:
        return ast_number_string((AstNumber *)ast);
    case AST_PREFIX:
        return ast_prefix_string((AstPrefix *)ast);
    case AST_INFIX:
        return ast_infix_string((AstInfix *)ast);
    default:
        return NULL;
    }
}

AstNumber *ast_number_init(double value) {
    AstNumber *ast_number = malloc(sizeof(AstNumber));
    ast_number->type = AST_NUMBER;
    ast_number->value = value;
    return ast_number;
}

void ast_number_free(AstNumber **pointer) {
    free(*pointer);
    *pointer = NULL;
}

char *ast_number_string(AstNumber *ast_number) {
    char buffer[128];
    sprintf(buffer, "%lg", ast_number->value);
    int length = strlen(buffer);
    char *string = malloc(length + 1);
    strcpy(string, buffer);
    return string;
}

AstPrefix *ast_prefix_init(const char *operation, Ast *right) {
    AstPrefix *ast_prefix = malloc(sizeof(AstPrefix));
    ast_prefix->type = AST_PREFIX;
    ast_prefix->operation = strdup(operation);
    ast_prefix->right = right;
    return ast_prefix;
}

void ast_prefix_free(AstPrefix **pointer) {
    free((*pointer)->operation);
    ast_free(&(*pointer)->right);
    free(*pointer);
    *pointer = NULL;
}

char *ast_prefix_string(AstPrefix *ast_prefix) {
    Buffer *buffer = buffer_init();

    buffer_write_char(buffer, '(');
    buffer_write_string(buffer, ast_prefix->operation);
    char *right_string = ast_string(ast_prefix->right);
    buffer_write_string(buffer, right_string);
    free(right_string);
    buffer_write_char(buffer, ')');

    char *string = buffer_into_string(buffer);
    return string;
}

AstInfix *ast_infix_init(Ast *left, const char *operation, Ast *right) {
    AstInfix *ast_infix = malloc(sizeof(AstInfix));
    ast_infix->type = AST_INFIX;
    ast_infix->left = left;
    ast_infix->operation = strdup(operation);
    ast_infix->right = right;
    return ast_infix;
}

void ast_infix_free(AstInfix **pointer) {
    ast_free(&(*pointer)->left);
    ast_free(&(*pointer)->right);
    free((*pointer)->operation);
    free(*pointer);
    *pointer = NULL;
}

char *ast_infix_string(AstInfix *ast_infix) {
    Buffer *buffer = buffer_init();

    buffer_write_char(buffer, '(');
    char *left_string = ast_string(ast_infix->left);
    buffer_write_string(buffer, left_string);
    free(left_string);
    buffer_write_char(buffer, ' ');
    buffer_write_string(buffer, ast_infix->operation);
    buffer_write_char(buffer, ' ');
    char *right_string = ast_string(ast_infix->right);
    buffer_write_string(buffer, right_string);
    free(right_string);
    buffer_write_char(buffer, ')');

    char *string = buffer_into_string(buffer);
    return string;
}
