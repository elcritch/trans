#ifndef SYMTAB_H
#define SYMTAB_H

#include "scanner/linkage.h"
#include "symtaben.h"

extern LINKAGE void SymtabPush(void);
extern LINKAGE void SymtabPop(void);
extern LINKAGE SymtabEntry SymTabGetTop(char* id);
extern LINKAGE SymtabEntry SymTabGet(char* id);
extern LINKAGE SymtabEntry SymTabPut(char* id, SymtabEntry entry);

#endif
