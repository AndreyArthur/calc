#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>

Lexer *lexer_init(const char *content) {
    Lexer *lexer = malloc(sizeof(Lexer));
    lexer->content = content;
    lexer->length = strlen(content);
    lexer->position = 0;
    lexer->current = lexer->content[lexer->position];
    return lexer;
}

void lexer_free(Lexer **pointer) {
    free(*pointer);
    *pointer = NULL;
}

static void lexer_advance(Lexer *lexer) {
    if (lexer->position >= lexer->length) {
        return;
    }

    if (lexer->position == lexer->length - 1) {
        lexer->position++;
        lexer->current = '\0';
        return;
    }

    lexer->position++;
    lexer->current = lexer->content[lexer->position];
}

static Token *lexer_collect_single(Lexer *lexer, TokenType type) {
    char buffer[2];
    buffer[0] = lexer->current;
    buffer[1] = '\0';
    lexer_advance(lexer);
    return token_init(type, buffer);
}

static void lexer_skip_whitespaces(Lexer *lexer) {
    while (lexer->current == ' ' || lexer->current == '\t' ||
           lexer->current == '\n' || lexer->current == '\r') {
        lexer_advance(lexer);
    }
}

static Token *lexer_collect_number(Lexer *lexer) {
    int length = 0;
    char *text = strdup("");
    while (lexer->current >= '0' && lexer->current <= '9') {
        length++;
        text = realloc(text, sizeof(char) * length + 1);
        strcat(text, &lexer->current);
        lexer_advance(lexer);
    }

    if (lexer->current != '.') {
        Token *token = token_init(TOKEN_NUMBER, text);
        free(text);
        return token;
    }

    length++;
    text = realloc(text, sizeof(char) * length + 1);
    strcat(text, &lexer->current);
    lexer_advance(lexer);

    while (lexer->current >= '0' && lexer->current <= '9') {
        length++;
        text = realloc(text, sizeof(char) * length + 1);
        strcat(text, &lexer->current);
        lexer_advance(lexer);
    }

    Token *token = token_init(TOKEN_NUMBER, text);
    free(text);
    return token;
}

Token *lexer_next(Lexer *lexer) {
    lexer_skip_whitespaces(lexer);

    switch (lexer->current) {
    case '\0':
        return lexer_collect_single(lexer, TOKEN_EOF);
    case '+':
        return lexer_collect_single(lexer, TOKEN_PLUS);
    case '-':
        return lexer_collect_single(lexer, TOKEN_MINUS);
    case '*':
        return lexer_collect_single(lexer, TOKEN_ASTERISK);
    case '/':
        return lexer_collect_single(lexer, TOKEN_SLASH);
    case '(':
        return lexer_collect_single(lexer, TOKEN_OPEN_PAREN);
    case ')':
        return lexer_collect_single(lexer, TOKEN_CLOSE_PAREN);
    default: {
        if (lexer->current >= '0' && lexer->current <= '9') {
            return lexer_collect_number(lexer);
        }
        return lexer_collect_single(lexer, TOKEN_ILLEGAL);
    }
    }
}
