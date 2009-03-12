#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "error.h"
#include "scanner.h"
#include "token.h"

#define OUTPUT stdout

extern LINKAGE void err(char *msg, char *file, int line) {
  fprintf(OUTPUT,"%s:%d: %s\n",file,line,msg);
  fflush(stdout); fflush(stderr);
  kill(getpid(),SIGINT);
}

extern LINKAGE void error_parse(char *msg) {
  fprintf(OUTPUT,"parse error: %s (line: %d, char %d)\n",msg,line(),col());
  fflush(stdout); fflush(stderr);
  // kill(getpid(),SIGINT);
}

// error_scan(code, curr()->code, file_, line_);
extern LINKAGE void error_scan(int code, int found, char *fl, int ln) {
   char *str = tok_string(code);
   char *str1 = tok_string(found);
   fprintf(OUTPUT,"scan error: at:%s:%d (line: %d, char %d)\n", fl, ln, line(),col());
   if (str)
      fprintf(OUTPUT,"tok found: '%s'\n", str);
   else
      fprintf(OUTPUT,"tok found: '%d'\n", code);

   if (str1)
      fprintf(OUTPUT,"tok require: '%s'\n", str1);
   else
      fprintf(OUTPUT,"tok found: '%d'\n", found);
      
   fflush(stdout); fflush(stderr);
   kill(getpid(),SIGINT);
}

