#include "tree.h"
#include <stdlib.h>

#define ALLOC(t)		  \
  struct t *v = calloc(1,sizeof(struct t)); \
  if (!v) ERR("malloc() failed")

/**
extern TreeStmt t_stmt_assign(TreeLoc loc, TreeBool bools) {
  ALLOC(treestmt);
  v->code=TOK_ID;
  v->u.u_assign.loc=loc;
  v->u.u_assign.bools=bools;
  return v;
}

extern TreeStmt t_stmt_while(TreeBool bools, TreeStmt stmt) {
  ALLOC(treestmt);
  v->code=TOK_while;
  v->u.u_while.bools=bools;
  v->u.u_while.stmt=stmt;
  return v;
}

extern TreeStmt t_stmt_break() {
  ALLOC(treestmt);
  v->code=TOK_break;
  return v;
}
*/


// ================= Block 1 ========================================


// ================= Block 1 ========================================

// Block ["decls", "stmts"]
extern TreeBlock t_block_decls(TreeDecls decls, TreeStmts stmts) {
  ALLOC(treeblock);
  v->decls = decls;
  v->stmts = stmts;
  return v;
}

// ================= Decls 1 ========================================

// Decls ["decl", "decls"]
extern TreeDecls t_decls_decl(TreeDecl decl, TreeDecls decls) {
  ALLOC(treedecls);
  v->decl = decl;
  v->decls = decls;
  return v;
}

// ================= Decl 1 ========================================

// Decl ["type", "id"]
extern TreeDecl t_decl_type(TreeType type, TreeId id) {
  ALLOC(treedecl);
  v->type = type;
  v->id = id;
  return v;
}

// ================= Type 1 ========================================

// Type ["basic", "type_1"]
extern TreeType t_type_basic(TreeBasic basic, TreeType_1 type_1) {
  ALLOC(treetype);
  v->basic = basic;
  v->type_1 = type_1;
  return v;
}

// ================= Type_1 1 ========================================

// Type_1 ["type_1"]
extern TreeType_1 t_type_1_num(TreeNum num, TreeType_1 type_1) {
  ALLOC(treetype_1);
  v->type_1 = type_1;
  return v;
}

// ================= Basic 2 ========================================

// Basic []
extern TreeBasic t_basic_float() {
  ALLOC(treebasic);
  v->code = TOK_float;
  
  return v;
}

// Basic []
extern TreeBasic t_basic_int() {
  ALLOC(treebasic);
  v->code = TOK_int;
  
  return v;
}

// ================= Stmts 1 ========================================

// Stmts ["stmt", "stmts"]
extern TreeStmts t_stmts_stmt(TreeStmt stmt, TreeStmts stmts) {
  ALLOC(treestmts);
  v->stmt = stmt;
  v->stmts = stmts;
  return v;
}

// ================= Stmt 9 ========================================

// Stmt ["block"]
extern TreeStmt t_stmt_block(TreeBlock block) {
  ALLOC(treestmt);
  v->code = '{';
  v->u.u_block.block = block;
  return v;
}

// Stmt []
extern TreeStmt t_stmt_break() {
  ALLOC(treestmt);
  v->code = TOK_break;
  
  return v;
}

// Stmt ["stmt", "bools"]
extern TreeStmt t_stmt_do(TreeStmt stmt, TreeBool bools) {
  ALLOC(treestmt);
  v->code = TOK_do;
  v->u.u_do.stmt = stmt;
  v->u.u_do.bools = bools;
  return v;
}

// Stmt ["bools", "stmt", "stmt"]
extern TreeStmt t_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt) {
  ALLOC(treestmt);
  v->code = TOK_if;
  v->u.u_if.bools = bools;
  v->u.u_if.stmt = stmt;
  v->u.u_if.else_stmt = else_stmt;
  printf("v->u.u_if.else_stmt == %p\n",v->u.u_if.else_stmt);
  return v;
}

// Stmt ["loc", "bools"]
extern TreeStmt t_stmt_loc(TreeLoc loc, TreeBool bools) {
  ALLOC(treestmt);
  v->code = TOK_ID;
  v->u.u_loc.loc = loc;
  v->u.u_loc.bools = bools;
  return v;
}

// Stmt ["loc"]
extern TreeStmt t_stmt_read(TreeLoc loc) {
  ALLOC(treestmt);
  v->code = TOK_read;
  v->u.u_read.loc = loc;
  return v;
}

// Stmt ["bools", "stmt"]
extern TreeStmt t_stmt_while(TreeBool bools, TreeStmt stmt) {
  ALLOC(treestmt);
  v->code = TOK_while;
  v->u.u_while.bools = bools;
  v->u.u_while.stmt = stmt;
  return v;
}

// Stmt ["bools"]
extern TreeStmt t_stmt_write(TreeBool bools) {
  ALLOC(treestmt);
  v->code = TOK_write;
  v->u.u_write.bools = bools;
  return v;
}

// ================= Loc 1 ========================================

// Loc ["id", "loc_1"]
extern TreeLoc t_loc_id(TreeId id, TreeLoc_1 loc_1) {
  ALLOC(treeloc);
  v->id = id;
  v->loc_1 = loc_1;
  return v;
}

// ================= Loc_1 1 ========================================

// Loc_1 ["bools", "loc_1"]
extern TreeLoc_1 t_loc_1_bool(TreeBool bools, TreeLoc_1 loc_1) {
  ALLOC(treeloc_1);
  v->bools = bools;
  v->loc_1 = loc_1;
  return v;
}

// ================= Bool 1 ========================================

// Bool ["join", "bool_1"]
extern TreeBool t_bool_join(TreeJoin join, TreeBool_1 bool_1) {
  ALLOC(treebool);
  v->join = join;
  v->bool_1 = bool_1;
  return v;
}

// ================= Bool_1 1 ========================================

// Bool_1 ["join", "bool_1"]
extern TreeBool_1 t_bool_1_OR(TreeJoin join, TreeBool_1 bool_1) {
  ALLOC(treebool_1);
  v->join = join;
  v->bool_1 = bool_1;
  return v;
}

// ================= Join 1 ========================================

// Join ["equality", "join_1"]
extern TreeJoin t_join_equality(TreeEquality equality, TreeJoin_1 join_1) {
  ALLOC(treejoin);
  v->equality = equality;
  v->join_1 = join_1;
  return v;
}

// ================= Join_1 1 ========================================

// Join_1 ["equality", "join_1"]
extern TreeJoin_1 t_join_1_AND(TreeEquality equality, TreeJoin_1 join_1) {
  ALLOC(treejoin_1);
  v->equality = equality;
  v->join_1 = join_1;
  return v;
}

// ================= Equality 1 ========================================

// Equality ["rel", "equality_1"]
extern TreeEquality t_equality_rel(TreeRel rel, TreeEquality_1 equality_1) {
  ALLOC(treeequality);
  v->rel = rel;
  v->equality_1 = equality_1;
  return v;
}

// ================= Equality_1 2 ========================================

// Equality_1 ["rel", "equality_1"]
extern TreeEquality_1 t_equality_1_EQ(TreeRel rel, TreeEquality_1 equality_1) {
  ALLOC(treeequality_1);
  v->code = TOK_EQ;
  v->u.u_EQ.rel = rel;
  v->u.u_EQ.equality_1 = equality_1;
  return v;
}

// Equality_1 ["rel", "equality_1"]
extern TreeEquality_1 t_equality_1_NE(TreeRel rel, TreeEquality_1 equality_1) {
  ALLOC(treeequality_1);
  v->code = TOK_NE;
  v->u.u_NE.rel = rel;
  v->u.u_NE.equality_1 = equality_1;
  return v;
}

// ================= Rel 2 ========================================

// Rel ["code", "expr", "expr"]
extern TreeRel t_rel(TokenCode code, TreeExpr expr, TreeExpr expr_1) {
  ALLOC(treerel);
  v->code = code;
  v->expr = expr;
  v->expr_1 = expr_1;
  return v;
}

// ================= Expr 1 ========================================

// Expr ["term", "expr_1"]
extern TreeExpr t_expr_term(TreeTerm term, TreeExpr_1 expr_1) {
  ALLOC(treeexpr);
  v->term = term;
  v->expr_1 = expr_1;
  return v;
}

// ================= Expr_1 1 ========================================

// Expr_1 ["code", "term", "expr_1"]
extern TreeExpr_1 t_expr_1_term(TokenCode code, TreeTerm term, TreeExpr_1 expr_1) {
  ALLOC(treeexpr_1);
  v->code = code;
  v->term = term;
  v->expr_1 = expr_1;
  return v;
}

// ================= Term 1 ========================================

// Term ["unary", "term_1"]
extern TreeTerm t_term_unary(TreeUnary unary, TreeTerm_1 term_1) {
  ALLOC(treeterm);
  v->unary = unary;
  v->term_1 = term_1;
  return v;
}

// ================= Term_1 1 ========================================

// Term_1 ["code", "unary", "term_1"]
extern TreeTerm_1 t_term_1_unary(TokenCode code, TreeUnary unary, TreeTerm_1 term_1) {
  ALLOC(treeterm_1);
  v->code = code;
  v->unary = unary;
  v->term_1 = term_1;
  return v;
}

// ================= Unary 2 ========================================

// Unary ["factor"]
extern TreeUnary t_unary_factor(TreeFactor factor) {
  ALLOC(treeunary);
  v->code = 0;
  v->u.u_factor.factor = factor;
  return v;
}

// Unary ["code", "unary"]
extern TreeUnary t_unary_unary(TokenCode code, TreeUnary unary) {
  ALLOC(treeunary);
  v->code = code;
  
  v->u.u_unary.unary = unary;
  return v;
}

// ================= Factor 6 ========================================

// Factor ["bools"]
extern TreeFactor t_factor_bool(TreeBool bools) {
  ALLOC(treefactor);
  v->code = '(';
  v->u.u_bool.bools = bools;
  return v;
}

// Factor []
extern TreeFactor t_factor_false() {
  ALLOC(treefactor);
  v->code = TOK_false;
  v->val = "1";
  return v;
}

// Factor ["loc"]
extern TreeFactor t_factor_loc(TreeLoc loc) {
  ALLOC(treefactor);
  v->code = TOK_ID;
  v->u.u_loc.loc = loc;
  return v;
}

// Factor []
extern TreeFactor t_factor_num(TreeNum num) {
  ALLOC(treefactor);
  v->code = TOK_NUM;
  v->u.u_num.num = num;
  return v;
}

// Factor []
extern TreeFactor t_factor_real(TreeReal real) {
  ALLOC(treefactor);
  v->code = TOK_REAL;
  v->u.u_real.real = real;
  return v;
}

// Factor []
extern TreeFactor t_factor_true() {
  ALLOC(treefactor);
  v->code = TOK_true;
  v->val = "1";
  return v;
}
