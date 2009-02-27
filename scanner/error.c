#include <stdio.h>
#include <stdlib.h>

#include "error.h"
#include "scanner.h"

extern LINKAGE void err(char *msg, char *file, int line) {
  fprintf(stderr,"%s:%d: %s\n",file,line,msg);
  exit(1);
}

extern LINKAGE void error_parse(char *msg) {
  fprintf(stderr,"parse error: %s (line: %d, char %d)\n",msg,line(),col());
}

extern LINKAGE void error_scan(int code) {
  fprintf(stderr,"scan error: %d (line: %d, char %d)\n",code,line(),col());
}
