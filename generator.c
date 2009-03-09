#include "generator.h"
#include <signal.h>

#define GEN(name) g_##name(var->name)
#define OPT_GEN(name) if (var->name) g_##name(var->name)

void emit_inst(char *inst);
void emit_inst2(char *inst, char *arg);

// ====================================================================
extern void generate(TreeBlock block) {
   if (!block) return;
      
   g_block(block);
   
}

// ====================================================================
static void g_block(TreeBlock var) {
   GEN(decls);
   GEN(stmts);
}

// ====================================================================
static void g_decls(TreeDecls var) {
   GEN(decl);
   OPT_GEN(decls);
}
static void g_decl(TreeDecl var) {
   
}


// ====================================================================
// ====================================================================

static void g_stmts(TreeStmts var) {
   GEN(stmt);
   OPT_GEN(stmts);
}

static void g_stmt(TreeStmt v) {
   if (!v) return;
   
   switch (v->code) {
      case TOK_ID:
         g_stmt_loc( v->u.u_loc.loc, v->u.u_loc.bools );            
         break;
      case  TOK_if:
         g_stmt_if( v->u.u_if.bools, v->u.u_if.stmt, v->u.u_if.else_stmt);                             
         break;
      case  TOK_while:
         g_stmt_while( v->u.u_while.bools, v->u.u_while.stmt );
         break;
      case  TOK_do:
         g_stmt_do( v->u.u_do.stmt, v->u.u_do.bools );
         break;
      case  TOK_break:
         g_stmt_break();          
         break;
      case  '{':
         g_stmt_block( v->u.u_block.block );
         break;
      case  TOK_read:
         g_stmt_read(v->u.u_read.loc);  
         break;
      case  TOK_write:
         g_stmt_write(v->u.u_write.bools);
         break;
      default:
         ERR("bad stmt");  
         break;
   }
}

// ====================================================================

static void g_stmt_loc(TreeLoc loc, TreeBool bools) {

}

static void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt) {

}

static void g_stmt_while(TreeBool bools, TreeStmt stmt) {

}

static void g_stmt_do(TreeStmt stmt, TreeBool bools) {

}

static void g_stmt_break() {

}

static void g_stmt_block(TreeBlock block) {

}

static void g_stmt_read(TreeLoc loc) {

}

static void g_stmt_write(TreeBool bools) {

}


// ====================================================================
// Structure: loc [["id", ["id", "loc_1"]]]
static void g_loc(TreeLoc var) {
   // GEN(id);
   GEN(loc_1);

}

// Structure: loc_1 [["bools", ["bools", "loc_1"]]]
static void g_loc_1(TreeLoc_1 var) {
   GEN(bools);
   GEN(loc_1);

}

// Structure: bools [["join", ["join", "bool_1"]]]
static Type g_bools(TreeBool var) {
   Type ret = 0; 
   GEN(join);
   GEN(bool_1);
   
   return ret;
}

// Structure: bool_1 [["OR", ["join", "bool_1"]]]
static Type g_bool_1(TreeBool_1 var) {
   Type ret = 0; 
   GEN(join);
   GEN(bool_1);

   
   return ret;
}

// Structure: join [["equality", ["equality", "join_1"]]]
static Type g_join(TreeJoin var) {
   Type ret = 0; 
   GEN(equality);
   GEN(join_1);

   
   return ret;
}

// Structure: join_1 [["AND", ["equality", "join_1"]]]
static Type g_join_1(TreeJoin_1 var) {
   Type ret = 0; 
   GEN(equality);
   GEN(join_1);

   
   return ret;
}

// Structure: equality [["rel", ["rel", "equality_1"]]]
static Type g_equality(TreeEquality var) {
   Type ret = 0; 
   GEN(rel);
   GEN(equality_1);

   
   return ret;
}

// Structure: equality_1 [["EQ", ["rel", "equality_1"]], ["NE", ["rel", "equality_1"]]]
static Type g_equality_1(TreeEquality_1 var) {
   Type ret = 0; 
   TokenCode code = var->code;
   
   g_rel(var->u.u_EQ.rel);
   
   if (var->u.u_EQ.equality_1)
      g_equality_1(var->u.u_EQ.equality_1);
   
   switch(code) {
      case TOK_EQ:
         break;
      case TOK_NE:
         break;
      default:
         break;
   }
   
   return ret;
}


// ====================================================================


static Type g_rel(TreeRel var) {
   Type ret = 0; 
   
   TokenCode code = var->code;
   code = var->code;
   GEN(expr);
   if (var->expr1) {
      /** TODO: print comparison code
      */
   }
   
   return ret;
}


// ====================================================================
static Type g_expr(TreeExpr var) {
   Type ret = 0; 
   GEN(term);
   GEN(expr_1);   
   
   return ret;
}

static Type g_expr_1(TreeExpr_1 var) {
   Type ret = 0; 
   GEN(term);
   OPT_GEN(expr_1);
   
   return ret;
};


// ====================================================================
static Type g_term(TreeTerm var) {
   Type ret = 0; 
   GEN(unary);
   GEN(term_1);
   
   return ret;
}

static Type g_term_1(TreeTerm_1 var) {
   Type ret;   
   
   TokenCode code = var->code;
   
   GEN(unary);
   OPT_GEN(term_1);
   
   switch (code) {
      case '*': {
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
   
   return ret;
}


// ====================================================================
static Type g_unary(TreeUnary var) {
   Type ret = 0; 
   TokenCode code = var->code;
   
   switch (code) {
      case '!': {  
         g_unary(var->u.u_unary.unary);
         emit_inst("not");
         break;
      }
      case '-': {
         g_unary(var->u.u_unary.unary);
         emit_inst("sub");
      }
      default: {
         g_factor(var->u.u_factor.factor);
         break; 
      }     
   }
   
   return ret;
}


// ====================================================================
static Type g_factor(TreeFactor var) {
   Type ret = 0; 
   TokenCode code = var->code;
   
   // emit_ins2();
   // emit_ins1();
   
   switch (code) {
      case '(': {  
         g_bools(var->u.u_bool.bools);
         break;
      }
      case TOK_ID: {  //===== REDUCED TOK_loc
         g_loc(var->u.u_loc.loc);
         break;
      }
      case TOK_NUM: {
         emit_inst2("push",var->u.u_num.num->num);
         break;
      }
      case TOK_REAL: {
         emit_inst2("push",var->u.u_real.real->real);         
         break;
      }
      case TOK_true: {  
         emit_inst2("push", "1");
         break;
      }
      case TOK_false: {  
         emit_inst2("push", "0");
         break;
      }
      default: {
         error_parse("gen:err:factor");
         kill(getpid(),SIGINT);
         break;
      }
   }   

   
   return ret;
}
