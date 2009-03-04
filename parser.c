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
   TreeBlock l0block = p_block();
   Program = t_program_block(l0block);

   
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
static TreeDecls p_decls(void) {
   TreeDecls = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeDecl l0decl = p_decl()
   if not ( ) return decls;

   TreeDecls l1decls = p_decls();
   decls = t_decls_decl(l0decl, l1decls);

   
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
   TreeType l0type = p_type();
   TreeId l1id = p_id();
   eat(';');
   decl = t_decl_type(l0type);

   
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
static TreeType_1 p_type_1(void) {
   TreeType_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_[: {  
         eat('[');
         TreeNum l1num = p_num();
         eat(']');
         TreeType_1 l3type_1 = p_type_1();
         type_1 = t_type_1_type_1(l3type_1);
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
static TreeBasic p_basic(void) {
   TreeBasic = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_int: {  
         eat(TOK_int);
         basic = t_basic_();
         break;
      }
      case TOK_float: {  
         eat(TOK_float);
         basic = t_basic_();
         break;
      }
      default:
         error_parse("basic");
         break;
   }   

   
   return basic;
}


/**
==================== Stmts ============================================
   Grammar:
      stmts : stmt stmts |  e
*/
static TreeStmts p_stmts(void) {
   TreeStmts = 0; // set null by default
   TokenCode code = curr()->code;
   // body
   TreeStmt l0stmt = p_stmt()
   if not ( ) return stmts;

   TreeStmts l1stmts = p_stmts();
   stmts = t_stmts_stmt(l0stmt, l1stmts);

   
   return stmts;
}


/**
==================== Stmt =============================================
   Grammar:
      stmt : loc '=' bool ';' | 'if' '(' bool ')' stmt | 'if' '(' bool ')' stmt 'else' stmt | 'while' '(' bool ')' stmt | 'do' stmt 'while' '(' bool ')' ';' | 'break' ';' | block | 'read' loc ';' | 'write' bool ';' 
*/
static TreeStmt p_stmt(void) {
   TreeStmt = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_id: {  //===== REDUCED TOK_loc
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
         stmt = t_stmt_bool(l2bool, l4stmt);
         break;
      }
      case TOK_if: {  
         eat(TOK_if);
         eat('(');
         TreeBool l2bool = p_bool();
         eat(')');
         TreeStmt l4stmt = p_stmt();
         eat(TOK_else);
         TreeStmt l6stmt = p_stmt();
         stmt = t_stmt_bool(l2bool, l4stmt, l6stmt);
         break;
      }
      case TOK_while: {  
         eat(TOK_while);
         eat('(');
         TreeBool l2bool = p_bool();
         eat(')');
         TreeStmt l4stmt = p_stmt();
         stmt = t_stmt_bool(l2bool, l4stmt);
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
         stmt = t_stmt_stmt(l1stmt, l4bool);
         break;
      }
      case TOK_break: {  
         eat(TOK_break);
         eat(';');
         stmt = t_stmt_();
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
         stmt = t_stmt_loc(l1loc);
         break;
      }
      case TOK_write: {  
         eat(TOK_write);
         TreeBool l1bool = p_bool();
         eat(';');
         stmt = t_stmt_bool(l1bool);
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
   TreeId l0id = p_id();
   TreeLoc_1 l1loc_1 = p_loc_1();
   loc = t_loc_loc_1(l1loc_1);

   
   return loc;
}


/**
==================== Loc_1 ============================================
   Grammar:
      loc_1 : '[' bool ']' loc_1 |  e
*/
static TreeLoc_1 p_loc_1(void) {
   TreeLoc_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_[: {  
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
static TreeBool p_bool(void) {
   TreeBool = 0; // set null by default
   TokenCode code = curr()->code;
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
static TreeBool_1 p_bool_1(void) {
   TreeBool_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_OR: {  
         eat(TOK_OR);
         TreeJoin l1join = p_join();
         TreeBool_1 l2bool_1 = p_bool_1();
         bool_1 = t_bool_1_join(l1join, l2bool_1);
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
static TreeJoin_1 p_join_1(void) {
   TreeJoin_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_AND: {  
         eat(TOK_AND);
         TreeEquality l1equality = p_equality();
         TreeJoin_1 l2join_1 = p_join_1();
         join_1 = t_join_1_equality(l1equality, l2join_1);
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
static TreeEquality_1 p_equality_1(void) {
   TreeEquality_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_EQ: {  
         eat(TOK_EQ);
         TreeRel l1rel = p_rel();
         TreeEquality_1 l2equality_1 = p_equality_1();
         equality_1 = t_equality_1_rel(l1rel, l2equality_1);
         break;
      }
      case TOK_NE: {  
         eat(TOK_NE);
         TreeRel l1rel = p_rel();
         TreeEquality_1 l2equality_1 = p_equality_1();
         equality_1 = t_equality_1_rel(l1rel, l2equality_1);
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
   TreeExpr l0expr = p_expr(); // common
   switch (code) {
      case TOK_<: {  
         eat('<');
         TreeExpr l1expr = p_expr();
         rel = t_rel_expr(l0expr, l1expr);
         break;
      }
      case TOK_LE: {  
         eat(TOK_LE);
         TreeExpr l1expr = p_expr();
         rel = t_rel_expr(l0expr, l1expr);
         break;
      }
      case TOK_GE: {  
         eat(TOK_GE);
         TreeExpr l1expr = p_expr();
         rel = t_rel_expr(l0expr, l1expr);
         break;
      }
      case TOK_>: {  
         eat('>');
         TreeExpr l1expr = p_expr();
         rel = t_rel_expr(l0expr, l1expr);
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
static TreeExpr_1 p_expr_1(void) {
   TreeExpr_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_+: {  
         eat('+');
         TreeTerm l1term = p_term();
         TreeExpr_1 l2expr_1 = p_expr_1();
         expr_1 = t_expr_1_term(l1term, l2expr_1);
         break;
      }
      case TOK_-: {  
         eat('-');
         TreeTerm l1term = p_term();
         TreeExpr_1 l2expr_1 = p_expr_1();
         expr_1 = t_expr_1_term(l1term, l2expr_1);
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
static TreeTerm_1 p_term_1(void) {
   TreeTerm_1 = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_*: {  
         eat('*');
         TreeUnary l1unary = p_unary();
         TreeTerm_1 l2term_1 = p_term_1();
         term_1 = t_term_1_unary(l1unary, l2term_1);
         break;
      }
      case TOK_/: {  
         eat('/');
         TreeUnary l1unary = p_unary();
         TreeTerm_1 l2term_1 = p_term_1();
         term_1 = t_term_1_unary(l1unary, l2term_1);
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
static TreeUnary p_unary(void) {
   TreeUnary = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_!: {  
         eat('!');
         TreeUnary l1unary = p_unary();
         unary = t_unary_unary(l1unary);
         break;
      }
      case TOK_-: {  
         eat('-');
         TreeUnary l1unary = p_unary();
         unary = t_unary_unary(l1unary);
         break;
      }
      case '(': {  //===== REDUCED TOK_factor
         TreeFactor l0factor = p_factor();
         unary = t_unary_factor(l0factor);
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
      factor : '(' bool ')' | loc | num | real | 'true' | 'false' 
*/
static TreeFactor p_factor(void) {
   TreeFactor = 0; // set null by default
   TokenCode code = curr()->code;
   // cases
   
   switch (code) {
      case TOK_(: {  
         eat('(');
         TreeBool l1bool = p_bool();
         eat(')');
         factor = t_factor_bool(l1bool);
         break;
      }
      case TOK_id: {  //===== REDUCED TOK_loc
         TreeLoc l0loc = p_loc();
         factor = t_factor_loc(l0loc);
         break;
      }
      case TOK_num: {  
         TreeNum l0num = p_num();
         factor = t_factor_();
         break;
      }
      case TOK_real: {  
         TreeReal l0real = p_real();
         factor = t_factor_();
         break;
      }
      case TOK_true: {  
         eat(TOK_true);
         factor = t_factor_();
         break;
      }
      case TOK_false: {  
         eat(TOK_false);
         factor = t_factor_();
         break;
      }
      default:
         error_parse("factor");
         break;
   }   

   
   return factor;
}


