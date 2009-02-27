#ifndef ERROR_H
#define ERROR_H

#include <stdio.h>
#include <unistd.h>

#include "linkage.h"

#define ERR(s) err((char *)s,(char *)__FILE__,__LINE__)

extern LINKAGE void err(char *msg, char *file, int line);

extern LINKAGE void error_parse(char *msg);
extern LINKAGE void error_scan(int code);

#endif
