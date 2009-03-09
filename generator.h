#include "tree.h"
#include "terminals.h"
#include "printlib.h"

// ====================================================================
typedef struct gen_type *Type;

extern void generate(TreeBlock block);

static void g_id(TreeId var);
static void g_block(TreeBlock var);
static void g_decls(TreeDecls var);
static void g_decl(TreeDecl var);
static void g_stmts(TreeStmts var);
static void g_stmt(TreeStmt v);
static void g_stmt_loc(TreeLoc loc, TreeBool bools);
static void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt);
static void g_stmt_while(TreeBool bools, TreeStmt stmt);
static void g_stmt_do(TreeStmt stmt, TreeBool bools);
static void g_stmt_break();
static void g_stmt_block(TreeBlock block);
static void g_stmt_read(TreeLoc loc);
static void g_stmt_write(TreeBool bools);
static void g_loc(TreeLoc var);
static void g_loc_1(TreeLoc_1 var);
static Type g_bools(TreeBool var);
static Type g_bool_1(TreeBool_1 var);
static Type g_join(TreeJoin var);
static Type g_join_1(TreeJoin_1 var);
static Type g_equality(TreeEquality var);
static Type g_equality_1(TreeEquality_1 var);
static Type g_rel(TreeRel var);
static Type g_expr(TreeExpr var);
static Type g_expr_1(TreeExpr_1 var);
static Type g_term(TreeTerm var);
static Type g_term_1(TreeTerm_1 var);
static Type g_unary(TreeUnary var);
static Type g_factor(TreeFactor var);

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
