#include "include/parser.h"
#include "include/token.h"
#include <stdio.h>
#include <stdlib.h>

Parser *parser_init(Token **tokens) {
    Parser *parser = malloc(sizeof(Parser));

    size_t index = 0;
    Token *token = tokens[index];
    while (token->type != TOKEN_EOF) {
        index++;
        token = tokens[index];
    }
    size_t length = index + 1;

    parser->length = length;
    parser->tokens = tokens;
    parser->position = 0;
    parser->current = parser->tokens[parser->position];

    return parser;
}

void parser_free(Parser **pointer) {
    Parser *parser = *pointer;

    for (size_t index = 0; index < parser->length; index++) {
        token_free(&parser->tokens[index]);
    }
    free(parser->tokens);
    free(parser);
    *pointer = NULL;
}

typedef enum {
    PRECEDENCE_NONE,
    PRECEDENCE_LOWEST,
    PRECEDENCE_SUM,
    PRECEDENCE_PRODUCT,
    PRECEDENCE_PREFIX
} Precedence;

static Precedence get_precedence(TokenType type) {
    switch (type) {
    case TOKEN_PLUS:
        return PRECEDENCE_SUM;
    case TOKEN_MINUS:
        return PRECEDENCE_SUM;
    case TOKEN_ASTERISK:
        return PRECEDENCE_PRODUCT;
    case TOKEN_SLASH:
        return PRECEDENCE_PRODUCT;
    default:
        return PRECEDENCE_NONE;
    }
}

static void parser_advance(Parser *parser) {
    if (parser->position + 1 >= parser->length) {
        return;
    }
    parser->position++;
    parser->current = parser->tokens[parser->position];
}

static Ast *parser_parse_expression(Parser *parser, Precedence precedence);

static AstNumber *parser_parse_number(Parser *parser) {
    double value;
    sscanf(parser->current->value, "%lf", &value);
    parser_advance(parser);
    return ast_number_init(value);
}

static AstPrefix *parser_parse_prefix(Parser *parser) {
    char *operation = parser->current->value;
    parser_advance(parser);
    return ast_prefix_init(operation,
                           parser_parse_expression(parser, PRECEDENCE_PREFIX));
}

static AstInfix *parser_parse_infix(Parser *parser, Ast *left) {
    char *operation = parser->current->value;
    Precedence precedence = get_precedence(parser->current->type);
    parser_advance(parser);
    return ast_infix_init(left, operation,
                          parser_parse_expression(parser, precedence));
}

static Ast *parser_parse_paren(Parser *parser) {
    parser_advance(parser);
    Ast *expression = parser_parse_expression(parser, PRECEDENCE_LOWEST);
    parser_advance(parser);
    return expression;
}

static Ast *parser_parse_expression(Parser *parser, Precedence precedence) {
    Ast *left;

    switch (parser->current->type) {
    case TOKEN_NUMBER:
        left = (Ast *)parser_parse_number(parser);
        break;
    case TOKEN_MINUS:
        left = (Ast *)parser_parse_prefix(parser);
        break;
    case TOKEN_OPEN_PAREN:
        left = parser_parse_paren(parser);
        break;
    default:
        break;
    }

    while (precedence < get_precedence(parser->current->type)) {
        left = (Ast *)parser_parse_infix(parser, left);
    }

    return left;
}

Ast *parser_parse(Parser *parser) {
    return parser_parse_expression(parser, PRECEDENCE_LOWEST);
}
