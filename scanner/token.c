#include "token.h"


extern char *tok_string(TokenCode tokid) {
	char *name = "";
	if ( tokid == TOK_ERROR )  {	name = "TOK_ERROR"; }
	if ( tokid == TOK_AND   )  {	name = "TOK_AND"; }
	if ( tokid == TOK_EQ    )  {	name = "TOK_EQ"; }
	if ( tokid == TOK_GE    )  {	name = "TOK_GE"; }
	if ( tokid == TOK_ID    )  {	name = "TOK_ID"; }
	if ( tokid == TOK_LE    )  {	name = "TOK_LE"; }
	if ( tokid == TOK_NE    )  {	name = "TOK_NE"; }
	if ( tokid == TOK_OR    )  {	name = "TOK_OR"; }
	if ( tokid == TOK_REAL  )  {	name = "TOK_REAL"; }
	if ( tokid == TOK_break )  {	name = "TOK_break"; }
	if ( tokid == TOK_do    )  {	name = "TOK_do"; }
	if ( tokid == TOK_if    )  {	name = "TOK_if"; }
	if ( tokid == TOK_else  )  {	name = "TOK_else"; }
	if ( tokid == TOK_read  )  {	name = "TOK_read"; }
	if ( tokid == TOK_REAL  )  {	name = "TOK_REAL"; }
	if ( tokid == TOK_NUM   )  {	name = "TOK_NUM"; }
	if ( tokid == TOK_int   )  {	name = "TOK_int"; }
	if ( tokid == TOK_float )  {	name = "TOK_float"; }
	if ( tokid == TOK_true  )  {	name = "TOK_true"; }
	if ( tokid == TOK_false )  {	name = "TOK_false"; }
	if ( tokid == TOK_while )  {	name = "TOK_while"; }
   if ( tokid == TOK_write )  {  name = "TOK_write"; }
   
   if ( tokid == '(' )  {  name = "("; }
   if ( tokid == ')' )  {  name = ")"; }
   if ( tokid == '*' )  {  name = "*"; }
   if ( tokid == '+' )  {  name = "+"; }
   if ( tokid == '-' )  {  name = "-"; }
   if ( tokid == ';' )  {  name = ";"; }
   if ( tokid == '[' )  {  name = "["; }
   if ( tokid == ']' )  {  name = "]"; }
   if ( tokid == '{' )  {  name = "{"; }
   if ( tokid == '}' )  {  name = "}"; }
   if ( tokid == '#' )  {  name = "#"; }
   if ( tokid == '<' )  {  name = "<"; }
   if ( tokid == '>' )  {  name = ">"; }
   if ( tokid == '/' )  {  name = "/"; }
   if ( tokid == '!' )  {  name = "!"; }
   if ( tokid == '=' )  {  name = "="; }
   if ( tokid == '#' )  {  name = "#"; }
   if ( tokid == '&' )  {  name = "&"; }
   if ( tokid == '|' )  {  name = "|"; }
	
	return name;
}

