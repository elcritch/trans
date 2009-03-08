#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

#define eat(code) eat_(code,(char *)__FILE__,__LINE__)

extern Token next(void);
extern Token curr(void);
extern void eat_(TokenCode code, char *file_, int line_);

extern int line(void);
extern int col(void);
extern char *scanner_str(void);

#endif
