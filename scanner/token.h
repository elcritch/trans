#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOK_ERROR=256,
    TOK_AND,
    TOK_EQ,
    TOK_GE,
    TOK_ID,
    TOK_LE,
    TOK_NE,
    TOK_NUM,
    TOK_OR,
    TOK_REAL,
    TOK_break,
    TOK_do,
    TOK_else,
    TOK_false,
    TOK_float,
    TOK_if,
    TOK_int,
    TOK_read,
    TOK_true,
    TOK_while,
    TOK_write,
} TokenCode;

typedef struct Token {
  char *lexeme;
  TokenCode code;
} *Token;

#endif
