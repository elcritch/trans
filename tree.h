#ifndef __TREE_H
#define __TREE_H

#include "scanner/token.h"
#include "symtaben.h"

typedef struct TreeBasic *TreeBasic; 
typedef struct TreeBlock *TreeBlock; 
typedef struct TreeBool *TreeBool; 
typedef struct TreeBool_1 *TreeBool_1; 
typedef struct TreeDecl *TreeDecl; 
typedef struct TreeDecls *TreeDecls; 
typedef struct TreeEquality *TreeEquality; 
typedef struct TreeEquality_1 *TreeEquality_1; 
typedef struct TreeExpr *TreeExpr; 
typedef struct TreeExpr_1 *TreeExpr_1; 
typedef struct TreeFactor *TreeFactor; 
typedef struct TreeJoin *TreeJoin; 
typedef struct TreeJoin_1 *TreeJoin_1; 
typedef struct TreeLoc *TreeLoc; 
typedef struct TreeLoc_1 *TreeLoc_1; 
typedef struct TreeProgram *TreeProgram; 
typedef struct TreeRel *TreeRel; 
typedef struct TreeStmt *TreeStmt;
typedef struct TreeStmts *TreeStmts; 
typedef struct TreeTerm *TreeTerm; 
typedef struct TreeTerm_1 *TreeTerm_1; 
typedef struct TreeType *TreeType; 
typedef struct TreeType_1 *TreeType_1; 
typedef struct TreeUnary *TreeUnary; 

// terminals
typedef struct TreeId *TreeId; 

/*
struct TreeStmt {
  TokenCode code;
  union {
    struct {
      TreeLoc loc;
      TreeBool bool;
    } u_assign; 
    struct {
      TreeBool bool;
      TreeStmt stmt;
    } u_while; 
  } u;
};

*/

struct TreeId {
  TokenCode code;
  SymtabEntry entry;
  char *lex;
};



// Structure: block [["decls", ["decls", "stmts"]]]
struct TreeBlock {
  TreeDecls decls;
  TreeStmts stmts;
};

// Structure: decls [["decl", ["decl", "decls"]]]
struct TreeDecls {
  TreeDecl decl;
  TreeDecls decls;
};

// Structure: decl [["type", ["type", "id"]]]
struct TreeDecl {
  TreeType type;
  TreeId id;
};

// Structure: type [["basic", ["basic", "type_1"]]]
struct TreeType {
  TreeBasic basic;
  TreeType_1 type_1;
};

// Structure: type_1 [["num", ["type_1"]]]
struct TreeType_1 {
  TreeType_1 type_1;
};

// Structure: basic [["float", []], ["int", []]]
struct TreeBasic {
  TokenCode code;
};


// Structure: stmts [["stmt", ["stmt", "stmts"]]]
struct TreeStmts {
  TreeStmt stmt;
  TreeStmts stmts;
};

// Structure: stmt [["block", ["block"]], ["break", []], ["do", ["stmt", "bool"]], ["if", ["bool", "stmt"]], ["if", ["bool", "stmt", "stmt"]], ["loc", ["loc", "bool"]], ["read", ["loc"]], ["while", ["bool", "stmt"]], ["write", ["bool"]]]
struct TreeStmt {
  TokenCode code;
  union {
    struct {
      TreeBlock block;
    } u_block;
    /* omitting empty rule: break */
    struct {
      TreeStmt stmt;
      TreeBool bool;
    } u_do;
    struct {
      TreeBool bool;
      TreeStmt stmt;
      TreeStmt else_stmt;
    } u_if;
    struct {
      TreeLoc loc;
      TreeBool bool;
    } u_loc;
    struct {
      TreeLoc loc;
    } u_read;
    struct {
      TreeBool bool;
      TreeStmt stmt;
    } u_while;
    struct {
      TreeBool bool;
    } u_write;
  } u;
};


// Structure: loc [["id", ["id", "loc_1"]]]
struct TreeLoc {
  TreeId id;
  TreeLoc_1 loc_1;
};

// Structure: loc_1 [["bool", ["bool", "loc_1"]]]
struct TreeLoc_1 {
  TreeBool bool;
  TreeLoc_1 loc_1;
};

// Structure: bool [["join", ["join", "bool_1"]]]
struct TreeBool {
  TreeJoin join;
  TreeBool_1 bool_1;
};

// Structure: bool_1 [["OR", ["join", "bool_1"]]]
struct TreeBool_1 {
  TreeJoin join;
  TreeBool_1 bool_1;
};

// Structure: join [["equality", ["equality", "join_1"]]]
struct TreeJoin {
  TreeEquality equality;
  TreeJoin_1 join_1;
};

// Structure: join_1 [["AND", ["equality", "join_1"]]]
struct TreeJoin_1 {
  TreeEquality equality;
  TreeJoin_1 join_1;
};

// Structure: equality [["rel", ["rel", "equality_1"]]]
struct TreeEquality {
  TreeRel rel;
  TreeEquality_1 equality_1;
};

// Structure: equality_1 [["EQ", ["rel", "equality_1"]], ["NE", ["rel", "equality_1"]]]
struct TreeEquality_1 {
  TokenCode code;
  union {
    struct {
      TreeRel rel;
      TreeEquality_1 equality_1;
    } u_EQ;
    struct {
      TreeRel rel;
      TreeEquality_1 equality_1;
    } u_NE;
  } u;
};


// Structure: rel [["GE", ["expr"]], ["LE", ["expr"]], ["expr", ["expr"]]]
struct TreeRel {
  TokenCode code;
  TreeExpr expr;
  TreeExpr expr_1;
};


// Structure: expr [["term", ["term", "expr_1"]]]
struct TreeExpr {
  TreeTerm term;
  TreeExpr_1 expr_1;
};

// Structure: expr_1 [["term", ["term", "expr_1"]]]
struct TreeExpr_1 {
  TreeTerm term;
  TreeExpr_1 expr_1;
};

// Structure: term [["unary", ["unary", "term_1"]]]
struct TreeTerm {
  TreeUnary unary;
  TreeTerm_1 term_1;
};

// Structure: term_1 [["unary", ["unary", "term_1"]]]
struct TreeTerm_1 {
  TreeUnary unary;
  TreeTerm_1 term_1;
};

// Structure: unary [["factor", ["factor"]], ["unary", ["unary"]]]
struct TreeUnary {
  TokenCode code;
  union {
    struct {
      TreeFactor factor;
    } u_factor;
    struct {
      TreeUnary unary;
    } u_unary;
  } u;
};


// Structure: factor [["bool", ["bool"]], ["false", []], ["loc", ["loc"]], ["num", []], ["real", []], ["true", []]]
struct TreeFactor {
  TokenCode code;
  char *val;
  union {
    struct {
      TreeBool bool;
    } u_bool;
    struct {
      TreeLoc loc;
    } u_loc;
	
	/* omitting empty rule: num */
    /* omitting empty rule: real */
    /* omitting empty rule: false */
    /* omitting empty rule: true */
  } u;
};


#endif
