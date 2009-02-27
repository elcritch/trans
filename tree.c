#define ALLOC(t) \
  t v=malloc(sizeof(*v)); \
  if (!v) ERR("malloc() failed")

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
