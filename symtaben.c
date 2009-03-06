#include "symtaben.h"
#include "scanner/scanner.h"
#include <stdlib.h>

/*
typedef struct symtabentry {
  // token id
  char *id;
  TreeType type;
  unsigned int dims;

  // table information 
  unsigned int offset;
  unsigned int depth;

  // line and column number
  unsigned int line;
  unsigned int col;
} *SymtabEntry;

*/
extern SymtabEntry SymtabEntryNew(char *id, TreeType type) {
	SymtabEntry entry = malloc(sizeof(struct SymtabEntry));
	if (!entry) ERR("SymtabEntry malloc() failed");
	
	entry->type = type; // store var type
   entry->offset = SYM_OFFSET++; // increment offset of var
   entry->depth = SYM_DEPTH; // block depth
	entry->line = line(); // source line
	entry->col = col(); // source col
	
	// count number of dimensions in array
	unsigned int dims = 0;
	TreeType_1 head = type->type_1;
	while (head) {
		dims++;
		head = head->type_1;
	}
	entry->dims = dims;
	
	return entry;
}