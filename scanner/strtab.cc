#include <stdlib.h>
#include <string.h>
#include <set>

#include "strtab.h"
#include "error.h"

using namespace::std;

struct str_less {
  bool operator() (char* x, char* y) const { return strcmp(x,y) < 0; }
};

typedef set<char*,str_less> Set;
typedef pair<Set::iterator,bool> Pair;

static char* stralloc(char* s, int len) {
  char* t=(char*)malloc(len+1);
  if (!t)
    ERR("malloc() failed");
  memcpy(t,s,len);
  t[len]=0;
  return t;
}

extern LINKAGE char *strtabget(char *s, int len) {
  static Set tab;
  char c=s[len];
  s[len]=0;
  Pair p=tab.insert(s);
  s[len]=c;
  if (p.second) {
    tab.erase(p.first);
    p=tab.insert(stralloc(s,len));
  }
  return *p.first;
}
