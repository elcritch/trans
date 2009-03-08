#ifndef __PRINTLIB_H
#define __PRINTLIB_H 1
#include "tree.h"

void printer(char *msg, int d);
void printer_line(char *msg, int d);
void print_tok(int d, int code);

extern void print_TreeBlock( int d, TreeBlock v );
extern void print_TreeDecls( int d, TreeDecls v );
extern void print_TreeDecl( int d, TreeDecl v );
extern void print_TreeType( int d, TreeType v );
extern void print_TreeType_1( int d, TreeType_1 v );
extern void print_TreeBasic( int d, TreeBasic v );
extern void print_TreeStmts( int d, TreeStmts v );
extern void print_TreeStmt( int d, TreeStmt v );
extern void print_TreeLoc( int d, TreeLoc v );
extern void print_TreeLoc_1( int d, TreeLoc_1 v );
extern void print_TreeBool( int d, TreeBool v );
extern void print_TreeBool_1( int d, TreeBool_1 v );
extern void print_TreeJoin( int d, TreeJoin v );
extern void print_TreeJoin_1( int d, TreeJoin_1 v );
extern void print_TreeEquality( int d, TreeEquality v );
extern void print_TreeEquality_1( int d, TreeEquality_1 v );
extern void print_TreeRel( int d, TreeRel v );
extern void print_TreeExpr( int d, TreeExpr v );
extern void print_TreeExpr_1( int d, TreeExpr_1 v );
extern void print_TreeTerm( int d, TreeTerm v );
extern void print_TreeTerm_1( int d, TreeTerm_1 v );
extern void print_TreeUnary( int d, TreeUnary v );
extern void print_TreeFactor( int d, TreeFactor v );

#endif
