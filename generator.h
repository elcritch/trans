#include "tree.h"
#include "terminals.h"
#include "printlib.h"

// ====================================================================
typedef struct gen_type *Type;

extern void generate(TreeBlock block);

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
