#ifndef __SYMTABENT_H
#define __SYMTABENT_H 1
#define SYM_MAX_DIMS = 4;

// #include "scanner/token.h"
#include "tree.h"


unsigned int SYM_OFFSET = 0;
unsigned int SYM_DEPTH = 0;
unsigned int SYM_MAX_DEPTH = 0;

// typedef struct SymtabEntry *SymtabEntry;
// typedef struct TreeType *TreeType; 
// typedef struct TreeType_1 *TreeType_1; 

typedef struct SymtabEntry {
  // token id
  char *id;
  TreeType type;
  unsigned int dims;

  // table information 
  unsigned int offset;
  unsigned int depth;

  // line and column number
  unsigned int line;
  unsigned int col;
} *SymtabEntry;




#endif