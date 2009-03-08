#include "printlib.h"
#define n 2


void printer(char *msg, int d) {
	for (int i = 0; i<d; i++) printf(" ");
	printf("%s\n",msg);
}
void printer_line(char *msg, int d) {
	for (int i = 0; i<d; i++) printf(" ");
	printf("%s",msg);
}

void print_tok(int d, int code) {
	//for (int i = 0; i<d; i++) printf(" ");
	
	printf("  token:%i:%s\n",code, tok_string(code) );
	
}


extern void print_TreeId( int d, TreeId v ) {
   if (!v) return;
   printer_line("Id:", d);
	printf("  %s\n", v->id);
}

extern void print_TreeNum( int d, TreeNum v ) {
   if (!v) return;
   printer_line("Num:", d);
	printf("  %s\n", v->num);
}

extern void print_TreeReal( int d, TreeReal v ) {
   if (!v) return;
   printer_line("Real:", d);
	printf("  %s\n", v->real);
}

char *tok_string(int tokid) {
	char *name = NULL;
	if ( tokid == TOK_ERROR )  {	name = "TOK_ERROR"; }
	if ( tokid == TOK_AND   )  {	name = "TOK_AND"; }
	if ( tokid == TOK_EQ    )  {	name = "TOK_EQ"; }
	if ( tokid == TOK_GE    )  {	name = "TOK_GE"; }
	if ( tokid == TOK_ID    )  {	name = "TOK_ID"; }
	if ( tokid == TOK_LE    )  {	name = "TOK_LE"; }
	if ( tokid == TOK_NE    )  {	name = "TOK_NE"; }
	if ( tokid == TOK_OR    )  {	name = "TOK_OR"; }
	if ( tokid == TOK_REAL  )  {	name = "TOK_REAL"; }
	if ( tokid == TOK_break )  {	name = "TOK_break"; }
	if ( tokid == TOK_do    )  {	name = "TOK_do"; }
	if ( tokid == TOK_if    )  {	name = "TOK_if"; }
	if ( tokid == TOK_else  )  {	name = "TOK_else"; }
	if ( tokid == TOK_read  )  {	name = "TOK_read"; }
	if ( tokid == TOK_REAL  )  {	name = "TOK_REAL"; }
	if ( tokid == TOK_NUM   )  {	name = "TOK_NUM"; }
	if ( tokid == TOK_int   )  {	name = "TOK_int"; }
	if ( tokid == TOK_float )  {	name = "TOK_float"; }
	if ( tokid == TOK_true  )  {	name = "TOK_true"; }
	if ( tokid == TOK_false )  {	name = "TOK_false"; }
	if ( tokid == TOK_while )  {	name = "TOK_while"; }
	if ( tokid == TOK_write )  {	name = "TOK_write"; }
	return name;
}


// auto generated code...


extern void print_TreeBlock( int d, TreeBlock v ) {
   if (!v) return;
   printer("Block:", d);
   print_TreeDecls(d+n, v->decls);
   print_TreeStmts(d+n, v->stmts);
}

extern void print_TreeDecls( int d, TreeDecls v ) {
   if (!v) return;
   printer("Decls:", d);
   print_TreeDecl(d+n, v->decl);
   print_TreeDecls(d+n, v->decls);
}

extern void print_TreeDecl( int d, TreeDecl v ) {
   if (!v) return;
   printer("Decl:", d);
   print_TreeType(d+n, v->type);
   print_TreeId(d+n, v->id);
}

extern void print_TreeType( int d, TreeType v ) {
   if (!v) return;
   printer("Type:", d);
   print_TreeBasic(d+n, v->basic);
   print_TreeType_1(d+n, v->type_1);
}

extern void print_TreeType_1( int d, TreeType_1 v ) {
   if (!v) return;
   printer("Type_1:", d);
   print_TreeType_1(d+n, v->type_1);
   print_TreeNum(d+n, v->num);
}

extern void print_TreeBasic( int d, TreeBasic v ) {
   if (!v) return;
   printer_line("Basic:", d);
   print_tok(d, v->code);
}

extern void print_TreeStmts( int d, TreeStmts v ) {
   if (!v) return;
   printer("Stmts:", d);
   print_TreeStmt(d+n, v->stmt);
   print_TreeStmts(d+n, v->stmts);
}

extern void print_TreeStmt( int d, TreeStmt v ) {
   if (!v) return;
   printer_line("Stmt:", d);
   printf(" from:\"%s\" ",v->str);
   print_tok(d, v->code);
   if (v->code == '{') {
      print_TreeBlock(d+n, v->u.u_block.block);
   }
   if (v->code == TOK_do) {
      print_TreeStmt(d+n, v->u.u_do.stmt);
      print_TreeBool(d+n, v->u.u_do.bools);
   }
   if (v->code == TOK_if) {
      print_TreeBool(d+n, v->u.u_if.bools);
      print_TreeStmt(d+n, v->u.u_if.stmt);
      print_TreeStmt(d+n, v->u.u_if.else_stmt);
   }
   if (v->code == TOK_ID) {
      print_TreeLoc(d+n, v->u.u_loc.loc);
      print_TreeBool(d+n, v->u.u_loc.bools);
   }
   if (v->code == TOK_read) {
      print_TreeLoc(d+n, v->u.u_read.loc);
   }
   if (v->code == TOK_while) {
      print_TreeBool(d+n, v->u.u_while.bools);
      print_TreeStmt(d+n, v->u.u_while.stmt);
   }
   if (v->code == TOK_write) {
      print_TreeBool(d+n, v->u.u_write.bools);
   }
}

extern void print_TreeLoc( int d, TreeLoc v ) {
   if (!v) return;
   printer("Loc:", d);
   print_TreeId(d+n, v->id);
   print_TreeLoc_1(d+n, v->loc_1);
}

extern void print_TreeLoc_1( int d, TreeLoc_1 v ) {
   if (!v) return;
   printer("Loc_1:", d);
   print_TreeBool(d+n, v->bools);
   print_TreeLoc_1(d+n, v->loc_1);
}

extern void print_TreeBool( int d, TreeBool v ) {
   if (!v) return;
   printer("Bool:", d);
   print_TreeJoin(d+n, v->join);
   print_TreeBool_1(d+n, v->bool_1);
}

extern void print_TreeBool_1( int d, TreeBool_1 v ) {
   if (!v) return;
   printer("Bool_1:", d);
   print_TreeJoin(d+n, v->join);
   print_TreeBool_1(d+n, v->bool_1);
}

extern void print_TreeJoin( int d, TreeJoin v ) {
   if (!v) return;
   printer("Join:", d);
   print_TreeEquality(d+n, v->equality);
   print_TreeJoin_1(d+n, v->join_1);
}

extern void print_TreeJoin_1( int d, TreeJoin_1 v ) {
   if (!v) return;
   printer("Join_1:", d);
   print_TreeEquality(d+n, v->equality);
   print_TreeJoin_1(d+n, v->join_1);
}

extern void print_TreeEquality( int d, TreeEquality v ) {
   if (!v) return;
   printer("Equality:", d);
   print_TreeRel(d+n, v->rel);
   print_TreeEquality_1(d+n, v->equality_1);
}

extern void print_TreeEquality_1( int d, TreeEquality_1 v ) {
   if (!v) return;
   printer_line("Equality_1:", d);
   print_tok(d, v->code);
   if (v->code == TOK_EQ) {
      print_TreeRel(d+n, v->u.u_EQ.rel);
      print_TreeEquality_1(d+n, v->u.u_EQ.equality_1);
   }
   if (v->code == TOK_NE) {
      print_TreeRel(d+n, v->u.u_NE.rel);
      print_TreeEquality_1(d+n, v->u.u_NE.equality_1);
   }
}

extern void print_TreeRel( int d, TreeRel v ) {
   if (!v) return;
   printer_line("Rel:", d);
   print_tok(d, v->code);
   print_TreeExpr(d+n, v->expr);
   print_TreeExpr(d+n, v->expr_1);
}

extern void print_TreeExpr( int d, TreeExpr v ) {
   if (!v) return;
   printer("Expr:", d);
   print_TreeTerm(d+n, v->term);
   print_TreeExpr_1(d+n, v->expr_1);
}

extern void print_TreeExpr_1( int d, TreeExpr_1 v ) {
   if (!v) return;
   printer_line("Expr_1:", d);
   print_tok(d, v->code);
   print_TreeTerm(d+n, v->term);
   print_TreeExpr_1(d+n, v->expr_1);
}

extern void print_TreeTerm( int d, TreeTerm v ) {
   if (!v) return;
   printer("Term:", d);
   print_TreeUnary(d+n, v->unary);
   print_TreeTerm_1(d+n, v->term_1);
}

extern void print_TreeTerm_1( int d, TreeTerm_1 v ) {
   if (!v) return;
   printer_line("Term_1:", d);
   print_tok(d, v->code);
   print_TreeUnary(d+n, v->unary);
   print_TreeTerm_1(d+n, v->term_1);
}

extern void print_TreeUnary( int d, TreeUnary v ) {
   if (!v) return;
   printer_line("Unary:", d);
   print_tok(d, v->code);
   if (v->code == '!' || v->code == '-') {
      print_TreeUnary(d+n, v->u.u_unary.unary);
   }
   if (v->code == 0) {
      print_TreeFactor(d+n, v->u.u_factor.factor);
   }
}

extern void print_TreeFactor( int d, TreeFactor v ) {
   if (!v) return;
   printer_line("Factor:", d);
   print_tok(d, v->code);
   if (v->code == '(') {
      print_TreeBool(d+n, v->u.u_bool.bools);
   }
   if (v->code == TOK_ID) {
      print_TreeLoc(d+n, v->u.u_loc.loc);
   }
   if (v->code == TOK_NUM) {
      print_TreeNum(d+n, v->u.u_num.num);
   }
   if (v->code == TOK_REAL) {
      print_TreeReal(d+n, v->u.u_real.real);
   }
}