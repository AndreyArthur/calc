#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_EOF,
    TOKEN_ILLEGAL,
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_ASTERISK,
    TOKEN_SLASH,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

Token *token_init(TokenType type, const char *value);
void token_free(Token **pointer);

#endif
