#include <stdlib.h>
#include "terminals.h"
#include "scanner/token.h"
#include "scanner/scanner.h"
#include "scanner/error.h"

#define ALLOC(t)		  \
  t v = malloc(sizeof(t)); \
  if (!v) ERR("malloc() failed")


// Block ["decls", "stmts"]
extern TreeId p_id() {
	ALLOC(TreeId);
	Token tok = curr();
	v->id = tok->lexeme;
	eat(TOK_ID);

	return v;
}

// TreeNum l1num = p_num();
extern TreeNum p_num() {
	ALLOC(TreeNum);
	Token tok = curr();
	eat(TOK_NUM);
	v->num = tok->lexeme;

	return v;
}

// TreeNum l1num = p_num();
extern TreeReal p_real() {
	ALLOC(TreeReal);
	Token tok = curr();
	eat(TOK_REAL);
	v->real = tok->lexeme;

	return v;
}


// TreeNum l1num = t_num();
