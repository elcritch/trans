#ifndef __TREE_H
#define __TREE_H

#include "scanner/token.h"

typedef struct TreeStmt *TreeStmt;

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

#endif

// Structure: loc [["id", ["id", "loc"]]]
struct TreeLoc {
  TokenCode code;
  TreeId id;
  TreeLoc loc;
};



// Structure: term_1 [["unary", ["unary", "term"]]]
struct TreeTerm_1 {
  TokenCode code;
  TreeUnary unary;
  TreeTerm term;
};



// Structure: join [["equality", ["equality", "join"]]]
struct TreeJoin {
  TokenCode code;
  TreeEquality equality;
  TreeJoin join;
};



// Structure: expr [["term", ["term", "expr"]]]
struct TreeExpr {
  TokenCode code;
  TreeTerm term;
  TreeExpr expr;
};



// Structure: decl [["type", ["type", "id"]]]
struct TreeDecl {
  TokenCode code;
  TreeType type;
  TreeId id;
};



// Structure: type_1 [["num", ["type"]]]
struct TreeType_1 {
  TokenCode code;
  TreeType type;
};



// Structure: term [["unary", ["unary", "term"]]]
struct TreeTerm {
  TokenCode code;
  TreeUnary unary;
  TreeTerm term;
};



// Structure: rel [["GE", ["expr"]], ["LE", ["expr"]], ["expr", ["expr"]]]
struct TreeRel {
  TokenCode code;
  union {
    struct {
      TreeExpr expr
    } u_GE;
    struct {
      TreeExpr expr
    } u_LE;
    struct {
      TreeExpr expr
    } u_expr;
  } u;
};


// Structure: equality_1 [["EQ", ["rel", "equality"]], ["NE", ["rel", "equality"]]]
struct TreeEquality_1 {
  TokenCode code;
  union {
    struct {
      TreeRel rel;
      TreeEquality equality
    } u_EQ;
    struct {
      TreeRel rel;
      TreeEquality equality
    } u_NE;
  } u;
};


// Structure: unary [["factor", ["factor"]], ["unary", ["unary"]]]
struct TreeUnary {
  TokenCode code;
  union {
    struct {
      TreeFactor factor
    } u_factor;
    struct {
      TreeUnary unary
    } u_unary;
  } u;
};


// Structure: stmts [["stmt", ["stmt", "stmts"]]]
struct TreeStmts {
  TokenCode code;
  TreeStmt stmt;
  TreeStmts stmts;
};



// Structure: type [["basic", ["basic", "type"]]]
struct TreeType {
  TokenCode code;
  TreeBasic basic;
  TreeType type;
};



// Structure: equality [["rel", ["rel", "equality"]]]
struct TreeEquality {
  TokenCode code;
  TreeRel rel;
  TreeEquality equality;
};



// Structure: block [["decls", ["decls", "stmts"]]]
struct TreeBlock {
  TokenCode code;
  TreeDecls decls;
  TreeStmts stmts;
};



// Structure: loc_1 [["bool", ["bool", "loc"]]]
struct TreeLoc_1 {
  TokenCode code;
  TreeBool bool;
  TreeLoc loc;
};



// Structure: expr_1 [["term", ["term", "expr"]]]
struct TreeExpr_1 {
  TokenCode code;
  TreeTerm term;
  TreeExpr expr;
};



// Structure: basic [["float", []], ["int", []]]
struct TreeBasic {
  TokenCode code;
  union {
    struct {
      
    } u_float;
    struct {
      
    } u_int;
  } u;
};


// Structure: stmt [["block", ["block"]], ["break", []], ["do", ["stmt", "bool"]], ["if", ["bool", "stmt"]], ["if", ["bool", "stmt", "stmt"]], ["loc", ["loc", "bool"]], ["read", ["loc"]], ["while", ["bool", "stmt"]], ["write", ["bool"]]]
struct TreeStmt {
  TokenCode code;
  union {
    struct {
      TreeBlock block
    } u_block;
    struct {
      
    } u_break;
    struct {
      TreeStmt stmt;
      TreeBool bool
    } u_do;
    struct {
      TreeBool bool;
      TreeStmt stmt
    } u_if;
    struct {
      TreeBool bool;
      TreeStmt stmt;
      TreeStmt stmt
    } u_if;
    struct {
      TreeLoc loc;
      TreeBool bool
    } u_loc;
    struct {
      TreeLoc loc
    } u_read;
    struct {
      TreeBool bool;
      TreeStmt stmt
    } u_while;
    struct {
      TreeBool bool
    } u_write;
  } u;
};


// Structure: program [["block", ["block"]]]
struct TreeProgram {
  TokenCode code;
  TreeBlock block;
};



// Structure: factor [["bool", ["bool"]], ["false", []], ["loc", ["loc"]], ["num", []], ["real", []], ["true", []]]
struct TreeFactor {
  TokenCode code;
  union {
    struct {
      TreeBool bool
    } u_bool;
    struct {
      
    } u_false;
    struct {
      TreeLoc loc
    } u_loc;
    struct {
      
    } u_num;
    struct {
      
    } u_real;
    struct {
      
    } u_true;
  } u;
};


// Structure: bool_1 [["OR", ["join", "bool"]]]
struct TreeBool_1 {
  TokenCode code;
  TreeJoin join;
  TreeBool bool;
};



// Structure: decls [["decl", ["decl", "decls"]]]
struct TreeDecls {
  TokenCode code;
  TreeDecl decl;
  TreeDecls decls;
};



// Structure: join_1 [["AND", ["equality", "join"]]]
struct TreeJoin_1 {
  TokenCode code;
  TreeEquality equality;
  TreeJoin join;
};



// Structure: bool [["join", ["join", "bool"]]]
struct TreeBool {
  TokenCode code;
  TreeJoin join;
  TreeBool bool;
};


