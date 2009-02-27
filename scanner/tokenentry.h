#ifndef TOKENENTRY_H
#define TOKENENTRY_H

#include "token.h"

extern Token Past(char *arg);
extern Token Upto(char *arg);
extern Token Skip(char *arg);

typedef struct TokenEntry {
  char *name;
  TokenCode code;
  int max;
  Token (*f)(char *arg);
  char *arg;
} *TokenEntry;

#endif
