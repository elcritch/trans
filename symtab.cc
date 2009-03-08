#include <map>
#include <vector>

#include "symtab.h"
#include "symtaben.h"
// using namespace std;

typedef std::map<char*,SymtabEntry> ScopeTab;
typedef std::vector<ScopeTab*> SymTab;
typedef struct symtabentry *SymtabEntry;


static SymTab symtab;

extern LINKAGE void SymtabPush(void) {
  SYM_DEPTH++;
  SYM_MAX_DEPTH++;
  
  symtab.push_back(new ScopeTab);
}

extern LINKAGE void SymtabPop(void) {
  if (!symtab.empty()) {
    symtab.pop_back();
    SYM_DEPTH--;
  }  
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


