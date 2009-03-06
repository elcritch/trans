#include <map>
#include <vector>

#include "symtab.h"
// #include "symtaben.h"
#include "scanner/error.h"

using namespace std;

typedef map<char*,SymtabEntry> ScopeTab;
typedef vector<ScopeTab*> SymTab;

static SymTab symtab;

extern LINKAGE void SymtabPush(void) {
  symtab.push_back(new ScopeTab);
}

extern LINKAGE void SymtabPop(void) {
  if (!symtab.empty())
    symtab.pop_back();
}

static SymtabEntry SymTabGetFromTab(char* id, ScopeTab& scopeTab) {
  return scopeTab[id];
}

extern LINKAGE SymtabEntry SymTabGetTop(char* id) {
  return SymTabGetFromTab(id,*symtab.back());
}

extern LINKAGE SymtabEntry SymTabGet(char* id) {
  SymtabEntry entry=0;
  for (int i=symtab.size() ; i>0 && !entry; i--)
    entry=SymTabGetFromTab(id,*symtab[i-1]);
  return entry;
}

extern LINKAGE SymtabEntry SymTabPut(char* id, SymtabEntry entry) {
  // SymtabEntry entry;
  if (symtab.empty())
    SymtabPush();
  // entry=SymtabEntryNew(id);
  (*symtab.back())[id]=entry;
  return entry;
}


