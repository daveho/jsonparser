%{

#include "util.h"
#include "node.h"
#include "parse.tab.h"

struct Node *create_token(int kind);

%}

%%

"{"                       { return create_token(TOK_LBRACE); }
"}"                       { return create_token(TOK_RBRACE); }
"["                       { return create_token(TOK_LBRACKET); }
"]"                       { return create_token(TOK_RBRACKET); }
":"                       { return create_token(TOK_COLON); }
","                       { return create_token(TOK_COMMA); }

"-"?[0-9]+("."[0-9]*)?    { return create_token(TOK_NUMBER); }

[ \t\r\n\v]+              { /* ignore whitespace */ }

\"                        { /* TODO: handle string literal */ }

.                         { err_fatal("Unknown character"); }

%%

struct int create_token(int kind) {
  struct Node *n = node_alloc_str_copy(kind, yytext);
  // FIXME: set source info
  yylval.node = n;
  return kind;
}
