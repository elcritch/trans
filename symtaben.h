
#ifndef __SYMTABENT_H
#define __SYMTABENT_H 1

#include "tree.h"

typedef struct SymtabEntry {
  TokenCode code; // type
  char *data;
  struct TreeLoc_1 *dim;
} *SymtabEntry;




#endif