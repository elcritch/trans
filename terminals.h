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


extern TreeId t_decl_id();
extern TreeId t_id();
extern TreeNum t_num();
extern TreeNum t_num_convert();
extern TreeReal t_real();

#endif



