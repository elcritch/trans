%option yylineno
%option noyywrap

%x COMMENT

%{
#include "yyinput.h"
%}

digit		[0-9]
num		{digit}+

%%

"/*"		BEGIN(COMMENT);
<COMMENT>"*/"	BEGIN(INITIAL);
<COMMENT>.
<COMMENT>\n
"//".*\n

"break" return TOK_break;

{num} {
  yylval.treeNum=t_num(strtabget(yytext,yyleng));
  return TOK_NUM;
}

[ \t\n]

. error_scan(*yytext);
