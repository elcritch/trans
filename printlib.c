#include "printlib.h"

void printer(char *msg, int d) {
	for (int i = 0; i<d; i++) printf(" ");
	printf("%s\n",msg);
}

void print_tok(int d, int code) {
	for (int i = 0; i<d; i++) printf(" ");
	printf("token:%i\n",code);
}


extern void print_TreeId( int d, TreeId v ) {
   if (!v) return;
   printer("Id:", d);
	printer(v->id, d);
}

extern void print_TreeNum( int d, TreeNum v ) {
   if (!v) return;
   printer("Num:", d);
	printer(v->num, d);
}

extern void print_TreeReal( int d, TreeReal v ) {
   if (!v) return;
   printer("Real:", d);
	printer(v->real, d);
}

// auto generated code...


extern void print_TreeBlock( int d, TreeBlock v ) {
   if (!v) return;
   printer("Block:", d);
   print_TreeDecls(d+1, v->decls);
   print_TreeStmts(d+1, v->stmts);
}

extern void print_TreeDecls( int d, TreeDecls v ) {
   if (!v) return;
   printer("Decls:", d);
   print_TreeDecl(d+1, v->decl);
   print_TreeDecls(d+1, v->decls);
}

extern void print_TreeDecl( int d, TreeDecl v ) {
   if (!v) return;
   printer("Decl:", d);
   print_TreeType(d+1, v->type);
   print_TreeId(d+1, v->id);
}

extern void print_TreeType( int d, TreeType v ) {
   if (!v) return;
   printer("Type:", d);
   print_TreeBasic(d+1, v->basic);
   print_TreeType_1(d+1, v->type_1);
}

extern void print_TreeType_1( int d, TreeType_1 v ) {
   if (!v) return;
   printer("Type_1:", d);
   print_TreeType_1(d+1, v->type_1);
   print_TreeNum(d+1, v->num);
}

extern void print_TreeBasic( int d, TreeBasic v ) {
   if (!v) return;
   printer("Basic:", d);
   print_tok(d, v->code);
}

extern void print_TreeStmts( int d, TreeStmts v ) {
   if (!v) return;
   printer("Stmts:", d);
   print_TreeStmt(d+1, v->stmt);
   print_TreeStmts(d+1, v->stmts);
}

extern void print_TreeStmt( int d, TreeStmt v ) {
   if (!v) return;
   printer("Stmt:", d);
   print_tok(d, v->code);
   if (v->code == '{') {
      print_TreeBlock(d+1, v->u.u_block.block);
   }
   if (v->code == TOK_do) {
      print_TreeStmt(d+1, v->u.u_do.stmt);
      print_TreeBool(d+1, v->u.u_do.bools);
   }
   if (v->code == TOK_if) {
      print_TreeBool(d+1, v->u.u_if.bools);
      print_TreeStmt(d+1, v->u.u_if.stmt);
      print_TreeStmt(d+1, v->u.u_if.else_stmt);
   }
   if (v->code == TOK_ID) {
      print_TreeLoc(d+1, v->u.u_loc.loc);
      print_TreeBool(d+1, v->u.u_loc.bools);
   }
   if (v->code == TOK_read) {
      print_TreeLoc(d+1, v->u.u_read.loc);
   }
   if (v->code == TOK_while) {
      print_TreeBool(d+1, v->u.u_while.bools);
      print_TreeStmt(d+1, v->u.u_while.stmt);
   }
   if (v->code == TOK_write) {
      print_TreeBool(d+1, v->u.u_write.bools);
   }
}

extern void print_TreeLoc( int d, TreeLoc v ) {
   if (!v) return;
   printer("Loc:", d);
   print_TreeId(d+1, v->id);
   print_TreeLoc_1(d+1, v->loc_1);
}

extern void print_TreeLoc_1( int d, TreeLoc_1 v ) {
   if (!v) return;
   printer("Loc_1:", d);
   print_TreeBool(d+1, v->bools);
   print_TreeLoc_1(d+1, v->loc_1);
}

extern void print_TreeBool( int d, TreeBool v ) {
   if (!v) return;
   printer("Bool:", d);
   print_TreeJoin(d+1, v->join);
   print_TreeBool_1(d+1, v->bool_1);
}

extern void print_TreeBool_1( int d, TreeBool_1 v ) {
   if (!v) return;
   printer("Bool_1:", d);
   print_TreeJoin(d+1, v->join);
   print_TreeBool_1(d+1, v->bool_1);
}

extern void print_TreeJoin( int d, TreeJoin v ) {
   if (!v) return;
   printer("Join:", d);
   print_TreeEquality(d+1, v->equality);
   print_TreeJoin_1(d+1, v->join_1);
}

extern void print_TreeJoin_1( int d, TreeJoin_1 v ) {
   if (!v) return;
   printer("Join_1:", d);
   print_TreeEquality(d+1, v->equality);
   print_TreeJoin_1(d+1, v->join_1);
}

extern void print_TreeEquality( int d, TreeEquality v ) {
   if (!v) return;
   printer("Equality:", d);
   print_TreeRel(d+1, v->rel);
   print_TreeEquality_1(d+1, v->equality_1);
}

extern void print_TreeEquality_1( int d, TreeEquality_1 v ) {
   if (!v) return;
   printer("Equality_1:", d);
   print_tok(d, v->code);
   if (v->code == TOK_EQ) {
      print_TreeRel(d+1, v->u.u_EQ.rel);
      print_TreeEquality_1(d+1, v->u.u_EQ.equality_1);
   }
   if (v->code == TOK_NE) {
      print_TreeRel(d+1, v->u.u_NE.rel);
      print_TreeEquality_1(d+1, v->u.u_NE.equality_1);
   }
}

extern void print_TreeRel( int d, TreeRel v ) {
   if (!v) return;
   printer("Rel:", d);
   print_tok(d, v->code);
   print_TreeExpr(d+1, v->expr);
   print_TreeExpr(d+1, v->expr_1);
}

extern void print_TreeExpr( int d, TreeExpr v ) {
   if (!v) return;
   printer("Expr:", d);
   print_TreeTerm(d+1, v->term);
   print_TreeExpr_1(d+1, v->expr_1);
}

extern void print_TreeExpr_1( int d, TreeExpr_1 v ) {
   if (!v) return;
   printer("Expr_1:", d);
   print_tok(d, v->code);
   print_TreeTerm(d+1, v->term);
   print_TreeExpr_1(d+1, v->expr_1);
}

extern void print_TreeTerm( int d, TreeTerm v ) {
   if (!v) return;
   printer("Term:", d);
   print_TreeUnary(d+1, v->unary);
   print_TreeTerm_1(d+1, v->term_1);
}

extern void print_TreeTerm_1( int d, TreeTerm_1 v ) {
   if (!v) return;
   printer("Term_1:", d);
   print_tok(d, v->code);
   print_TreeUnary(d+1, v->unary);
   print_TreeTerm_1(d+1, v->term_1);
}

extern void print_TreeUnary( int d, TreeUnary v ) {
   if (!v) return;
   printer("Unary:", d);
   print_tok(d, v->code);
   if (v->code == '!' || v->code == '-') {
      print_TreeFactor(d+1, v->u.u_factor.factor);
   }
   if (v->code == 0) {
      print_TreeUnary(d+1, v->u.u_unary.unary);
   }
}

extern void print_TreeFactor( int d, TreeFactor v ) {
   if (!v) return;
   printer("Factor:", d);
   print_tok(d, v->code);
   if (v->code == '(') {
      print_TreeBool(d+1, v->u.u_bool.bools);
   }
   if (v->code == TOK_ID) {
      print_TreeLoc(d+1, v->u.u_loc.loc);
   }
   if (v->code == TOK_num) {
      print_TreeNum(d+1, v->u.u_num.num);
   }
   if (v->code == TOK_real) {
      print_TreeReal(d+1, v->u.u_real.real);
   }
}