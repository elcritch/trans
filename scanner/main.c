#include <stdio.h>

#include "scanner.h"

int main() {
  Token token;
  while ((token=curr())) {
    printf("%d: %s\n",token->code,token->lexeme);
    next();
  }
  return 0;
}
