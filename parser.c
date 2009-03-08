#include "tree.h"
#include "terminals.h"
#include "printlib.h"
#include "symtab.h"
#include "symtaben.h"

#include "scanner/scanner.h"
#include "scanner/token.h"

#include <setjmp.h>
#include <signal.h>
#include <string.h>

//!make simple

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
==================== Program <<<<<<<<<<<<<<<<<<<<<<<<<<<===============
   Grammar:
      Program : block 
*/
extern TreeBlock Program(void) {
   // setjmp(env);
   SYM_OFFSET = 0;
   SYM_DEPTH = 0;
   SYM_MAX_DEPTH = 0;
   
   TreeBlock block = p_block();

   return block;
}


/**
==================== Block <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      block : '{' decls stmts '}' 
*/
static TreeBlock p_block(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Block		line:'%s'\n", scanner_str() );
   TreeBlock block = 0; // set null by default
   
   SymtabPush();
   
   // body
   eat('{');
   TreeDecls l1decls = p_decls();
   TreeStmts l2stmts = p_stmts();
   eat('}');
   block = t_block_decls(l1decls, l2stmts);
   
   SymtabPop();
   
   // printf(">>>>>>>>>>>>>>>>\nTreeBlock\n");
   // print_TreeBlock(2,block);
   return block;
}


/**
==================== Decls <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      decls : decl decls |  e
*/
static TreeDecls p_decls(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Decls		line:'%s'\n", scanner_str() );
   TreeDecls decls = 0; // set null by default
   TokenCode code = curr()->code;
   
   // check if we have next production, return on zero
   if ( code != TOK_int && code != TOK_float  ) 
      return decls;
   
   // body
   TreeDecl l0decl = p_decl();
   
   // if found type then another type continue
   TreeDecls l1decls = p_decls();
   decls = t_decls_decl(l0decl, l1decls);
   
   // printf(">>>>>>>>>>>>>>>>\nTreeDecls\n");
   // print_TreeDecls(2,decls);
   return decls;
}


/**
==================== Decl <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      decl : type id ';' 
*/
static TreeDecl p_decl(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Decl		line:'%s'\n", scanner_str() );
   TreeDecl decl = 0; // set null by default
	
   // body
   TreeType l0type = p_type();
   TreeId l1id = p_decl_id();
	
	// add id to symbol table;
   SymtabEntry id_entry = SymtabEntryNew(l1id->id, l0type);
   SymTabPut(l1id->id, id_entry);
   printf("decl: Adding Symtable Entry: %p\n", id_entry);
   print_SymtabEntry(2,id_entry);
   
   eat(';');
   decl = t_decl_type(l0type, l1id);

   // printf(">>>>>>>>>>>>>>>>\nTreeDecl\n");
   // print_TreeDecl(2,decl);
   return decl;
}


/**
==================== Type <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      type : basic type_1 
*/
static TreeType p_type(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Type		line:'%s'\n", scanner_str() );
   TreeType type = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeBasic l0basic = p_basic();
   TreeType_1 l1type_1 = p_type_1();
   type = t_type_basic(l0basic, l1type_1);
   
   // printf(">>>>>>>>>>>>>>>>\nTreeType\n");
   // print_TreeType(2,type);
   return type;
}


/**
==================== Type_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      type_1 : '[' num ']' type_1 |  e
*/
static TreeType_1 p_type_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Type_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeType_1\n");
   // print_TreeType_1(2,type_1);
   return type_1;
}


/**
==================== Basic <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      basic : 'int' | 'float' 
*/
static TreeBasic p_basic(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Basic		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeBasic\n");
   // print_TreeBasic(2,basic);
   return basic;
}


/**
==================== Stmts <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      stmts : stmt stmts |  e
*/
static TreeStmts p_stmts(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Stmts		line:'%s'\n", scanner_str() );
   TreeStmts stmts = 0; // set null by default
   TokenCode code = curr()->code;

   // body
	if ( code == '}' ) 
      return stmts = 0;
   
	TreeStmt l0stmt = p_stmt();   
   TreeStmts l1stmts = p_stmts();
   stmts = t_stmts_stmt(l0stmt, l1stmts);

   // printf(">>>>>>>>>>>>>>>>\nTreeStmts\n");
   // print_TreeStmts(2,stmts);
   return stmts;
}


/**
==================== Stmt <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      stmt : loc '=' bool ';' | 'if' '(' bool ')' stmt | 'if' '(' bool ')' stmt 'else' stmt | 'while' '(' bool ')' stmt | 'do' stmt 'while' '(' bool ')' ';' | 'break' ';' | block | 'read' loc ';' | 'write' bool ';' 
*/
static TreeStmt p_stmt(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Stmt		line:'%s'\n", scanner_str() );
   TreeStmt stmt = 0; // set null by default
   TokenCode code = curr()->code;
   char *str = strdup(scanner_str());
   
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
      default: {
         // printf("Stmt error line:'%s'\n", scanner_str() );
         TokenCode code = curr()->code;
         print_tok(3, code);
         
         error_parse("stmt");
         // longjmp(env,1);
         kill(getpid(),SIGINT);
         break;
      }
   }   

   if (stmt) stmt->str = str;
   // printf(">>>>>>>>>>>>>>>>\nTreeStmt\n");
   // print_TreeStmt(2,stmt);
   return stmt;
}


/**
==================== Loc <<<<<<<<<<<<<<<<<<<<<<<<<<<===================
   Grammar:
      loc : id loc_1 
*/
static TreeLoc p_loc(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Loc		line:'%s'\n", scanner_str() );
   TreeLoc loc = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeId l0id = p_id();
   TreeLoc_1 l1loc_1 = p_loc_1();
   loc = t_loc_id(l0id, l1loc_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeLoc\n");
   // print_TreeLoc(2,loc);
   return loc;
}


/**
==================== Loc_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      loc_1 : '[' bool ']' loc_1 |  e
*/
static TreeLoc_1 p_loc_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Loc_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeLoc_1\n");
   // print_TreeLoc_1(2,loc_1);
   return loc_1;
}


/**
==================== Bool <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      bool : join bool_1 
*/
static TreeBool p_bool(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Bool		line:'%s'\n", scanner_str() );
   TreeBool bool = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeJoin l0join = p_join();
   TreeBool_1 l1bool_1 = p_bool_1();
   bool = t_bool_join(l0join, l1bool_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeBool\n");
   // print_TreeBool(2,bool);
   return bool;
}


/**
==================== Bool_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      bool_1 : '||' join bool_1 |  e
*/
static TreeBool_1 p_bool_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Bool_1		line:'%s'\n", scanner_str() );
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
   
   // printf(">>>>>>>>>>>>>>>>\nTreeBool_1\n");
   // print_TreeBool_1(2,bool_1);
   return bool_1;
}


/**
==================== Join <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      join : equality join_1 
*/
static TreeJoin p_join(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Join		line:'%s'\n", scanner_str() );
   TreeJoin join = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeEquality l0equality = p_equality();
   TreeJoin_1 l1join_1 = p_join_1();
   join = t_join_equality(l0equality, l1join_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeJoin\n");
   // print_TreeJoin(2,join);
   return join;
}


/**
==================== Join_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      join_1 : '&&' equality join_1 |  e
*/
static TreeJoin_1 p_join_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Join_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeJoin_1\n");
   // print_TreeJoin_1(2,join_1);
   return join_1;
}


/**
==================== Equality <<<<<<<<<<<<<<<<<<<<<<<<<<<==============
   Grammar:
      equality : rel equality_1 
*/
static TreeEquality p_equality(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Equality		line:'%s'\n", scanner_str() );
   TreeEquality equality = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeRel l0rel = p_rel();
   TreeEquality_1 l1equality_1 = p_equality_1();
   equality = t_equality_rel(l0rel, l1equality_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeEquality\n");
   // print_TreeEquality(2,equality);
   return equality;
}


/**
==================== Equality_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<============
   Grammar:
      equality_1 : '==' rel equality_1 | '!=' rel equality_1 |  e
*/
static TreeEquality_1 p_equality_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Equality_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeEquality_1\n");
   // print_TreeEquality_1(2,equality_1);
   return equality_1;
}


/**
==================== Rel <<<<<<<<<<<<<<<<<<<<<<<<<<<===================
   Grammar:
      rel : '<' expr | '<=' expr | '>=' expr | '>' expr |  e
*/
static TreeRel p_rel(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Rel		line:'%s'\n", scanner_str() );
   TreeRel rel = 0; // set null by default
   // cases
   TreeExpr l0expr = p_expr(); // common

   TokenCode code = curr()->code;
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeRel\n");
   // print_TreeRel(2,rel);
   return rel;
}


/**
==================== Expr <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      expr : term expr_1 
*/
static TreeExpr p_expr(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Expr		line:'%s'\n", scanner_str() );
   TreeExpr expr = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeTerm l0term = p_term();
   TreeExpr_1 l1expr_1 = p_expr_1();
   expr = t_expr_term(l0term, l1expr_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeExpr\n");
   // print_TreeExpr(2,expr);
   return expr;
}


/**
==================== Expr_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      expr_1 : '+' term expr_1 | '-' term expr_1 |  e
*/
static TreeExpr_1 p_expr_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Expr_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeExpr_1\n");
   // print_TreeExpr_1(2,expr_1);
   return expr_1;
}


/**
==================== Term <<<<<<<<<<<<<<<<<<<<<<<<<<<==================
   Grammar:
      term : unary term_1 
*/
static TreeTerm p_term(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Term		line:'%s'\n", scanner_str() );
   TreeTerm term = 0; // set null by default
   // TokenCode code = curr()->code;
   // body
   TreeUnary l0unary = p_unary();
   TreeTerm_1 l1term_1 = p_term_1();
   term = t_term_unary(l0unary, l1term_1);

   
   // printf(">>>>>>>>>>>>>>>>\nTreeTerm\n");
   // print_TreeTerm(2,term);
   return term;
}


/**
==================== Term_1 <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      term_1 : '*' unary term_1 | '/' unary term_1 |  e
*/
static TreeTerm_1 p_term_1(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Term_1		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeTerm_1\n");
   // print_TreeTerm_1(2,term_1);
   return term_1;
}


/**
==================== Unary <<<<<<<<<<<<<<<<<<<<<<<<<<<=================
   Grammar:
      unary : '!' unary | '-' unary | factor 
*/
static TreeUnary p_unary(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Unary		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeUnary\n");
   // print_TreeUnary(2,unary);
   return unary;
}


/**
==================== Factor <<<<<<<<<<<<<<<<<<<<<<<<<<<================
   Grammar:
      factor : '(' bool ')' | loc | num | real | 'true' | 'false' 
*/
static TreeFactor p_factor(void)  {
   // printf("\n<<<<<<<<<<<<<<<<<<<<<<<<<<<\n  trace:  Factor		line:'%s'\n", scanner_str() );
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

   
   // printf(">>>>>>>>>>>>>>>>\nTreeFactor\n");
   // print_TreeFactor(2,factor);
   return factor;
}


