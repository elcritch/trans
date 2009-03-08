#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

#include "scanner.h"
#include "tokenentry.h"
#include "strtab.h"
#include "error.h"
//make scanner
extern TokenEntry in_word_set(char *str, unsigned int len);

typedef struct {
  char *str;
  int lineno;
  int eof;
  char *pos;
  struct Token curr;
} Scanner;

static Scanner s;

static void getline(void) {
  if (s.eof)
    return;
  if (s.str)
    free(s.str);
  s.str=readline(0);
  s.lineno++;
  if (s.str) {
    add_history(s.str);
  } else {
    s.eof=1;
    write_history(".history");
  }
  s.pos=s.str;
}

static void new(void) {
  if (isatty(fileno(stdin))) {
    using_history();
    read_history(".history");
  } else {
    rl_bind_key('\t',rl_insert);
    rl_outstream=fopen("/dev/null","w");
  }
  getline();
  next();
}

extern Token curr(void) {
  if (s.eof)
    return 0;
  if (!s.str)
    new();
  return &s.curr;
}

extern void eat_(TokenCode code, char *file_, int line_) {
  if (!curr() || code!=curr()->code)
    error_scan(code, curr()->code, file_, line_);
  next();
}

extern int line(void) {
  return s.lineno;
}

extern char *scanner_str(void) {
  return s.str;
}

extern int col(void) {
  return s.pos-s.str;
}

static Token mktoken(char *old, TokenCode code) {
  s.curr.lexeme=strtabget(old,s.pos-old);
  s.curr.code=code;
  return &s.curr;
}

static void past(char *str) {
  int len=strlen(str);
  if (len==0) {
    getline();
    return;
  }
  while (!s.eof) {
    while (*s.pos) {
      if (!strncmp(s.pos,str,len)) {
	s.pos+=len;
	return;
      }
      s.pos++;
    }
    getline();
  }
}

static void upto(char *str) {
  int len=strlen(str);
  if (len==0) {
    getline();
    return;
  }
  while (!s.eof) {
    while (*s.pos) {
      if (!strncmp(s.pos,str,len))
	return;
      s.pos++;
    }
    getline();
  }
}

static void skip(char *chars) {
  while (!s.eof) {
    while (*s.pos && strchr(chars,*s.pos))
      s.pos++;
    if (*s.pos)
      return;
    getline();
  }
}

static Token scan_id(void) {
  char *old=s.pos;
  while (isalpha(*s.pos) || isdigit(*s.pos))
    s.pos++;
  TokenEntry entry=in_word_set(old,s.pos-old);
  return mktoken(old,(entry ? entry->code : TOK_ID));
}

static Token scan_num(void) {
  TokenCode code=TOK_NUM;
  char *old=s.pos;
  while (isdigit(*s.pos))
    s.pos++;
  if (*s.pos=='.') {
    code=TOK_REAL;
    s.pos++;
    while (isdigit(*s.pos))
      s.pos++;
  }
  return mktoken(old,code);
}

static Token scan_sym(void) {
  char *old=s.pos++;
  TokenEntry entry=in_word_set(old,1);
  if (!entry)
    return mktoken(old,TOK_ERROR);
  TokenCode code=(entry->code ? entry->code : *old);
  if (entry->max) {
    int len=entry->max;
    if (len>strlen(old))
      len=strlen(old);
    for (; len>1; len--) {
      entry=in_word_set(old,len);
      if (entry) {
	code=entry->code;
	s.pos=old+len;
	break;
      }
    }
  }
  if (entry && entry->f)
    return entry->f(entry->arg);
  return mktoken(old,code);
}

extern Token next(void) {
  Token token;
  do {
    skip(" \t");
    if (s.eof)
      return 0;
    if (isalpha(*s.pos))
      token=scan_id();
    else if (isdigit(*s.pos))
      token=scan_num();
    else
      token=scan_sym();
  } while (!token);
  return token;
}

extern Token Past(char *arg) { past(arg); return 0; }
extern Token Upto(char *arg) { upto(arg); return 0; }
extern Token Skip(char *arg) { skip(arg); return 0; }
