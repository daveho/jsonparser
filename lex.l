%{

#include "util.h"
#include "node.h"
#include "parse.tab.h"

int create_token(int kind, const char *lexeme);
void add_to_string(const char *s);

// FIXME: fixed-size buffer for scanning string literals
char g_strbuf[4096];
%}

%option noyywrap
%x STRLIT

%%

"{"                 { return create_token(TOK_LBRACE, yytext); }
"}"                 { return create_token(TOK_RBRACE, yytext); }
"["                 { return create_token(TOK_LBRACKET, yytext); }
"]"                 { return create_token(TOK_RBRACKET, yytext); }
":"                 { return create_token(TOK_COLON, yytext); }
","                 { return create_token(TOK_COMMA, yytext); }

"-"?(0|[1-9][0-9]*)("."[0-9]*)?((e|E)("+"|"-")?[0-9]+)? { return create_token(TOK_NUMBER, yytext); }

[ \t\r\n\v]+        { /* ignore whitespace */ }

                    /* beginning of string literal */
\"                  { g_strbuf[0] = '\0'; add_to_string("\""); BEGIN STRLIT; }
                    /* escape sequence */
<STRLIT>\\([\\\"/bfnrt]|u[0-9A-Fa-f]{4}) {  add_to_string(yytext); }
                    /* "ordinary" character in string (should reject control chars) */
<STRLIT>.           { add_to_string(yytext); }
                    /* string literal ends */
<STRLIT>\"          { add_to_string("\"");
                      BEGIN INITIAL;
                      return create_token(TOK_STRING_LITERAL, g_strbuf); }

.                   { err_fatal("Unknown character"); }

%%

int create_token(int kind, const char *lexeme) {
  struct Node *n = node_alloc_str_copy(kind, lexeme);
  // FIXME: set source info
  yylval.node = n;
  return kind;
}

void add_to_string(const char *s) {
  strcat(g_strbuf, s);
}
