#include <stdio.h>
#include "node.h"
#include "grammar_symbols.h"

int yyparse(void );

int main(void) {
  // yyparse() will set this to the root of the parse tree
  extern struct Node *g_parse_tree;

  yyparse();

  printf("TODO: print parse tree\n");
  return 0;
}
