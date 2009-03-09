#include "generator.h"

#define generate(name) if (name) g_#name
#define gen_term(name, term) if (term) g_#name


// ====================================================================
extern void generate(TreeBlock block) {
   if (!block) return;
   
   g_decls(block->decls, block->block);
   g_block(block->decls, block->block);
}

// ====================================================================
static void g_block(TreeDecls decls, TreeStmts stmts) {
   Type ret;
   gen(decls, decl, decls);
   gen(stmts, stmt, stmts);

}

// ====================================================================
static void g_decls(TreeDecl decl, TreeDecls decls) {
   Type ret;
   gen(decl, id);
   gen(decls, decl, decls);

}
static void g_decl(TreeId id) {
   Type ret;

}


// ====================================================================
static void g_stmts(TreeStmt stmt, TreeStmts stmts) {
   Type ret;
   gen(stmt,);
   gen(stmts,);

}

// ====================================================================
static void g_stmt(TreeStmt stmt) {
   Type ret;
   gen(stmt,);

}

static void g_stmt_loc(TreeLoc loc, TreeBool bools) {
   Type ret;

}

static void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt) {
   Type ret;

}

static void g_stmt_while(TreeBool bools, TreeStmt stmt) {
   Type ret;

}

static void g_stmt_do(TreeStmt stmt, TreeBool bools) {
   Type ret;

}

static void g_stmt_break() {
   Type ret;

}

static void g_stmt_block(TreeBlock block) {
   Type ret;

}

static void g_stmt_read(TreeLoc loc) {
   Type ret;

}

static void g_stmt_write(TreeBool bools) {
   Type ret;

}


// ====================================================================
static void g_loc(TreeId id, TreeLoc_1 loc_1) {
   Type ret;
}
static void g_loc_1(TreeBool bools, TreeLoc_1 loc_1) {
   Type ret;
   gen(bools, join, bools_1);
   gen(loc_1, bools, loc_1);

}

// ====================================================================
static void g_bool(TreeJoin join, TreeBool_1 bool_1) {
   Type ret;
   gen(join, equality, join_1);
   gen(bool_1, equality, join_1);

}
static void g_bool_1(TreeJoin join, TreeBool_1 bool_1) {
   Type ret;
   gen(join, equality, join_1);
   gen(bool_1, join, bool_1);

}

// ====================================================================
static void g_join(TreeEquality equality, TreeJoin_1 join_1) {
   Type ret;
   gen(equality, rel, equality_1);
   gen(join_1, equality, join_1);

}

static void g_join_1(TreeEquality equality, TreeJoin_1 join_1) {
   Type ret;
   gen(equality, rel, equality_1);
   gen(join_1, equality, join_1);

}


// ====================================================================
static void g_equality(TreeRel rel, TreeEquality_1 equality_1) {
   Type ret;
   g_rel(rel);
   g_equality_1(TreeRel rel);
   
}

static void g_equality_1(TreeRel rel, TreeEquality_1 equality_1) {
   Type ret;
   g_rel(rel);
   gen_union(equality_1, );
   
}

static Type g_rel(TreeRel rel) {
   Type ret;
   
   TokenCode code = rel->code;
   gen_struct2(rel->expr, term, expr_1);
   
   switch (code) {
      case '<': {
         emit_inst("mul");
         break;
      } 
      case '>': {
         emit_inst("mul");
         break;
      } 
      case TOK_LT: {
         emit_inst("mul");
         break;
      } 
      case TOK_GT: {
         emit_inst("mul");
         break;
      } 
      default: {
         error_parse("gen:err:rel");
         kill(getpid(),SIGINT);
         break; 
      }     
   }
   
}


// ====================================================================
static void g_expr(TreeTerm term, TreeExpr_1 expr_1) {
   Type ret;
   
   gen_struct2(term, unary, term_1);
   gen_struct3(expr_1, code, term, expr_1);

}

static Type t_expr_1_term(TokenCode code, TreeTerm term, TreeExpr_1 expr_1) {
   Type ret;
   
   gen_struct2(term, unary, term_1);
   opt_gen_struct3(expr_1, code, term, expr_1);
   
}


// ====================================================================
static void g_term(TreeUnary unary, TreeTerm_1 term_1) {
   Type ret;
   
   gen_union(unary, unary);
   gen_struct3(term_1, code, unary, term_1);
}

static Type g_term_1(TokenCode code, TreeUnary unary, TreeTerm_1 term_1) {
   Type ret;   
   
   gen_union(unary, unary);
   
   switch (code) {
      case '*' {
         emit_inst("mul");
         break;
      } 
      case '/': {
         emit_inst("div");
         break;
      } 
      default: {
         error_parse("gen:err:term_1");
         kill(getpid(),SIGINT);
      }
   }
   
   opt_gen_struct3(term_1, code, unary, term_1);
   
}


// ====================================================================
static Type g_unary(TreeUnary unary) {
   Type ret;
   if (!factor) return;
   
   Type ret;
   TokenCode code = factor->code;
   
   switch (code) {
      case '!': {  
         gen_union(unary, unary);
         emit_inst2("not", 1);
         break;
      }
      case '-': {
         gen_union(unary, unary);
         emit_inst2("sub", 1);
      }
      default: {
         gen_union(factor, unary);
         break; 
      }     
   }
}


// ====================================================================
static Type g_factor(TreeFactor factor) {
   if (!factor) return;
   
   Type ret;
   TokenCode code = factor->code;
   
   // emit_ins2();
   // emit_ins1();
   
   switch (code) {
      case '(': {  
         gen_struct2(bools, join, bool_1);
         break;
      }
      case TOK_ID: {  //===== REDUCED TOK_loc
         gen_struct2(loc, id, loc_1);
         break;
      }
      case TOK_NUM: {  
         emit_inst2("push",factor->u_num.num->num);
         break;
      }
      case TOK_REAL: {  
         emit_inst2("push",factor->u_real.real->real);         
         break;
      }
      case TOK_true: {  
         emit_inst2("push", 1);
         break;
      }
      case TOK_false: {  
         emit_inst2("push", 0);
         break;
      }
      default: {
         error_parse("gen:err:factor");
         kill(getpid(),SIGINT);
         break;
      }
   }   

}
