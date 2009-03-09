#include "tree.h"
#include "parser.h"
#include "generator.h"

int main() {
  generate(parse());
  // return generate(parse());
  return 0;
}
