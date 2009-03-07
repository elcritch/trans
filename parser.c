#include "tree.h"
#include "terminals.h"
// #include "symtaben.h"
#include "scanner/scanner.h"
#include "scanner/token.h"

#include <setjmp.h>
#include <signal.h>

static TreeBlock p_block(void) ;
static TreeDecls p_decls(void) ;
static TreeDecl p_decl(void) ;
static TreeType p_type(void) ;
static TreeType_1 p_type_1(void) ;
static TreeBasic p_basic(void) ;
static TreeStmts p_stmts(void) ;
static TreeStmt p_stmt(void) ;
static TreeLoc p_loc(void) ;
static TreeLoc_1 p_loc_1(void) ;
static TreeBool p_bool(void) ;
static TreeBool_1 p_bool_1(void) ;
static TreeJoin p_join(void) ;
static TreeJoin_1 p_join_1(void) ;
static TreeEquality p_equality(void) ;
static TreeEquality_1 p_equality_1(void) ;
static TreeRel p_rel(void) ;
static TreeExpr p_expr(void) ;
static TreeExpr_1 p_expr_1(void) ;
static TreeTerm p_term(void) ;
static TreeTerm_1 p_term_1(void) ;
static TreeUnary p_unary(void) ;
static TreeFactor p_factor(void) ;


jmp_buf env;

/**
==================== Program ==========================================
   Grammar:
      Program : block 
*/
extern TreeBlock Program(void) {
   // setjmp(env);
   TreeBlock block = p_block();
   return block;
}


/**
==================== Block ============================================
   Grammar:
      block : '{' decls stmts '}' 
*/
static TreeBlock p_block(void)  {
   printf("Block\n");
   TreeBlock block = 0; // set null by default

   // body
   eat('{');
   TreeDecls l1decls = p_decls();
   TreeStmts l2stmts = p_stmts();
   eat('}');
   block = t_block_decls(l1decls, l2stmts);

   return block;
}


/**
==================== Decls ============================================
   Grammar:
      decls : decl decls |  e
*/
static TreeDecls p_decls(void)  {
   printf("Decls\n");
   TreeDecls decls = 0; // set null by default
   TokenCode code = curr()->code;
   // body
	TreeDecl l0decl = p_decl();
   
   // check if we have next production, return on zero
   code = curr()->code;
   if ( code != TOK_int && code != TOK_REAL  ) 
      return t_decls_decl(l0decl, 0);
	
	// if found type then another type continue
   TreeDecls l1decls = p_decls();
   decls = t_decls_decl(l0decl, l1decls);
  	
   return decls;
}


/**
==================== Decl =============================================
   Grammar:
      decl : type id ';' 
*/
static TreeDecl p_decl(void)  {
   printf("Decl\n");
   TreeDecl decl = 0; // set null by default
	
   // body
   TreeType l0type = p_type();
   TreeId l1id = p_id();
	
	// add id to symbol table;
	
	
   eat(';');
   decl = t_decl_type(l0type, l1id);

   return decl;
}


/**
==================== Type =============================================
   Grammar:
      type : basic type_1 
*/
static TreeType p_type(void)  {
   printf("Type\n");
   TreeType type = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeBasic l0basic = p_basic();
   TreeType_1 l1type_1 = p_type_1();
   type = t_type_basic(l0basic, l1type_1);
   
   return type;
}


/**
==================== Type_1 ===========================================
   Grammar:
      type_1 : '[' num ']' type_1 |  e
*/
static TreeType_1 p_type_1(void)  {
   printf("Type_1\n");
   TreeType_1 type_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '[': {  
         eat('[');
         TreeNum l1num = p_num();
         eat(']');
         TreeType_1 l3type_1 = p_type_1();
         type_1 = t_type_1_num(l1num, l3type_1);
         break;
      }

      default:
         break;
   }   

   
   return type_1;
}


/**
==================== Basic ============================================
   Grammar:
      basic : 'int' | 'float' 
*/
static TreeBasic p_basic(void)  {
   printf("Basic\n");
   TreeBasic basic = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_int: {  
         eat(TOK_int);
         basic = t_basic_int();
         break;
      }
      case TOK_float: {  
         eat(TOK_float);
         basic = t_basic_float();
         break;
      }
      default:
         error_parse("basic");
         // longjmp(env,1);
         kill(getpid(),SIGINT);
         break;
   }

   
   return basic;
}


/**
==================== Stmts ============================================
   Grammar:
      stmts : stmt stmts |  e
*/
static TreeStmts p_stmts(void)  {
   printf("Stmts\n");
   TreeStmts stmts = 0; // set null by default
   TokenCode code = curr()->code;

   // body
	if ( code == '}' ) 
      return stmts = 0;
   
	TreeStmt l0stmt = p_stmt();   
   TreeStmts l1stmts = p_stmts();
   stmts = t_stmts_stmt(l0stmt, l1stmts);

   return stmts;
}


/**
==================== Stmt =============================================
   Grammar:
      stmt : loc '=' bool ';' | 'if' '(' bool ')' stmt | 'if' '(' bool ')' stmt 'else' stmt | 'while' '(' bool ')' stmt | 'do' stmt 'while' '(' bool ')' ';' | 'break' ';' | block | 'read' loc ';' | 'write' bool ';' 
*/
static TreeStmt p_stmt(void)  {
   printf("Stmt\n");
   TreeStmt stmt = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_ID: {  //===== REDUCED TOK_loc
         TreeLoc l0loc = p_loc();
         eat('=');
         TreeBool l2bool = p_bool();
         eat(';');
         stmt = t_stmt_loc(l0loc, l2bool);
         break;
      }
      case TOK_if: {  
         eat(TOK_if);
         eat('(');
         TreeBool l2bool = p_bool();
         eat(')');
         TreeStmt l4stmt = p_stmt();
			
         TreeStmt l6stmt = 0;
			TokenCode code = curr()->code;
			if (code == TOK_else) {
	         eat(TOK_else);
	         l6stmt = p_stmt();
			}
         stmt = t_stmt_if(l2bool, l4stmt, l6stmt);
         break;
      }
      case TOK_while: {  
         eat(TOK_while);
         eat('(');
         TreeBool l2bool = p_bool();
         eat(')');
         TreeStmt l4stmt = p_stmt();
         stmt = t_stmt_while(l2bool, l4stmt);
         break;
      }
      case TOK_do: {  
         eat(TOK_do);
         TreeStmt l1stmt = p_stmt();
         eat(TOK_while);
         eat('(');
         TreeBool l4bool = p_bool();
         eat(')');
         eat(';');
         stmt = t_stmt_do(l1stmt, l4bool);
         break;
      }
      case TOK_break: {  
         eat(TOK_break);
         eat(';');
         stmt = t_stmt_break();
         break;
      }
      case '{': {  //===== REDUCED TOK_block
         TreeBlock l0block = p_block();
         stmt = t_stmt_block(l0block);
         break;
      }
      case TOK_read: {  
         eat(TOK_read);
         TreeLoc l1loc = p_loc();
         eat(';');
         stmt = t_stmt_read(l1loc);
         break;
      }
      case TOK_write: {  
         eat(TOK_write);
         TreeBool l1bool = p_bool();
         eat(';');
         stmt = t_stmt_write(l1bool);
         break;
      }
      default:
         error_parse("stmt");
         // longjmp(env,1);
         kill(getpid(),SIGINT);
         break;
   }   

   
   return stmt;
}


/**
==================== Loc ==============================================
   Grammar:
      loc : id loc_1 
*/
static TreeLoc p_loc(void)  {
   printf("Loc\n");
   TreeLoc loc = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeId l0id = p_id();
   TreeLoc_1 l1loc_1 = p_loc_1();
   loc = t_loc_id(l0id, l1loc_1);

   
   return loc;
}


/**
==================== Loc_1 ============================================
   Grammar:
      loc_1 : '[' bool ']' loc_1 |  e
*/
static TreeLoc_1 p_loc_1(void)  {
   printf("Loc_1\n");
   TreeLoc_1 loc_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '[': {  
         eat('[');
         TreeBool l1bool = p_bool();
         eat(']');
         TreeLoc_1 l3loc_1 = p_loc_1();
         loc_1 = t_loc_1_bool(l1bool, l3loc_1);
         break;
      }

      default:
         break;
   }   

   
   return loc_1;
}


/**
==================== Bool =============================================
   Grammar:
      bool : join bool_1 
*/
static TreeBool p_bool(void)  {
   printf("Bool\n");
   TreeBool bool = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeJoin l0join = p_join();
   TreeBool_1 l1bool_1 = p_bool_1();
   bool = t_bool_join(l0join, l1bool_1);

   
   return bool;
}


/**
==================== Bool_1 ===========================================
   Grammar:
      bool_1 : '||' join bool_1 |  e
*/
static TreeBool_1 p_bool_1(void)  {
   printf("Bool_1\n");
   TreeBool_1 bool_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_OR: {  
         eat(TOK_OR);
         TreeJoin l1join = p_join();
         TreeBool_1 l2bool_1 = p_bool_1();
         bool_1 = t_bool_1_OR(l1join, l2bool_1);
         break;
      }

      default:
         break;
   }
   
   return bool_1;
}


/**
==================== Join =============================================
   Grammar:
      join : equality join_1 
*/
static TreeJoin p_join(void)  {
   printf("Join\n");
   TreeJoin join = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeEquality l0equality = p_equality();
   TreeJoin_1 l1join_1 = p_join_1();
   join = t_join_equality(l0equality, l1join_1);

   
   return join;
}


/**
==================== Join_1 ===========================================
   Grammar:
      join_1 : '&&' equality join_1 |  e
*/
static TreeJoin_1 p_join_1(void)  {
   printf("Join_1\n");
   TreeJoin_1 join_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_AND: {  
         eat(TOK_AND);
         TreeEquality l1equality = p_equality();
         TreeJoin_1 l2join_1 = p_join_1();
         join_1 = t_join_1_AND(l1equality, l2join_1);
         break;
      }

      default:
         break;
   }   

   
   return join_1;
}


/**
==================== Equality =========================================
   Grammar:
      equality : rel equality_1 
*/
static TreeEquality p_equality(void)  {
   printf("Equality\n");
   TreeEquality equality = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeRel l0rel = p_rel();
   TreeEquality_1 l1equality_1 = p_equality_1();
   equality = t_equality_rel(l0rel, l1equality_1);

   
   return equality;
}


/**
==================== Equality_1 =======================================
   Grammar:
      equality_1 : '==' rel equality_1 | '!=' rel equality_1 |  e
*/
static TreeEquality_1 p_equality_1(void)  {
   printf("Equality_1\n");
   TreeEquality_1 equality_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_EQ: {  
         eat(TOK_EQ);
         TreeRel l1rel = p_rel();
         TreeEquality_1 l2equality_1 = p_equality_1();
         equality_1 = t_equality_1_EQ(l1rel, l2equality_1);
         break;
      }
      case TOK_NE: {  
         eat(TOK_NE);
         TreeRel l1rel = p_rel();
         TreeEquality_1 l2equality_1 = p_equality_1();
         equality_1 = t_equality_1_NE(l1rel, l2equality_1);
         break;
      }

      default:
         break;
   }   

   
   return equality_1;
}


/**
==================== Rel ==============================================
   Grammar:
      rel : '<' expr | '<=' expr | '>=' expr | '>' expr |  e
*/
static TreeRel p_rel(void)  {
   printf("Rel\n");
   TreeRel rel = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   TreeExpr l0expr = p_expr(); // common
   switch (code) {
      case '<': {  
         eat('<');
         TreeExpr l1expr = p_expr();
         rel = t_rel(code, l0expr, l1expr);
         break;
      }
      case TOK_LE: {  
         eat(TOK_LE);
         TreeExpr l1expr = p_expr();
         rel = t_rel(code, l0expr, l1expr);
         break;
      }
      case TOK_GE: {  
         eat(TOK_GE);
         TreeExpr l1expr = p_expr();
         rel = t_rel(code, l0expr, l1expr);
         break;
      }
      case '>': {  
         eat('>');
         TreeExpr l1expr = p_expr();
         rel = t_rel(code, l0expr, l1expr);
         break;
      }

      default:
		rel = t_rel(0, l0expr, NULL);
			break;
   }   

   
   return rel;
}


/**
==================== Expr =============================================
   Grammar:
      expr : term expr_1 
*/
static TreeExpr p_expr(void)  {
   printf("Expr\n");
   TreeExpr expr = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeTerm l0term = p_term();
   TreeExpr_1 l1expr_1 = p_expr_1();
   expr = t_expr_term(l0term, l1expr_1);

   
   return expr;
}


/**
==================== Expr_1 ===========================================
   Grammar:
      expr_1 : '+' term expr_1 | '-' term expr_1 |  e
*/
static TreeExpr_1 p_expr_1(void)  {
   printf("Expr_1\n");
   TreeExpr_1 expr_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '+': {  
         eat('+');
         TreeTerm l1term = p_term();
         TreeExpr_1 l2expr_1 = p_expr_1();
         expr_1 = t_expr_1_term(code, l1term, l2expr_1);
         break;
      }
      case '-': {  
         eat('-');
         TreeTerm l1term = p_term();
         TreeExpr_1 l2expr_1 = p_expr_1();
         expr_1 = t_expr_1_term(code, l1term, l2expr_1);
         break;
      }

      default:
         break;
   }   

   
   return expr_1;
}


/**
==================== Term =============================================
   Grammar:
      term : unary term_1 
*/
static TreeTerm p_term(void)  {
   printf("Term\n");
   TreeTerm term = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeUnary l0unary = p_unary();
   TreeTerm_1 l1term_1 = p_term_1();
   term = t_term_unary(l0unary, l1term_1);

   
   return term;
}


/**
==================== Term_1 ===========================================
   Grammar:
      term_1 : '*' unary term_1 | '/' unary term_1 |  e
*/
static TreeTerm_1 p_term_1(void)  {
   printf("Term_1\n");
   TreeTerm_1 term_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '*': {  
         eat('*');
         TreeUnary l1unary = p_unary();
         TreeTerm_1 l2term_1 = p_term_1();
         term_1 = t_term_1_unary(code, l1unary, l2term_1);
         break;
      }
      case '/': {  
         eat('/');
         TreeUnary l1unary = p_unary();
         TreeTerm_1 l2term_1 = p_term_1();
         term_1 = t_term_1_unary(code, l1unary, l2term_1);
         break;
      }

      default:
         break;
   }   

   
   return term_1;
}


/**
==================== Unary ============================================
   Grammar:
      unary : '!' unary | '-' unary | factor 
*/
static TreeUnary p_unary(void)  {
   printf("Unary\n");
   TreeUnary unary = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '!': {  
         eat('!');
         TreeUnary l1unary = p_unary();
         unary = t_unary_unary(code, l1unary);
         break;
      }
      case '-': {  
         eat('-');
         TreeUnary l1unary = p_unary();
         unary = t_unary_unary(code, l1unary);
         break;
      }
      default: {
         TreeFactor l0factor = p_factor();
         unary = t_unary_factor(l0factor);
         break;
	  }
   }   

   
   return unary;
}


/**
==================== Factor ===========================================
   Grammar:
      factor : '(' bool ')' | loc | num | real | 'true' | 'false' 
*/
static TreeFactor p_factor(void)  {
   printf("Factor\n");
   TreeFactor factor = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '(': {  
         eat('(');
         TreeBool l1bool = p_bool();
         eat(')');
         factor = t_factor_bool(l1bool);
         break;
      }
      case TOK_ID: {  //===== REDUCED TOK_loc
         TreeLoc l0loc = p_loc();
         factor = t_factor_loc(l0loc);
         break;
      }
      case TOK_NUM: {  
         TreeNum l0num = p_num();
         factor = t_factor_num(l0num);
         break;
      }
      case TOK_REAL: {  
         TreeReal l0real = p_real();
         factor = t_factor_real(l0real);
         break;
      }
      case TOK_true: {  
         eat(TOK_true);
         factor = t_factor_true();
         break;
      }
      case TOK_false: {  
         eat(TOK_false);
         factor = t_factor_false();
         break;
      }
      default:
         error_parse("factor");
         // longjmp(env,1);
         kill(getpid(),SIGINT);
         break;
   }   

   
   return factor;
}


