#include "tree.h"

// stmt : loc '=' bool ';'
//      | 'while' '(' bool ')' stmt
//      | 'break' ';'
static TreeStmt p_stmt(void) {
  TreeStmt stmt=0;
  TokenCode code=curr()->code;
  switch (code) {
    case TOK_ID: {
      TreeLoc loc = p_loc();
      eat('=');
      TreeBool bool = p_bool();
      eat(';');
      stmt = t_stmt_assign(loc,bool);
      break;
    }
    case TOK_while: {
      eat(TOK_while);
      eat('(');
      TreeBool bool=p_bool();
      eat(')');
      TreeStmt body=p_stmt();
      stmt = t_stmt_while(bool,body);
      break;
    }
    case TOK_break: {
      eat(TOK_break);
      eat(';');
      stmt=t_stmt_break();
      break;
    }
    default:
      error_parse("stmt");
      break;
  }
  return stmt;
}
