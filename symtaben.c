#include <stdlib.h>
#include "symtaben.h"
#include "scanner/scanner.h"
#include "scanner/error.h"

#include "symtaben.h"
#include "tree.h"

unsigned int SYM_OFFSET = 0;
unsigned int SYM_DEPTH = 0;
unsigned int SYM_MAX_DEPTH = 0;

extern SymtabEntry SymtabEntryNew(char *id, TreeType type) {
	SymtabEntry entry = malloc(sizeof(struct symtabentry));
	if (!entry) ERR("SymtabEntry malloc() failed");
	
   entry->id = id;
   entry->tok_code = type->basic->code;
	entry->type = type; // store var type
   entry->offset = SYM_OFFSET++; // increment offset of var
   entry->depth = SYM_DEPTH; // block depth
	entry->line = line(); // source line
	entry->col = col(); // source col
	
	// count number of dimensions in array
	unsigned int dims = 0;
	TreeType_1 head = type->type_1;
	while (head && (dims < SYM_MAX_DIMS) ) {
		dims++;
		head = head->type_1;
	}
	entry->dims = dims;
	
	return entry;
}




