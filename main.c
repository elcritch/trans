#include "tree.h"
#include "parser.h"
#include "generator.h"

int main() {
   
   TreeBlock block = parse();
   
   if (PARSE_ERROR == 0)
      generate(block);
      
   return PARSE_ERROR + GEN_ERROR;
}
