#ifndef AST_H
#define AST_H

typedef enum { AST_NUMBER, AST_PREFIX, AST_INFIX } AstType;

typedef struct {
    AstType type;
} Ast;

void ast_free(Ast **pointer);
char *ast_string(Ast *ast);

typedef struct {
    AstType type;
    double value;
} AstNumber;

AstNumber *ast_number_init(double value);
void ast_number_free(AstNumber **pointer);
char *ast_number_string(AstNumber *ast_number);

typedef struct {
    AstType type;
    char *operation;
    Ast *right;
} AstPrefix;

AstPrefix *ast_prefix_init(const char *operation, Ast *right);
void ast_prefix_free(AstPrefix **pointer);
char *ast_prefix_string(AstPrefix *ast_prefix);

typedef struct {
    AstType type;
    Ast *left;
    char *operation;
    Ast *right;
} AstInfix;

AstInfix *ast_infix_init(Ast *left, const char *operation, Ast *right);
void ast_infix_free(AstInfix **pointer);
char *ast_infix_string(AstInfix *ast_infix);

#endif
