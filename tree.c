#include "tree.h"

#define ALLOC(t)		  \
  t v=malloc(sizeof(*v)); \
  if (!v) ERR("malloc() failed")

/**
extern TreeStmt t_stmt_assign(TreeLoc loc, TreeBool bool) {
  ALLOC(TreeStmt);
  v->code=TOK_ID;
  v->u.u_assign.loc=loc;
  v->u.u_assign.bool=bool;
  return v;
}

extern TreeStmt t_stmt_while(TreeBool bool, TreeStmt stmt) {
  ALLOC(TreeStmt);
  v->code=TOK_while;
  v->u.u_while.bool=bool;
  v->u.u_while.stmt=stmt;
  return v;
}

extern TreeStmt t_stmt_break() {
  ALLOC(TreeStmt);
  v->code=TOK_break;
  return v;
}
*/


// =====================================================================

// Basic []
extern TreeBasic t_basic_float() {
  ALLOC(TreeBasic);
  v->code=TOK_float;
  
  return v;
}

// Basic []
extern TreeBasic t_basic_int() {
  ALLOC(TreeBasic);
  v->code=TOK_int;
  
  return v;
}

// Block ["decls", "stmts"]
extern TreeBlock t_block_decls(TreeDecls decls, TreeStmts stmts) {
  ALLOC(TreeBlock);
  v->code=TOK_decls;
  v->decls = decls;
  v->stmts = stmts;
  return v;
}

// Bool ["join", "bool"]
extern TreeBool t_bool_join(TreeJoin join, TreeBool bool) {
  ALLOC(TreeBool);
  v->code=TOK_join;
  v->join = join;
  v->bool = bool;
  return v;
}

// Bool_1 ["join", "bool"]
extern TreeBool_1 t_bool_1_OR(TreeJoin join, TreeBool bool) {
  ALLOC(TreeBool_1);
  v->code=TOK_OR;
  v->join = join;
  v->bool = bool;
  return v;
}

// Decl ["type", "id"]
extern TreeDecl t_decl_type(TreeType type, TreeId id) {
  ALLOC(TreeDecl);
  v->code=TOK_type;
  v->type = type;
  v->id = id;
  return v;
}

// Decls ["decl", "decls"]
extern TreeDecls t_decls_decl(TreeDecl decl, TreeDecls decls) {
  ALLOC(TreeDecls);
  v->code=TOK_decl;
  v->decl = decl;
  v->decls = decls;
  return v;
}

// Equality ["rel", "equality"]
extern TreeEquality t_equality_rel(TreeRel rel, TreeEquality equality) {
  ALLOC(TreeEquality);
  v->code=TOK_rel;
  v->rel = rel;
  v->equality = equality;
  return v;
}

// Equality_1 ["rel", "equality"]
extern TreeEquality_1 t_equality_1_EQ(TreeRel rel, TreeEquality equality) {
  ALLOC(TreeEquality_1);
  v->code=TOK_EQ;
  v->u.u_EQ.rel = rel;
  v->u.u_EQ.equality = equality;
  return v;
}

// Equality_1 ["rel", "equality"]
extern TreeEquality_1 t_equality_1_NE(TreeRel rel, TreeEquality equality) {
  ALLOC(TreeEquality_1);
  v->code=TOK_NE;
  v->u.u_NE.rel = rel;
  v->u.u_NE.equality = equality;
  return v;
}

// Expr ["term", "expr"]
extern TreeExpr t_expr_term(TreeTerm term, TreeExpr expr) {
  ALLOC(TreeExpr);
  v->code=TOK_term;
  v->term = term;
  v->expr = expr;
  return v;
}

// Expr_1 ["term", "expr"]
extern TreeExpr_1 t_expr_1_term(TreeTerm term, TreeExpr expr) {
  ALLOC(TreeExpr_1);
  v->code=TOK_term;
  v->term = term;
  v->expr = expr;
  return v;
}

// Factor ["bool"]
extern TreeFactor t_factor_bool(TreeBool bool) {
  ALLOC(TreeFactor);
  v->code=TOK_bool;
  v->u.u_bool.bool = bool;
  return v;
}

// Factor []
extern TreeFactor t_factor_false() {
  ALLOC(TreeFactor);
  v->code=TOK_false;
  
  return v;
}

// Factor ["loc"]
extern TreeFactor t_factor_loc(TreeLoc loc) {
  ALLOC(TreeFactor);
  v->code=TOK_loc;
  v->u.u_loc.loc = loc;
  return v;
}

// Factor []
extern TreeFactor t_factor_num() {
  ALLOC(TreeFactor);
  v->code=TOK_num;
  
  return v;
}

// Factor []
extern TreeFactor t_factor_real() {
  ALLOC(TreeFactor);
  v->code=TOK_real;
  
  return v;
}

// Factor []
extern TreeFactor t_factor_true() {
  ALLOC(TreeFactor);
  v->code=TOK_true;
  
  return v;
}

// Join ["equality", "join"]
extern TreeJoin t_join_equality(TreeEquality equality, TreeJoin join) {
  ALLOC(TreeJoin);
  v->code=TOK_equality;
  v->equality = equality;
  v->join = join;
  return v;
}

// Join_1 ["equality", "join"]
extern TreeJoin_1 t_join_1_AND(TreeEquality equality, TreeJoin join) {
  ALLOC(TreeJoin_1);
  v->code=TOK_AND;
  v->equality = equality;
  v->join = join;
  return v;
}

// Loc ["id", "loc"]
extern TreeLoc t_loc_id(TreeId id, TreeLoc loc) {
  ALLOC(TreeLoc);
  v->code=TOK_id;
  v->id = id;
  v->loc = loc;
  return v;
}

// Loc_1 ["bool", "loc"]
extern TreeLoc_1 t_loc_1_bool(TreeBool bool, TreeLoc loc) {
  ALLOC(TreeLoc_1);
  v->code=TOK_bool;
  v->bool = bool;
  v->loc = loc;
  return v;
}

// Program ["block"]
extern TreeProgram t_program_block(TreeBlock block) {
  ALLOC(TreeProgram);
  v->code=TOK_block;
  v->block = block;
  return v;
}

// Rel ["expr"]
extern TreeRel t_rel_GE(TreeExpr expr) {
  ALLOC(TreeRel);
  v->code=TOK_GE;
  v->u.u_GE.expr = expr;
  return v;
}

// Rel ["expr"]
extern TreeRel t_rel_LE(TreeExpr expr) {
  ALLOC(TreeRel);
  v->code=TOK_LE;
  v->u.u_LE.expr = expr;
  return v;
}

// Rel ["expr"]
extern TreeRel t_rel_expr(TreeExpr expr) {
  ALLOC(TreeRel);
  v->code=TOK_expr;
  v->u.u_expr.expr = expr;
  return v;
}

// Stmt ["block"]
extern TreeStmt t_stmt_block(TreeBlock block) {
  ALLOC(TreeStmt);
  v->code=TOK_block;
  v->u.u_block.block = block;
  return v;
}

// Stmt []
extern TreeStmt t_stmt_break() {
  ALLOC(TreeStmt);
  v->code=TOK_break;
  
  return v;
}

// Stmt ["stmt", "bool"]
extern TreeStmt t_stmt_do(TreeStmt stmt, TreeBool bool) {
  ALLOC(TreeStmt);
  v->code=TOK_do;
  v->u.u_do.stmt = stmt;
  v->u.u_do.bool = bool;
  return v;
}

// Stmt ["bool", "stmt"]
extern TreeStmt t_stmt_if(TreeBool bool, TreeStmt stmt) {
  ALLOC(TreeStmt);
  v->code=TOK_if;
  v->u.u_if.bool = bool;
  v->u.u_if.stmt = stmt;
  return v;
}

// Stmt ["bool", "stmt", "stmt"]
extern TreeStmt t_stmt_if(TreeBool bool, TreeStmt stmt, TreeStmt stmt) {
  ALLOC(TreeStmt);
  v->code=TOK_if;
  v->u.u_if.bool = bool;
  v->u.u_if.stmt = stmt;
  v->u.u_if.stmt = stmt;
  return v;
}

// Stmt ["loc", "bool"]
extern TreeStmt t_stmt_loc(TreeLoc loc, TreeBool bool) {
  ALLOC(TreeStmt);
  v->code=TOK_loc;
  v->u.u_loc.loc = loc;
  v->u.u_loc.bool = bool;
  return v;
}

// Stmt ["loc"]
extern TreeStmt t_stmt_read(TreeLoc loc) {
  ALLOC(TreeStmt);
  v->code=TOK_read;
  v->u.u_read.loc = loc;
  return v;
}

// Stmt ["bool", "stmt"]
extern TreeStmt t_stmt_while(TreeBool bool, TreeStmt stmt) {
  ALLOC(TreeStmt);
  v->code=TOK_while;
  v->u.u_while.bool = bool;
  v->u.u_while.stmt = stmt;
  return v;
}

// Stmt ["bool"]
extern TreeStmt t_stmt_write(TreeBool bool) {
  ALLOC(TreeStmt);
  v->code=TOK_write;
  v->u.u_write.bool = bool;
  return v;
}

// Stmts ["stmt", "stmts"]
extern TreeStmts t_stmts_stmt(TreeStmt stmt, TreeStmts stmts) {
  ALLOC(TreeStmts);
  v->code=TOK_stmt;
  v->stmt = stmt;
  v->stmts = stmts;
  return v;
}

// Term ["unary", "term"]
extern TreeTerm t_term_unary(TreeUnary unary, TreeTerm term) {
  ALLOC(TreeTerm);
  v->code=TOK_unary;
  v->unary = unary;
  v->term = term;
  return v;
}

// Term_1 ["unary", "term"]
extern TreeTerm_1 t_term_1_unary(TreeUnary unary, TreeTerm term) {
  ALLOC(TreeTerm_1);
  v->code=TOK_unary;
  v->unary = unary;
  v->term = term;
  return v;
}

// Type ["basic", "type"]
extern TreeType t_type_basic(TreeBasic basic, TreeType type) {
  ALLOC(TreeType);
  v->code=TOK_basic;
  v->basic = basic;
  v->type = type;
  return v;
}

// Type_1 ["type"]
extern TreeType_1 t_type_1_num(TreeType type) {
  ALLOC(TreeType_1);
  v->code=TOK_num;
  v->type = type;
  return v;
}

// Unary ["factor"]
extern TreeUnary t_unary_factor(TreeFactor factor) {
  ALLOC(TreeUnary);
  v->code=TOK_factor;
  v->u.u_factor.factor = factor;
  return v;
}

// Unary ["unary"]
extern TreeUnary t_unary_unary(TreeUnary unary) {
  ALLOC(TreeUnary);
  v->code=TOK_unary;
  v->u.u_unary.unary = unary;
  return v;
}
