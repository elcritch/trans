%defines
%debug
%verbose

%{
#define YYERROR_VERBOSE 1

extern Tree tree;
extern int yylex(void);
extern void yyerror(char *s);

%}

%expect 1

%union {
  TreeProgram  treeProgram;
  TreeBlock    treeBlock;
  TreeId       treeId;
  TreeNum      treeNum;
  TreeReal     treeReal;
}

%type <treeProgram>  program
%type <treeBlock>    block

%token TOK_break "break"
%token TOK_NE  "!="

%token <treeId>	  TOK_ID
%token <treeNum>  TOK_NUM
%token <treeReal> TOK_REAL

%%

program
    : block
        { tree=t_program($1); }
    ;
