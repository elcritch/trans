#include "tree.h"
#include "printlib.h"

// ====================================================================
extern void generate(TreeBlock block);

void g_block(TreeDecls decls, TreeStmts stmts);

// ====================================================================
void g_decls(TreeDecl decl, TreeDecls decls);
void g_decl(TreeId id);


// ====================================================================
void g_stmts(TreeStmt stmt, TreeStmts stmts);

// ====================================================================
void g_stmt(TreeStmt stmt);

void g_stmt_loc(TreeLoc loc, TreeBool bools);

void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt);

void g_stmt_while(TreeBool bools, TreeStmt stmt);

void g_stmt_do(TreeStmt stmt, TreeBool bools);

void g_stmt_break();

void g_stmt_block(TreeBlock block);

void g_stmt_read(TreeLoc loc);

void g_stmt_write(TreeBool bools);


// ====================================================================
Type g_loc(TreeId id, TreeLoc_1 loc_1);
Type g_loc_1(TreeBool bools, TreeLoc_1 loc_1);

// ====================================================================
Type g_bool(TreeJoin join, TreeBool_1 bool_1);
Type g_bool_1(TreeJoin join, TreeBool_1 bool_1);

// ====================================================================
Type g_join(TreeEquality equality, TreeJoin_1 join_1);
Type g_join_1(TreeEquality equality, TreeJoin_1 join_1);


// ====================================================================
Type g_equality(TreeRel rel, TreeEquality_1 equality_1);
Type g_rel(TokenCode code, TreeExpr expr1, TreeExpr expr2);


// ====================================================================
Type g_expr(TreeTerm term, TreeExpr_1 expr_1);
Type t_expr_1_term(TokenCode code, TreeTerm term, TreeExpr_1 expr_1);


// ====================================================================
Type g_term(TreeUnary unary, TreeTerm_1 term_1);
Type g_term_1(TokenCode code, TreeUnary unary, TreeTerm_1 term_1);

// ====================================================================
Type g_unary_factor(TreeFactor factor);
Type g_unary_unary(TokenCode code, TreeUnary unary);


// ====================================================================
Type g_factor(TreeFactor factor);


/*
static void g_stmt(TreeStmt stmt) {
  if (!stmt)
    return;
  switch (stmt->code) {
    case TOK_ID:    g_stmt_assign(stmt);            break;
    case TOK_while: g_stmt_while(stmt);             break;
    case TOK_break: g_stmt_break(stmt);             break;
    default:        ERR("bad stmt");                break;
  }
}


static void g_stmt_while(TreeStmt stmt) {
  Type bool;
  char *ltop=gen_label();
  char *lend=gen_label();
  emit_label(ltop);
  g_bool(stmt->u.u_while.bool,&bool);
  type_or(&bool,&bool);
  emit_ins2("push",lend);
  emit_ins1("jz");
  g_stmt(stmt->u.u_while.stmt);
  emit_ins2("push",ltop);
  emit_ins1("jmp");
  emit_label(lend);
}
*/
