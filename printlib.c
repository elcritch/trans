
extern void print_TreeBlock(TreeBlock v, int d) {
   if (!v) return;
   printer("Block:", d);
   print_TreeDecls(d+1, v->decls);
   print_TreeStmts(d+1, v->stmts);
}

extern void print_TreeDecls(TreeDecls v, int d) {
   if (!v) return;
   printer("Decls:", d);
   print_TreeDecl(d+1, v->decl);
   print_TreeDecls(d+1, v->decls);
}

extern void print_TreeDecl(TreeDecl v, int d) {
   if (!v) return;
   printer("Decl:", d);
   print_TreeType(d+1, v->type);
   print_TreeId(d+1, v->id);
}

extern void print_TreeType(TreeType v, int d) {
   if (!v) return;
   printer("Type:", d);
   print_TreeBasic(d+1, v->basic);
   print_TreeType_1(d+1, v->type_1);
}

extern void print_TreeType_1(TreeType_1 v, int d) {
   if (!v) return;
   printer("Type_1:", d);
   print_TreeType_1(d+1, v->type_1);
   print_TreeNum(d+1, v->num);
}

extern void print_TreeBasic(TreeBasic v, int d) {
   if (!v) return;
   printer("Basic:", d);
   print_tok(d, v->code);
}

extern void print_TreeStmts(TreeStmts v, int d) {
   if (!v) return;
   printer("Stmts:", d);
   print_TreeStmt(d+1, v->stmt);
   print_TreeStmts(d+1, v->stmts);
}

extern void print_TreeStmt(TreeStmt v, int d) {
   if (!v) return;
   printer("Stmt:", d);
   print_tok(d, v->code);
   if (v->code == TOK_block) {
      print_TreeBlock(d+1, v->u_block.block);
   }
   if (v->code == TOK_do) {
      print_TreeStmt(d+1, v->u_do.stmt);
      print_TreeBool(d+1, v->u_do.bools);
   }
   if (v->code == TOK_if) {
      print_TreeBool(d+1, v->u_if.bools);
      print_TreeStmt(d+1, v->u_if.stmt);
      print_TreeStmt(d+1, v->u_if.else_stmt);
   }
   if (v->code == TOK_loc) {
      print_TreeLoc(d+1, v->u_loc.loc);
      print_TreeBool(d+1, v->u_loc.bools);
   }
   if (v->code == TOK_read) {
      print_TreeLoc(d+1, v->u_read.loc);
   }
   if (v->code == TOK_while) {
      print_TreeBool(d+1, v->u_while.bools);
      print_TreeStmt(d+1, v->u_while.stmt);
   }
   if (v->code == TOK_write) {
      print_TreeBool(d+1, v->u_write.bools);
   }
}

extern void print_TreeLoc(TreeLoc v, int d) {
   if (!v) return;
   printer("Loc:", d);
   print_TreeId(d+1, v->id);
   print_TreeLoc_1(d+1, v->loc_1);
}

extern void print_TreeLoc_1(TreeLoc_1 v, int d) {
   if (!v) return;
   printer("Loc_1:", d);
   print_TreeBool(d+1, v->bools);
   print_TreeLoc_1(d+1, v->loc_1);
}

extern void print_TreeBool(TreeBool v, int d) {
   if (!v) return;
   printer("Bool:", d);
   print_TreeJoin(d+1, v->join);
   print_TreeBool_1(d+1, v->bool_1);
}

extern void print_TreeBool_1(TreeBool_1 v, int d) {
   if (!v) return;
   printer("Bool_1:", d);
   print_TreeJoin(d+1, v->join);
   print_TreeBool_1(d+1, v->bool_1);
}

extern void print_TreeJoin(TreeJoin v, int d) {
   if (!v) return;
   printer("Join:", d);
   print_TreeEquality(d+1, v->equality);
   print_TreeJoin_1(d+1, v->join_1);
}

extern void print_TreeJoin_1(TreeJoin_1 v, int d) {
   if (!v) return;
   printer("Join_1:", d);
   print_TreeEquality(d+1, v->equality);
   print_TreeJoin_1(d+1, v->join_1);
}

extern void print_TreeEquality(TreeEquality v, int d) {
   if (!v) return;
   printer("Equality:", d);
   print_TreeRel(d+1, v->rel);
   print_TreeEquality_1(d+1, v->equality_1);
}

extern void print_TreeEquality_1(TreeEquality_1 v, int d) {
   if (!v) return;
   printer("Equality_1:", d);
   print_tok(d, v->code);
   if (v->code == TOK_EQ) {
      print_TreeRel(d+1, v->u_EQ.rel);
      print_TreeEquality_1(d+1, v->u_EQ.equality_1);
   }
   if (v->code == TOK_NE) {
      print_TreeRel(d+1, v->u_NE.rel);
      print_TreeEquality_1(d+1, v->u_NE.equality_1);
   }
}

extern void print_TreeRel(TreeRel v, int d) {
   if (!v) return;
   printer("Rel:", d);
   print_tok(d, v->code);
   print_TreeExpr(d+1, v->expr);
   print_TreeExpr(d+1, v->expr_1);
}

extern void print_TreeExpr(TreeExpr v, int d) {
   if (!v) return;
   printer("Expr:", d);
   print_TreeTerm(d+1, v->term);
   print_TreeExpr_1(d+1, v->expr_1);
}

extern void print_TreeExpr_1(TreeExpr_1 v, int d) {
   if (!v) return;
   printer("Expr_1:", d);
   print_tok(d, v->code);
   print_TreeTerm(d+1, v->term);
   print_TreeExpr_1(d+1, v->expr_1);
}

extern void print_TreeTerm(TreeTerm v, int d) {
   if (!v) return;
   printer("Term:", d);
   print_TreeUnary(d+1, v->unary);
   print_TreeTerm_1(d+1, v->term_1);
}

extern void print_TreeTerm_1(TreeTerm_1 v, int d) {
   if (!v) return;
   printer("Term_1:", d);
   print_tok(d, v->code);
   print_TreeUnary(d+1, v->unary);
   print_TreeTerm_1(d+1, v->term_1);
}

extern void print_TreeUnary(TreeUnary v, int d) {
   if (!v) return;
   printer("Unary:", d);
   print_tok(d, v->code);
   if (v->code == TOK_factor) {
      print_TreeFactor(d+1, v->u_factor.factor);
   }
   if (v->code == TOK_unary) {
      print_TreeUnary(d+1, v->u_unary.unary);
   }
}

extern void print_TreeFactor(TreeFactor v, int d) {
   if (!v) return;
   printer("Factor:", d);
   print_tok(d, v->code);
   if (v->code == TOK_bool) {
      print_TreeBool(d+1, v->u_bool.bools);
   }
   if (v->code == TOK_loc) {
      print_TreeLoc(d+1, v->u_loc.loc);
   }
   if (v->code == TOK_num) {
      print_TreeNum(d+1, v->u_num.num);
   }
   if (v->code == TOK_real) {
      print_TreeReal(d+1, v->u_real.real);
   }
}
