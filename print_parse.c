#include "tree.h"
#include "terminals.h"
#include "parser.h"
#include "scanner/token.h"
#include "printlib.h"

int main (int argc, char const *argv[])
{
	// parser program
	printf("Parsing...\n");
	TreeBlock block = Program();
	
	printf("\n=============================================================\n");
	printf("Finished Parsing...\n\n");
	printf("\n=============================================================\n");
	// print AST parse tree
	print_TreeBlock( 0, block );
	
	return 0;
}

