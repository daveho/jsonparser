%{
#include <stdarg.h>
#include "util.h"
#include "node.h"
#include "grammar_symbols.h"

int yylex(void);
void yyerror(const char *fmt, ...);

// Global variable pointing to root of parse tree
struct Node *g_parse_tree;
%}

%union {
  struct Node *node;
}

%token<node> TOK_LBRACE TOK_RBRACE TOK_LBRACKET TOK_RBRACKET
%token<node> TOK_COLON TOK_COMMA
%token<node> TOK_NUMBER TOK_STRING_LITERAL

%type<node> value
%type<node> object opt_field_list field_list field
%type<node> array opt_value_list value_list

%%

value
	: object { $$ = g_parse_tree = node_build1(NODE_value, $1); }
	| array { $$ = g_parse_tree = node_build1(NODE_value, $1); }
	| TOK_NUMBER { $$ = g_parse_tree = node_build1(NODE_value, $1); }
	| TOK_STRING_LITERAL { $$ = g_parse_tree = node_build1(NODE_value, $1); }
	;

object
	: TOK_LBRACE opt_field_list TOK_RBRACE { $$ = node_build3(NODE_object, $1, $2, $3); }
	;

opt_field_list
	: field_list { $$ = node_build1(NODE_opt_field_list, $1); }
	| /* epsilon */ { $$ = node_build0(NODE_opt_field_list); }
	;

field_list
	: field { $$ = node_build1(NODE_field_list, $1); }
	| field TOK_COMMA field_list { $$ = node_build3(NODE_field_list, $1, $2, $3); }
	;

field
	: TOK_STRING_LITERAL TOK_COLON value { $$ = node_build3(NODE_field, $1, $2, $3); }
	;

array
	: TOK_LBRACKET opt_value_list TOK_RBRACKET { $$ = node_build3(NODE_array, $1, $2, $3); }
	;

opt_value_list
	: value_list { $$ = node_build1(NODE_opt_value_list, $1); }
	| /* epsilon */ { $$ = node_build0(NODE_opt_value_list); }
	;

value_list
	: value { $$ = node_build1(NODE_value_list, $1); }
	| value TOK_COMMA value_list { $$ = node_build3(NODE_value_list, $1, $2, $3); }
	;

%%

void yyerror(const char *fmt, ...) {
  va_list args;

  va_start(args, fmt);
  verr_fatal(fmt, args);
  va_end(args);
}
