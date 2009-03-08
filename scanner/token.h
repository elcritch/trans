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
    TOK_OR,
    TOK_REAL,
    TOK_NUM,
    TOK_break,
    TOK_do,
    TOK_if,
    TOK_else,
    TOK_read,
    TOK_int,
    TOK_float,
    TOK_true,
    TOK_false,
    TOK_while,
    TOK_write,
} TokenCode;

typedef struct token {
  char *lexeme;
  TokenCode code;
} *Token;


extern char *tok_string(TokenCode tokid);

#endif
