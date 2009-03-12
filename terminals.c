#include <stdlib.h>
#include "scanner/error.h"
#include "scanner/scanner.h"
#include "scanner/token.h"
#include "scanner/error.h"
#include "terminals.h"
#include "symtab.h"

#define ALLOC(t)		  \
  t v = malloc(sizeof(t)); \
  if (!v) ERR("malloc() failed")


// Block ["decls", "stmts"]
extern TreeId p_decl_id() {
   ALLOC(TreeId);
   Token tok = curr();
   v->lex = tok->lexeme;
   v->entry = 0;
   eat(TOK_ID);   
   return v;
}

// Block ["decls", "stmts"]
extern TreeId p_id() {
   ALLOC(TreeId);
   Token tok = curr();
   v->lex = tok->lexeme;
   v->entry = 0;
   
   if ( (v->entry = SymTabGet(v->lex)) == 0 ) {
      printf("var id:'%s'\n",v->lex);
      error_parse("Cannot find var entry!");
   }
   
   eat(TOK_ID);
   
   return v;
}

// TreeNum l1num = p_num();
extern TreeNum p_num() {
   ALLOC(TreeNum);
   Token tok = curr();
   v->num = tok->lexeme;
   v->size = -1;
   
   eat(TOK_NUM);
   return v;
}

extern TreeNum p_num_convert() {
   ALLOC(TreeNum);
   Token tok = curr();
   v->num = tok->lexeme;

   char *end = (char *)NULL;
   int size = (int)strtol( v->num, &end, 10);
   if (*end != '\0') error_parse("Number Type: cannot convert to positive integer");
   v->size = size;
   
   eat(TOK_NUM);
   return v;
}

// TreeNum l1num = p_num();
extern TreeReal p_real() {
	ALLOC(TreeReal);
	Token tok = curr();
	v->real = tok->lexeme;

	eat(TOK_REAL);
	return v;
}


// TreeNum l1num = t_num();
