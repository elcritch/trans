#include "generator.h"
#include "symtaben.h"
#include <signal.h>

#define GEN(name) g_##name(var->name)
#define OPT_GEN(name) if (var->name) g_##name(var->name)

#define emit_ins1(inst) printf("\t\t"inst"\n")
#define emit_ins2(inst, arg) printf("\t\t"inst"\t\t"arg"\n")

#define emit_ins1f(inst, args...) printf("\t\t"inst"\n", args)
#define emit_ins2f(inst, arg, args...) printf("\t\t"inst"\t\t"arg"\n", args)

#define emit_comm(msg) printf("\t\t# "msg"\n")
#define emit_commf(msg, args...) printf("\t\t# "msg"\n", args)

#define emit_label(msg) printf(""msg":\n");
#define emit_labelf(msg, args...) printf(""msg":\n", args)
#define emit_label2f(msg, arg, args...) printf(""msg":\t\t"arg"\n", args)


static void g_id_addr(TreeId var);
static void g_block(TreeBlock var);
static void g_decls(TreeDecls var);
static void g_decl(TreeDecl var);
static void g_stmts(TreeStmts var);
static void g_stmt(TreeStmt v);
static void g_stmt_loc(TreeLoc loc, TreeBool bools);
static void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt);
static void g_stmt_while(TreeBool bools, TreeStmt stmt);
static void g_stmt_do(TreeStmt stmt, TreeBool bools);
static void g_stmt_break();
static void g_stmt_block(TreeBlock block);
static void g_stmt_read(TreeLoc loc);
static void g_stmt_write(TreeBool bools);
static Type g_loc(TreeLoc var);
static void g_loc_1(TreeLoc_1 var, TreeType_1 type_1);
static Type g_bools(TreeBool var);
static Type g_bool_1(TreeBool_1 var);
static Type g_join(TreeJoin var);
static Type g_join_1(TreeJoin_1 var);
static Type g_equality(TreeEquality var);
static Type g_equality_1(TreeEquality_1 var);
static Type g_rel(TreeRel var);
static Type g_expr(TreeExpr var);
static Type g_expr_1(TreeExpr_1 var);
static Type g_term(TreeTerm var);
static Type g_term_1(TreeTerm_1 var);
static Type g_unary(TreeUnary var);
static Type g_factor(TreeFactor var);

size_t EQ_COUNT;
size_t REL_COUNT;
size_t IF_COUNT;
size_t WHILE_COUNT;
size_t BLOCK_COUNT;

// ====================================================================
extern void generate(TreeBlock block) {
   if (!block) return;
   
   EQ_COUNT = 0;
   REL_COUNT = 0;
   IF_COUNT = 0;
   WHILE_COUNT = 0;
   BLOCK_COUNT = 0;
   
   emit_ins2("push",	"$beg");
   emit_ins1("jmp");

   for(size_t i = 0; i < SYM_MAX_DEPTH; ++i)
   {
      emit_label2f("$view%zd","%s\n",i+1, "-1"); // make variable storage for stack
   }
   
   emit_label("$beg");
   
   g_block(block);
   
   emit_ins1("stop");
   emit_ins1("end");
	
}

// ====================================================================
static void g_block(TreeBlock var) {
   BLOCK_COUNT++;
   
   emit_commf("Entering block %zd", BLOCK_COUNT);
   if (var->decls) {
      // find beginning of block address and store it in the block's viewport
      SymtabEntry entry = var->decls->decl->id->entry;
      if (entry->depth != BLOCK_COUNT) {
         error_parse("Generator error! block count doesn't match entry depth!");
         kill(getpid(), SIGINT);
      }
      emit_ins2f("push","$view%zd", BLOCK_COUNT);	// store in viewport 1
      emit_ins2("push","$sp");   // store add of stack+1 in $v1
      emit_ins2("push", "1");   // stack offset adjus
      emit_ins1("add");
      emit_ins1("st");  // now location of block 1 is stored in $view%zd
      GEN(decls);
   }
   
   OPT_GEN(stmts);
   
   if (var->decls) {
   
      // todo: add block cleanup code... 
      // should restore sp to value in viewport of id.
      // or pop off variable spaces for each decl
      emit_commf("Cleaning up block frame %zd", BLOCK_COUNT);
      emit_ins2("push","$sp");
      emit_ins2f("push","$view%zd", BLOCK_COUNT);
      emit_ins1("ld");
      emit_ins2("push", "1");
      emit_ins1("sub");
      emit_ins1("st");
   }
   
   BLOCK_COUNT--;
}

// ====================================================================
static void g_decls(TreeDecls var) {
   GEN(decl);
   OPT_GEN(decls);
}

static void g_decl(TreeDecl var) {
   
   SymtabEntry entry = var->id->entry;
   // Structure: type [["basic", ["basic", "type_1"]]]
   // Structure: type_1 [["num", ["type_1"]]]
   // GEN(id);
   // GEN(type);
   
   // "allocate" enough space on the block to store this var
   // this could also done by "jumping" the stack pointer
   for (size_t i = 0; i< entry->dims; ++i)
      emit_ins2("push", "0\t\t# empty var for block");
   
}

static void g_id_addr(TreeId var) {
   char *lex = var->lex;
   SymtabEntry entry = var->entry;
   
   emit_commf("variable: %s depth:%zd offset:%zd",lex, entry->depth, entry->offset);
   emit_ins2f("push","$view%zd", entry->depth);
   emit_ins1("ld");
   emit_ins2f("push","%zd", entry->offset);
   emit_ins1("add");
   
}

// Structure: loc [["id", ["id", "loc_1"]]]
static Type g_loc(TreeLoc var) {
   TreeId id = var->id;
   SymtabEntry entry = var->id->entry;
   TreeLoc_1 loc_1 = var->loc_1;
   
   // generate base offset
   g_id_addr(var->id);
   
   if (var->loc_1) {
      // if array, then we need to add array offset to base offset
      emit_commf("array offset: %s", id->lex);
      g_bools(loc_1->bools);
      // add runtime dimension check here
      if (loc_1->loc_1) 
         g_loc_1(loc_1->loc_1, entry->type->type_1->type_1);
      emit_ins1("add");
      // if width wasn't 1, them multiply by width here.
      emit_commf("end array offset: %s", id->lex);
   }
   return (Type) NULL;
}

// Structure: loc_1 [["bools", ["bools", "loc_1"]]]
static void g_loc_1(TreeLoc_1 var, TreeType_1 type_1) {
   //  (...) x N_j + I_j 
   
   // calc N_j and multiply by prev dim on stack
   emit_ins2f("push", "%zd", type_1->num->size);
   emit_ins1("mul");
   
   // calc I_j and add to prev value on stack
   GEN(bools);
   // add runtime dimension check here
   emit_ins1("add");
   
   if (var->loc_1) {
      g_loc_1(var->loc_1, type_1->type_1);
   }
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
   Type tp1 = g_loc(loc);
   Type tp2 = g_bools(bools);
   tp1 = tp2;
   emit_ins1("st");
}

static void g_stmt_if(TreeBool bools, TreeStmt stmt, TreeStmt else_stmt) {
   g_bools(bools);
   emit_ins2f("push", "$ie%zd", IF_COUNT); // jump to else (even if no else)
   emit_ins1("jz");   // we want to jump if bools value was 0
   g_stmt(stmt);
   emit_ins2f("push", "$iq%zd", IF_COUNT); // jump to end
   emit_ins1("jmp");   // we want to jump if bools value was false
   
   emit_labelf("$ie%zd", IF_COUNT);
   if (else_stmt) {
      g_stmt(else_stmt);
   }
   emit_labelf("$iq%zd", IF_COUNT);
   IF_COUNT++;
}

static void g_stmt_while(TreeBool bools, TreeStmt stmt) {
   
   emit_commf("while loop %zd", WHILE_COUNT);
   emit_labelf("$ws%zd", WHILE_COUNT);
   g_bools(bools);
   
   emit_ins2f("push", "$wq%zd", WHILE_COUNT); // jump to end
   emit_ins1("jz");   // we want to jump to end if bools value was 0
   
   g_stmt(stmt);
   
   emit_ins2f("push", "$ws%zd", WHILE_COUNT); // jump to beginning
   emit_ins1("jmp");   // we want to jump if bools value was false
   
   emit_labelf("$wq%zd", WHILE_COUNT);
   emit_commf("end while loop %zd", WHILE_COUNT);
   
   WHILE_COUNT++;
}

static void g_stmt_do(TreeStmt stmt, TreeBool bools) {
   
   emit_labelf("$ws%zd", WHILE_COUNT);
   g_stmt(stmt);
   
   g_bools(bools);

   emit_ins2f("push", "$ws%zd", WHILE_COUNT); // jump to end
   emit_ins1("jp");   // we want to jump if bools value was 1>0

   emit_labelf("$wq%zd", WHILE_COUNT);
   WHILE_COUNT++;

}

static void g_stmt_break() {
   emit_ins2f("push", "$wq%zd", WHILE_COUNT-1); // goto last labeled loop
   emit_ins1("jmp");
}

static void g_stmt_block(TreeBlock block) {
   g_block(block);
}

static void g_stmt_read(TreeLoc loc) {
   g_loc(loc);
   emit_ins1("rd");
   emit_ins1("st");
}

static void g_stmt_write(TreeBool bools) {
   g_bools(bools);
   emit_ins1("wr");
}



// ====================================================================

// Structure: bools [["join", ["join", "bool_1"]]]
static Type g_bools(TreeBool var) {
   Type ret = 0; 
   GEN(join);
   OPT_GEN(bool_1);
   
   return ret;
}

// Structure: bool_1 [["OR", ["join", "bool_1"]]]
static Type g_bool_1(TreeBool_1 var) {
   Type ret = 0; 
   GEN(join);
   
   if (var->bool_1) {
      GEN(bool_1);
      // if st1 = 1 or st2 = 1, add > 0, then true, else, 0
      emit_ins1("add");
      emit_ins2("push", "1");
      emit_ins1("sub");
      emit_ins2f("push", "$ef%zd", EQ_COUNT);
      emit_ins1("jp");  // jump if greater than 0
      emit_labelf("$et%zd",EQ_COUNT);	
      emit_ins2("push", "0");
      emit_ins2f("push", "$eq%zd", EQ_COUNT);
      emit_ins1("jmp");
      emit_labelf("$ef%zd",EQ_COUNT);
      emit_ins2("push","1");
      emit_labelf("$eq%zd",EQ_COUNT);
      EQ_COUNT++;
   }
   
   return ret;
}

// Structure: join [["equality", ["equality", "join_1"]]]
static Type g_join(TreeJoin var) {
   Type ret = 0; 
   GEN(equality);
   OPT_GEN(join_1);
   return ret;
}

// Structure: join_1 [["AND", ["equality", "join_1"]]]
static Type g_join_1(TreeJoin_1 var) {
   Type ret = 0; 
   GEN(equality);
   
   // if st1 = 1 and st2 = 1, add == 2, then true, else, 0
   emit_ins1("add");
   emit_ins2("push", "2");
   emit_ins1("sub");
   emit_ins2f("push", "$ef%zd", EQ_COUNT);
   emit_ins1("jz");   // we want to jump if >= 2
   emit_labelf("$et%zd",EQ_COUNT);	
   emit_ins2("push", "0");
   emit_ins2f("push", "$eq%zd", EQ_COUNT);
   emit_ins1("jmp");
   emit_labelf("$ef%zd",EQ_COUNT);
   emit_ins2("push","1");
   emit_labelf("$eq%zd",EQ_COUNT);
   EQ_COUNT++;

   OPT_GEN(join_1);
   
   return ret;
}

// Structure: equality [["rel", ["rel", "equality_1"]]]
static Type g_equality(TreeEquality var) {
   Type ret = 0; 
   GEN(rel);
   OPT_GEN(equality_1);   
   
   return ret;
}

// Structure: equality_1 [["EQ", ["rel", "equality_1"]], ["NE", ["rel", "equality_1"]]]
static Type g_equality_1(TreeEquality_1 var) {
   Type ret = 0; 
   TokenCode code = var->code;
   
   g_rel(var->u.u_EQ.rel);
   
   // now generate code for == and !=
   if (var->u.u_EQ.equality_1)
      g_equality_1(var->u.u_EQ.equality_1);
   
   switch(code) {
      case TOK_EQ:
         emit_ins1("sub");
         emit_ins2f("push", "$ef%zd", EQ_COUNT);
         emit_ins1("jz");
         break;
      case TOK_NE:
         emit_ins1("sub");
         emit_ins1("not");
         emit_ins2f("push", "$ef%zd", EQ_COUNT);
         emit_ins1("jz");
         break;
      default:
         break;
   }
   
   emit_labelf("$et%zd",EQ_COUNT);	
   emit_ins2("push", "0");
   emit_ins2f("push", "$eq%zd", EQ_COUNT);
   emit_ins1("jmp");
   emit_labelf("$ef%zd",EQ_COUNT);
   emit_ins2("push","1");
   emit_labelf("$eq%zd",EQ_COUNT);
   
   EQ_COUNT++;
   // program would continue with 0/1 on stack now
   return ret;
}


// ====================================================================


static Type g_rel(TreeRel var) {
   Type ret = 0; 
   
   TokenCode code = var->code;
   code = var->code;
   GEN(expr);
   
   if (var->expr1) {
      g_expr(var->expr1);
      emit_commf("Rel compare %s",tok_string(code));
      emit_ins1("sub");
      if (code == TOK_GE || code == TOK_LE)
         emit_ins1("dup");
      emit_ins2f("push", "$rf%zd", REL_COUNT );
      
      if (code == '<') {
         emit_ins1("jn");         
      }
      else if (code == '>') {
         emit_ins1("jp");
      }
      else if (code == TOK_LE) {
         emit_ins1("jn"); 
         emit_ins2f("push", "$rf%zd", REL_COUNT );
         emit_ins1("jz");
      }
      else if (code == TOK_GE) {
         emit_ins1("jp"); 
         emit_ins2f("push", "$rf%zd", REL_COUNT );
         emit_ins1("jz");
      }
      
      emit_labelf("$rt%zd",REL_COUNT);	
      emit_ins2("push","0");
      emit_ins2f("push", "$rq%zd", REL_COUNT );
      emit_ins1("jmp");
      emit_labelf("$rf%zd", REL_COUNT);
      if (code == TOK_GE || code == TOK_LE)
         emit_ins1("pop");
      emit_ins2("push","1");
      emit_labelf("$rq%zd",REL_COUNT);	
      REL_COUNT++;
   }
   
   return ret;
}


// ====================================================================
static Type g_expr(TreeExpr var) {
   Type ret = 0; 
   GEN(term);
   OPT_GEN(expr_1);   
   
   return ret;
}

static Type g_expr_1(TreeExpr_1 var) {
   Type ret = 0; 
   GEN(term);
   if (var->code == '+')
      emit_ins1("add");
   else if (var->code == '-')
      emit_ins1("sub");
   else
      printf("gen:error:g_expr_1:\n");
   
   OPT_GEN(expr_1);
   return ret;
};


// ====================================================================
static Type g_term(TreeTerm var) {
   Type ret = 0; 
   GEN(unary);
   OPT_GEN(term_1);
   
   return ret;
}

static Type g_term_1(TreeTerm_1 var) {
   Type ret;   
   
   TokenCode code = var->code;
   
   GEN(unary);
   
   switch (code) {
      case '*': {
         emit_ins1("mul");
         break;
      } 
      case '/': {
         emit_ins1("div");
         break;
      } 
      default: {
         error_parse("gen:err:term_1");
         kill(getpid(),SIGINT);
      }
   }
   
   OPT_GEN(term_1);
   
   return ret;
}


// ====================================================================
static Type g_unary(TreeUnary var) {
   Type ret = 0; 
   TokenCode code = var->code;
   
   switch (code) {
      case '!': {  
         g_unary(var->u.u_unary.unary);
         emit_ins1("not");
         break;
      }
      case '-': {
         g_unary(var->u.u_unary.unary);
         emit_ins2("push", "-1");
         emit_ins1("mul");
		 break;
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
         emit_ins1("ld"); // load value from computed address
         break;
      }
      case TOK_NUM: {
         emit_ins2f("push","%s",var->u.u_num.num->num);
         break;
      }
      case TOK_REAL: {
         emit_ins2f("push","%s",var->u.u_real.real->real);         
         break;
      }
      case TOK_true: {  
         emit_ins2("push", "1");
         break;
      }
      case TOK_false: {  
         emit_ins2("push", "0");
         break;
      }
      default: {
         printf("gen:err:factor:code:%d\n",code);
         error_parse("gen:err:factor");
         kill(getpid(),SIGINT);
         break;
      }
   }   

   
   return ret;
}
