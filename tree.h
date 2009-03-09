#ifndef __TREE_H
#define __TREE_H 1

#include "terminals.h"
#include "scanner/token.h"
#include "scanner/error.h"
#include "scanner/tokenentry.h"


/*
struct treestmt {
  TokenCode code;
  union {
    struct {
      TreeLoc loc;
      TreeBool bools;
    } u_assign; 
    struct {
      TreeBool bools;
      TreeStmt stmt;
    } u_while; 
  } u;
};

*/

// Structure: block [["decls", ["decls", "stmts"]]]
struct treeblock {
  TreeDecls decls;
  TreeStmts stmts;
};

// Structure: decls [["decl", ["decl", "decls"]]]
struct treedecls {
  TreeDecl decl;
  TreeDecls decls;
};

// Structure: decl [["type", ["type", "id"]]]
struct treedecl {
  TreeType type;
  TreeId id;
};

// Structure: type [["basic", ["basic", "type_1"]]]
struct treetype {
  TreeBasic basic;
  TreeType_1 type_1;
};

// Structure: type_1 [["num", ["type_1"]]]
struct treetype_1 {
  TreeType_1 type_1;
  TreeNum num;
};

// Structure: basic [["float", []], ["int", []]]
struct treebasic {
  TokenCode code;
};


// Structure: stmts [["stmt", ["stmt", "stmts"]]]
struct treestmts {
  TreeStmt stmt;
  TreeStmts stmts;
};

// Structure: stmt [["block", ["block"]], ["break", []], ["do", ["stmt", "bools"]], ["if", ["bools", "stmt"]], ["if", ["bools", "stmt", "stmt"]], ["loc", ["loc", "bools"]], ["read", ["loc"]], ["while", ["bools", "stmt"]], ["write", ["bools"]]]
struct treestmt {
  TokenCode code;
  char *str;
  union {
    struct {
      TreeBlock block;
    } u_block;
    /* omitting empty rule: break */
    struct {
      TreeStmt stmt;
      TreeBool bools;
    } u_do;
    struct {
      TreeBool bools;
      TreeStmt stmt;
      TreeStmt else_stmt;
    } u_if;
    struct {
      TreeLoc loc;
      TreeBool bools;
    } u_loc;
    struct {
      TreeLoc loc;
    } u_read;
    struct {
      TreeBool bools;
      TreeStmt stmt;
    } u_while;
    struct {
      TreeBool bools;
    } u_write;
  } u;
};


// Structure: loc [["id", ["id", "loc_1"]]]
struct treeloc {
  TreeId id;
  TreeLoc_1 loc_1;
};

// Structure: loc_1 [["bools", ["bools", "loc_1"]]]
struct treeloc_1 {
  TreeBool bools;
  TreeLoc_1 loc_1;
};

// Structure: bools [["join", ["join", "bool_1"]]]
struct treebool {
  TreeJoin join;
  TreeBool_1 bool_1;
};

// Structure: bool_1 [["OR", ["join", "bool_1"]]]
struct treebool_1 {
  TreeJoin join;
  TreeBool_1 bool_1;
};

// Structure: join [["equality", ["equality", "join_1"]]]
struct treejoin {
  TreeEquality equality;
  TreeJoin_1 join_1;
};

// Structure: join_1 [["AND", ["equality", "join_1"]]]
struct treejoin_1 {
  TreeEquality equality;
  TreeJoin_1 join_1;
};

// Structure: equality [["rel", ["rel", "equality_1"]]]
struct treeequality {
  TreeRel rel;
  TreeEquality_1 equality_1;
};

// Structure: equality_1 [["EQ", ["rel", "equality_1"]], ["NE", ["rel", "equality_1"]]]
struct treeequality_1 {
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
struct treerel {
  TokenCode code;
  TreeExpr expr;
  TreeExpr expr_1;
};


// Structure: expr [["term", ["term", "expr_1"]]]
struct treeexpr {
  TreeTerm term;
  TreeExpr_1 expr_1;
};

// Structure: expr_1 [["term", ["term", "expr_1"]]]
struct treeexpr_1 {
  TokenCode code;
  TreeTerm term;
  TreeExpr_1 expr_1;
};

// Structure: term [["unary", ["unary", "term_1"]]]
struct treeterm {
  TreeUnary unary;
  TreeTerm_1 term_1;
};

// Structure: term_1 [["unary", ["unary", "term_1"]]]
struct treeterm_1 {
  TokenCode code;
  TreeUnary unary;
  TreeTerm_1 term_1;
};

// Structure: unary [["factor", ["factor"]], ["unary", ["unary"]]]
struct treeunary {
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


// Structure: factor [["bools", ["bools"]], ["false", []], ["loc", ["loc"]], ["num", []], ["real", []], ["true", []]]
struct treefactor {
  TokenCode code;
  char *val;
  union {
    struct {
      TreeBool bools;
    } u_bool;
    struct {
      TreeLoc loc;
    } u_loc;
    struct {
      TreeNum num;
    } u_num;
    struct {
      TreeReal real;
    } u_real;
	
	/* omitting empty rule: num */
    /* omitting empty rule: real */
    /* omitting empty rule: false */
    /* omitting empty rule: true */
  } u;
};

// tree.c functions
extern TreeBlock t_block_decls(TreeDecls decls, TreeStmts stmts);
extern TreeDecls t_decls_decl(TreeDecl decl, TreeDecls decls);
extern TreeDecl t_decl_type(TreeType type, TreeId id);
extern TreeType t_type_basic(TreeBasic basic, TreeType_1 type_1);
extern TreeType_1 t_type_1_num(TreeNum num, TreeType_1 type_1);
extern TreeBasic t_basic_float();
extern TreeBasic t_basic_int();
extern TreeStmts t_stmts_stmt(TreeStmt stmt, TreeStmts stmts);
extern TreeStmt t_stmt_block(TreeBlock block);
extern TreeStmt t_stmt_break();
extern TreeStmt t_stmt_do(TreeStmt stmt, TreeBool bools);
extern TreeStmt t_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt);
extern TreeStmt t_stmt_loc(TreeLoc loc, TreeBool bools);
extern TreeStmt t_stmt_read(TreeLoc loc);
extern TreeStmt t_stmt_while(TreeBool bools, TreeStmt stmt);
extern TreeStmt t_stmt_write(TreeBool bools);
extern TreeLoc t_loc_id(TreeId id, TreeLoc_1 loc_1);
extern TreeLoc_1 t_loc_1_bool(TreeBool bools, TreeLoc_1 loc_1);
extern TreeBool t_bool_join(TreeJoin join, TreeBool_1 bool_1);
extern TreeBool_1 t_bool_1_OR(TreeJoin join, TreeBool_1 bool_1);
extern TreeJoin t_join_equality(TreeEquality equality, TreeJoin_1 join_1);
extern TreeJoin_1 t_join_1_AND(TreeEquality equality, TreeJoin_1 join_1);
extern TreeEquality t_equality_rel(TreeRel rel, TreeEquality_1 equality_1);
extern TreeEquality_1 t_equality_1_EQ(TreeRel rel, TreeEquality_1 equality_1);
extern TreeEquality_1 t_equality_1_NE(TreeRel rel, TreeEquality_1 equality_1);
extern TreeRel t_rel(TokenCode code, TreeExpr expr, TreeExpr expr_1);
extern TreeExpr t_expr_term(TreeTerm term, TreeExpr_1 expr_1);
extern TreeExpr_1 t_expr_1_term(TokenCode code, TreeTerm term, TreeExpr_1 expr_1);
extern TreeTerm t_term_unary(TreeUnary unary, TreeTerm_1 term_1);
extern TreeTerm_1 t_term_1_unary(TokenCode code, TreeUnary unary, TreeTerm_1 term_1);
extern TreeUnary t_unary_factor(TreeFactor factor);
extern TreeUnary t_unary_unary(TokenCode code, TreeUnary unary);
extern TreeFactor t_factor_bool(TreeBool bools);
extern TreeFactor t_factor_false();
extern TreeFactor t_factor_loc(TreeLoc loc);
extern TreeFactor t_factor_num(TreeNum tok);
extern TreeFactor t_factor_real(TreeReal tok);
extern TreeFactor t_factor_true();

#endif
