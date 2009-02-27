#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

extern Token next(void);
extern Token curr(void);
extern void eat(TokenCode code);

extern int line(void);
extern int col(void);

#endif
