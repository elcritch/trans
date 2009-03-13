#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <unistd.h>
// #include "token.h"
#include "linkage.h"

#define ERR(s) err((char *)s,(char *)__FILE__,__LINE__)

int PARSE_ERROR;
int GEN_ERROR;

extern LINKAGE void err(char *msg, char *file, int line);

extern LINKAGE void error_parse(char *msg);
extern LINKAGE void error_scan(int code, int found, char *file, int line);

#endif
