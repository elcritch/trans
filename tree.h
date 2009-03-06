#ifndef __TREE_H
#define __TREE_H

#include "scanner/token.h"
#include "symtaben.h"
#include "scanner/error.h"
#include "scanner/tokenentry.h"

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
  char *id;
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

extern TreeStmt t_stmt_assign(TreeLoc loc, TreeBool bool);
extern TreeStmt t_stmt_while(TreeBool bool, TreeStmt stmt);
extern TreeStmt t_stmt_break();
extern TreeBlock t_block_decls(TreeDecls decls, TreeStmts stmts);
extern TreeDecls t_decls_decl(TreeDecl decl, TreeDecls decls);
extern TreeDecl t_decl_type(TreeType type, TreeId id);
extern TreeType t_type_basic(TreeBasic basic, TreeType_1 type_1);
extern TreeType_1 t_type_1_num(TreeType_1 type_1);
extern TreeBasic t_basic_float();
extern TreeBasic t_basic_int();
extern TreeStmts t_stmts_stmt(TreeStmt stmt, TreeStmts stmts);
extern TreeStmt t_stmt_block(TreeBlock block);
extern TreeStmt t_stmt_break();
extern TreeStmt t_stmt_do(TreeStmt stmt, TreeBool bool);
extern TreeStmt t_stmt_if(TreeBool bool, TreeStmt stmt, TreeStmt else_stmt);
extern TreeStmt t_stmt_loc(TreeLoc loc, TreeBool bool);
extern TreeStmt t_stmt_read(TreeLoc loc);
extern TreeStmt t_stmt_while(TreeBool bool, TreeStmt stmt);
extern TreeStmt t_stmt_write(TreeBool bool);
extern TreeLoc t_loc_id(TreeId id, TreeLoc_1 loc_1);
extern TreeLoc_1 t_loc_1_bool(TreeBool bool, TreeLoc_1 loc_1);
extern TreeBool t_bool_join(TreeJoin join, TreeBool_1 bool_1);
extern TreeBool_1 t_bool_1_OR(TreeJoin join, TreeBool_1 bool_1);
extern TreeJoin t_join_equality(TreeEquality equality, TreeJoin_1 join_1);
extern TreeJoin_1 t_join_1_AND(TreeEquality equality, TreeJoin_1 join_1);
extern TreeEquality t_equality_rel(TreeRel rel, TreeEquality_1 equality_1);
extern TreeEquality_1 t_equality_1_EQ(TreeRel rel, TreeEquality_1 equality_1);
extern TreeEquality_1 t_equality_1_NE(TreeRel rel, TreeEquality_1 equality_1);
extern TreeRel t_rel_codeexprexpr(TokenCode code, TreeExpr expr, TreeExpr expr_1);
extern TreeExpr t_expr_term(TreeTerm term, TreeExpr_1 expr_1);
extern TreeExpr_1 t_expr_1_term(TokenCode code, TreeTerm term, TreeExpr_1 expr_1);
extern TreeTerm t_term_unary(TreeUnary unary, TreeTerm_1 term_1);
extern TreeTerm_1 t_term_1_unary(TokenCode code, TreeUnary unary, TreeTerm_1 term_1);
extern TreeUnary t_unary_factor(TreeFactor factor);
extern TreeUnary t_unary_unary(TokenCode code, TreeUnary unary);
extern TreeFactor t_factor_bool(TreeBool bool);
extern TreeFactor t_factor_false();
extern TreeFactor t_factor_loc(TreeLoc loc);
extern TreeFactor t_factor_num(TokenEntry tok);
extern TreeFactor t_factor_real(TokenEntry tok);
extern TreeFactor t_factor_true();

#endif
