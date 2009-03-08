#ifndef __TERMINALS_H
#define __TERMINALS_H 1

#include "symtaben.h"

typedef struct treeid {
  char *id;
  SymtabEntry entry;
} *TreeId;

typedef struct treenum {
  char *num;
} *TreeNum;

typedef struct treereal {
  char *real;
} *TreeReal;



extern TreeId p_id();
extern TreeNum p_num();
extern TreeReal p_real();

#endif



