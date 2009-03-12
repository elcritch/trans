#ifndef __TERMINALS_H
#define __TERMINALS_H 1

#include "symtaben.h"

typedef struct treeid {
  char *lex;
  SymtabEntry entry;
} *TreeId;

typedef struct treenum {
  char *num;
  size_t size;
} *TreeNum;

typedef struct treereal {
  char *real;
} *TreeReal;


extern TreeId p_decl_id();
extern TreeId p_id();
extern TreeNum p_num();
extern TreeNum p_num_convert();
extern TreeReal p_real();

#endif



