#ifndef __PARSER_H
#define __PARSER_H 1
#include "tree.h"

TreeProgram parser(void);
TreeProgram p_Program(void) ;
TreeBlock p_block(void) ;
TreeDecls p_decls(void) ;
TreeDecl p_decl(void) ;
TreeType p_type(void) ;
TreeType_1 p_type_1(void) ;
TreeBasic p_basic(void) ;
TreeStmts p_stmts(void) ;
TreeStmt p_stmt(void) ;
TreeLoc p_loc(void) ;
TreeLoc_1 p_loc_1(void) ;
TreeBool p_bool(void) ;
TreeBool_1 p_bool_1(void) ;
TreeJoin p_join(void) ;
TreeJoin_1 p_join_1(void) ;
TreeEquality p_equality(void) ;
TreeEquality_1 p_equality_1(void) ;
TreeRel p_rel(void) ;
TreeExpr p_expr(void) ;
TreeExpr_1 p_expr_1(void) ;
TreeTerm p_term(void) ;
TreeTerm_1 p_term_1(void) ;
TreeUnary p_unary(void) ;
TreeFactor p_factor(void) ;



#endif
