#ifndef __SYMTABENT_H
#define __SYMTABENT_H 1
#include "scanner/token.h"
// #include "tree.h"
#include <ctype.h>

#define SYM_MAX_DIMS 255

size_t SYM_OFFSET;
size_t SYM_DEPTH;
size_t SYM_MAX_DEPTH;

// typedef struct SymtabEntry *SymtabEntry;
typedef struct treebasic *TreeBasic; 
typedef struct treeblock *TreeBlock; 
typedef struct treebool *TreeBool; 
typedef struct treebool_1 *TreeBool_1; 
typedef struct treedecl *TreeDecl; 
typedef struct treedecls *TreeDecls; 
typedef struct treeequality *TreeEquality; 
typedef struct treeequality_1 *TreeEquality_1; 
typedef struct treeexpr *TreeExpr; 
typedef struct treeexpr_1 *TreeExpr_1; 
typedef struct treefactor *TreeFactor; 
typedef struct treejoin *TreeJoin; 
typedef struct treejoin_1 *TreeJoin_1; 
typedef struct treeloc *TreeLoc; 
typedef struct treeloc_1 *TreeLoc_1; 
typedef struct treeprogram *TreeProgram; 
typedef struct treerel *TreeRel; 
typedef struct treestmt *TreeStmt;
typedef struct treestmts *TreeStmts; 
typedef struct treeterm *TreeTerm; 
typedef struct treeterm_1 *TreeTerm_1; 
typedef struct treetype *TreeType; 
typedef struct treetype_1 *TreeType_1; 
typedef struct treeunary *TreeUnary; 

// typedef struct TreeType_1 *TreeType_1; 

typedef struct symtabentry {
  // token id
  char *id;
  TreeType type;
  TokenCode tok_code;
  size_t dims;

  // table information 
  size_t offset;
  size_t depth;

  // line and column number
  size_t line;
  size_t col;
} *SymtabEntry;

extern SymtabEntry SymtabEntryNew(char *id, TreeType type);



#endif


