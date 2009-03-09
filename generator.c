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
// Structure: loc [["id", ["id", "loc_1"]]]
static Type g_loc(TreeLoc loc) {
   Type ret; 
   TreeId id = var->id;
   g_id(id);
   TreeLoc_1 loc_1 = var->loc_1;
   g_loc_1(loc_1);

}

// Structure: loc_1 [["bools", ["bools", "loc_1"]]]
static Type g_loc_1(TreeLoc_1 loc_1) {
   Type ret; 
   TreeBool bools = var->bools;
   g_bools(bools);
   TreeLoc_1 loc_1 = var->loc_1;
   g_loc_1(loc_1);

}

// Structure: bools [["join", ["join", "bool_1"]]]
static Type g_bool(TreeBool bool) {
   Type ret; 
   TreeJoin join = var->join;
   g_join(join);
   TreeBool_1 bool_1 = var->bool_1;
   g_bool_1(bool_1);

}

// Structure: bool_1 [["OR", ["join", "bool_1"]]]
static Type g_bool_1(TreeBool_1 bool_1) {
   Type ret; 
   TreeJoin join = var->join;
   g_join(join);
   TreeBool_1 bool_1 = var->bool_1;
   g_bool_1(bool_1);

}

// Structure: join [["equality", ["equality", "join_1"]]]
static Type g_join(TreeJoin join) {
   Type ret; 
   TreeEquality equality = var->equality;
   g_equality(equality);
   TreeJoin_1 join_1 = var->join_1;
   g_join_1(join_1);

}

// Structure: join_1 [["AND", ["equality", "join_1"]]]
static Type g_join_1(TreeJoin_1 join_1) {
   Type ret; 
   TreeEquality equality = var->equality;
   g_equality(equality);
   TreeJoin_1 join_1 = var->join_1;
   g_join_1(join_1);

}

// Structure: equality [["rel", ["rel", "equality_1"]]]
static Type g_equality(TreeEquality equality) {
   Type ret; 
   TreeRel rel = var->rel;
   g_rel(rel);
   TreeEquality_1 equality_1 = var->equality_1;
   g_equality_1(equality_1);

}

// Structure: equality_1 [["EQ", ["rel", "equality_1"]], ["NE", ["rel", "equality_1"]]]
static Type g_equality_1(TreeEquality_1 equality_1) {
   Type ret; 
  TokenCode code = equality_1->code;
  
  switch(code) {
    case TOK_EQ: {
      equality_1->u_EQ->rel;
      equality_1->u_EQ->equality_1;
    } ;
    case TOK_NE: {
      equality_1->u_NE.rel;
      equality_1->u_NE.equality_1;
    }
  }

}


// ====================================================================


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
static void g_expr(TreeExpr var) {
   Type ret;
   g_term(var->term);
   g_expr_1(var->expr_1);   
}

static void g_expr_1(TreeExpr_1 var) {
   Type ret;
  g_term(var->term);
  g_expr_1(var->expr_1);
};


// ====================================================================
static void g_term(TreeTerm var) {
   Type ret;
   g_unary(var->unary);
   g_term_1(var->term_1);
}

static Type g_term_1(TreeTerm_1 var) {
   Type ret;   
   
   TokenCode code = var->code;
   TreeUnary unary = var->unary;
   TreeTerm_1 term_1 = var->term_1;
   
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
   
   GEN(term_1);
   
}


// ====================================================================
static Type g_unary(TreeUnary unary) {
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
   Type ret;
   TokenCode code = factor->code;
   
   // emit_ins2();
   // emit_ins1();
   
   switch (code) {
      case '(': {  
         g_bools( join, bool_1);
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
