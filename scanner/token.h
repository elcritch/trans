#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
  TOK_ERROR=256,
  TOK_ID,
  TOK_NUM,
  TOK_REAL,
  TOK_break,
  TOK_while,
  TOK_AND,
  TOK_LE,
  TOK_OR,
} TokenCode;

typedef struct Token {
  char *lexeme;
  TokenCode code;
} *Token;

#endif
