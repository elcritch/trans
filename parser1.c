Grammar: 
/**
==================== Program ==========================================
   Grammar:
      Program : block 
*/
static TreeProgram p_Program(void) {
   TreeProgram = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeBlock lblock = p_block();
   Program = t_program_block(lblock);

   return Program;
}


/**
==================== Block ============================================
   Grammar:
      block : '{' decls stmts '}' 
*/
static TreeBlock p_block(void) {
   TreeBlock = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   eat('{');
   TreeDecls ldecls = p_decls();
   TreeStmts lstmts = p_stmts();
   eat('}');
   block = t_block_decls(ldecls, lstmts);

   return block;
}


/**
==================== Decls ============================================
   Grammar:
      decls : decls |  e
*/
static TreeDecls p_decls(void) {
   TreeDecls = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_decls: {
         TreeDecls ldecls = p_decls();
         decls = t_decls_decls(ldecls);
         break;
      }

      default:
         break;
   }   

   return decls;
}


/**
==================== Decl =============================================
   Grammar:
      decl : type id ';' 
*/
static TreeDecl p_decl(void) {
   TreeDecl = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeType ltype = p_type();
   TreeId lid = p_id();
   eat(';');
   decl = t_decl_type(ltype);

   return decl;
}


/**
==================== Type =============================================
   Grammar:
      type : basic type_1 
*/
static TreeType p_type(void) {
   TreeType = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeBasic lbasic = p_basic();
   TreeType_1 ltype_1 = p_type_1();
   type = t_type_basic(lbasic, ltype_1);

   return type;
}


/**
==================== Type_1 ===========================================
   Grammar:
      type_1 : num ']' type_1 |  e
*/
static TreeType_1 p_type_1(void) {
   TreeType_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_num: {
         TreeNum lnum = p_num();
         eat(']');
         TreeType_1 ltype_1 = p_type_1();
         type_1 = t_type_1_type_1(ltype_1);
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
      basic :  |  e
*/
static TreeBasic p_basic(void) {
   TreeBasic = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {


      default:
         error_parse("basic");
         break;
   }   

   return basic;
}


/**
==================== Stmts ============================================
   Grammar:
      stmts : stmts |  e
*/
static TreeStmts p_stmts(void) {
   TreeStmts = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_stmts: {
         TreeStmts lstmts = p_stmts();
         stmts = t_stmts_stmts(lstmts);
         break;
      }

      default:
         break;
   }   

   return stmts;
}


/**
==================== Stmt =============================================
   Grammar:
      stmt : '=' bool ';' | '(' bool ')' stmt | '(' bool ')' stmt 'else' stmt | '(' bool ')' stmt | stmt 'while' '(' bool ')' ';' | ';' |  | loc ';' | bool ';' 
*/
static TreeStmt p_stmt(void) {
   TreeStmt = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case '=': {
         eat('=');
         TreeBool lbool = p_bool();
         eat(';');
         stmt = t_stmt_bool(lbool);
         break;
      }
      case '(': {
         eat('(');
         TreeBool lbool = p_bool();
         eat(')');
         TreeStmt lstmt = p_stmt();
         stmt = t_stmt_bool(lbool, lstmt);
         break;
      }
      case '(': {
         eat('(');
         TreeBool lbool = p_bool();
         eat(')');
         TreeStmt lstmt = p_stmt();
         eat(TOK_else);
         TreeStmt lstmt = p_stmt();
         stmt = t_stmt_bool(lbool, lstmt, lstmt);
         break;
      }
      case '(': {
         eat('(');
         TreeBool lbool = p_bool();
         eat(')');
         TreeStmt lstmt = p_stmt();
         stmt = t_stmt_bool(lbool, lstmt);
         break;
      }
      case TOK_stmt: {
         TreeStmt lstmt = p_stmt();
         eat(TOK_while);
         eat('(');
         TreeBool lbool = p_bool();
         eat(')');
         eat(';');
         stmt = t_stmt_stmt(lstmt, lbool);
         break;
      }
      case ';': {
         eat(';');
         stmt = t_stmt_();
         break;
      }

      case TOK_loc: {
         TreeLoc lloc = p_loc();
         eat(';');
         stmt = t_stmt_loc(lloc);
         break;
      }
      case TOK_bool: {
         TreeBool lbool = p_bool();
         eat(';');
         stmt = t_stmt_bool(lbool);
         break;
      }
      default:
         error_parse("stmt");
         break;
   }   

   return stmt;
}


/**
==================== Loc ==============================================
   Grammar:
      loc : id loc_1 
*/
static TreeLoc p_loc(void) {
   TreeLoc = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeId lid = p_id();
   TreeLoc_1 lloc_1 = p_loc_1();
   loc = t_loc_loc_1(lloc_1);

   return loc;
}


/**
==================== Loc_1 ============================================
   Grammar:
      loc_1 : bool ']' loc_1 |  e
*/
static TreeLoc_1 p_loc_1(void) {
   TreeLoc_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_bool: {
         TreeBool lbool = p_bool();
         eat(']');
         TreeLoc_1 lloc_1 = p_loc_1();
         loc_1 = t_loc_1_bool(lbool, lloc_1);
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
static TreeBool p_bool(void) {
   TreeBool = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeJoin ljoin = p_join();
   TreeBool_1 lbool_1 = p_bool_1();
   bool = t_bool_join(ljoin, lbool_1);

   return bool;
}


/**
==================== Bool_1 ===========================================
   Grammar:
      bool_1 : join bool_1 |  e
*/
static TreeBool_1 p_bool_1(void) {
   TreeBool_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_join: {
         TreeJoin ljoin = p_join();
         TreeBool_1 lbool_1 = p_bool_1();
         bool_1 = t_bool_1_join(ljoin, lbool_1);
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
static TreeJoin p_join(void) {
   TreeJoin = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeEquality lequality = p_equality();
   TreeJoin_1 ljoin_1 = p_join_1();
   join = t_join_equality(lequality, ljoin_1);

   return join;
}


/**
==================== Join_1 ===========================================
   Grammar:
      join_1 : equality join_1 |  e
*/
static TreeJoin_1 p_join_1(void) {
   TreeJoin_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_equality: {
         TreeEquality lequality = p_equality();
         TreeJoin_1 ljoin_1 = p_join_1();
         join_1 = t_join_1_equality(lequality, ljoin_1);
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
static TreeEquality p_equality(void) {
   TreeEquality = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeRel lrel = p_rel();
   TreeEquality_1 lequality_1 = p_equality_1();
   equality = t_equality_rel(lrel, lequality_1);

   return equality;
}


/**
==================== Equality_1 =======================================
   Grammar:
      equality_1 : rel equality_1 | rel equality_1 |  e
*/
static TreeEquality_1 p_equality_1(void) {
   TreeEquality_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_rel: {
         TreeRel lrel = p_rel();
         TreeEquality_1 lequality_1 = p_equality_1();
         equality_1 = t_equality_1_rel(lrel, lequality_1);
         break;
      }
      case TOK_rel: {
         TreeRel lrel = p_rel();
         TreeEquality_1 lequality_1 = p_equality_1();
         equality_1 = t_equality_1_rel(lrel, lequality_1);
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
static TreeRel p_rel(void) {
   TreeRel = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   TreeExpr lexpr = p_expr(); // common
   switch (code) {
      case '<': {
         eat('<');
         TreeExpr lexpr = p_expr();
         rel = t_rel_expr(lexpr);
         break;
      }
      case TOK_LE: {
         eat(TOK_LE);
         TreeExpr lexpr = p_expr();
         rel = t_rel_expr(lexpr);
         break;
      }
      case TOK_GE: {
         eat(TOK_GE);
         TreeExpr lexpr = p_expr();
         rel = t_rel_expr(lexpr);
         break;
      }
      case '>': {
         eat('>');
         TreeExpr lexpr = p_expr();
         rel = t_rel_expr(lexpr);
         break;
      }

      default:
         error_parse("rel");
         break;
   }   

   return rel;
}


/**
==================== Expr =============================================
   Grammar:
      expr : term expr_1 
*/
static TreeExpr p_expr(void) {
   TreeExpr = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeTerm lterm = p_term();
   TreeExpr_1 lexpr_1 = p_expr_1();
   expr = t_expr_term(lterm, lexpr_1);

   return expr;
}


/**
==================== Expr_1 ===========================================
   Grammar:
      expr_1 : term expr_1 | term expr_1 |  e
*/
static TreeExpr_1 p_expr_1(void) {
   TreeExpr_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_term: {
         TreeTerm lterm = p_term();
         TreeExpr_1 lexpr_1 = p_expr_1();
         expr_1 = t_expr_1_term(lterm, lexpr_1);
         break;
      }
      case TOK_term: {
         TreeTerm lterm = p_term();
         TreeExpr_1 lexpr_1 = p_expr_1();
         expr_1 = t_expr_1_term(lterm, lexpr_1);
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
static TreeTerm p_term(void) {
   TreeTerm = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeUnary lunary = p_unary();
   TreeTerm_1 lterm_1 = p_term_1();
   term = t_term_unary(lunary, lterm_1);

   return term;
}


/**
==================== Term_1 ===========================================
   Grammar:
      term_1 : unary term_1 | unary term_1 |  e
*/
static TreeTerm_1 p_term_1(void) {
   TreeTerm_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_unary: {
         TreeUnary lunary = p_unary();
         TreeTerm_1 lterm_1 = p_term_1();
         term_1 = t_term_1_unary(lunary, lterm_1);
         break;
      }
      case TOK_unary: {
         TreeUnary lunary = p_unary();
         TreeTerm_1 lterm_1 = p_term_1();
         term_1 = t_term_1_unary(lunary, lterm_1);
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
      unary : unary | unary |  e
*/
static TreeUnary p_unary(void) {
   TreeUnary = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_unary: {
         TreeUnary lunary = p_unary();
         unary = t_unary_unary(lunary);
         break;
      }
      case TOK_unary: {
         TreeUnary lunary = p_unary();
         unary = t_unary_unary(lunary);
         break;
      }

      default:
         error_parse("unary");
         break;
   }   

   return unary;
}


/**
==================== Factor ===========================================
   Grammar:
      factor : bool ')' |  |  |  |  |  e
*/
static TreeFactor p_factor(void) {
   TreeFactor = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_bool: {
         TreeBool lbool = p_bool();
         eat(')');
         factor = t_factor_bool(lbool);
         break;
      }





      default:
         error_parse("factor");
         break;
   }   

   return factor;
}


