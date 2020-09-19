#include <stdio.h>
#include "node.h"
#include "grammar_symbols.h"
#include "treeprint.h"

int yyparse(void );

int main(void) {
  // yyparse() will set this to the root of the parse tree
  extern struct Node *g_parse_tree;

  yyparse();

  treeprint(g_parse_tree, get_grammar_symbol_name);
  return 0;
}
