%{
#include "parser.h"
%}

%option noyywrap

%%

"start"             { return START; }
"end"               { return END; }
"int"               { return INT; }
"double"            { return DOUBLE; }
"bool"              { return BOOL; }
"and"               { return AND; }
"or"                { return OR; }
"xor"               { return XOR; }

[0-9]+              { yylval.intValue = atoi(yytext); return INT_NUMBER; }
[0-9]+\.[0-9]+      { yylval.doubleValue = atof(yytext); return DOUBLE_NUMBER; }
"true"|"false"      { yylval.boolValue = (strcmp(yytext, "true") == 0); return BOOL_VALUE; }

[a-zA-Z][a-zA-Z0-9]*  { yylval.string = strdup(yytext); return IDENTIFIER; }

"+"                 { return PLUS; }
"-"                 { return MINUS; }
"*"                 { return MULT; }
"/"                 { return DIV; }

";"                 { return SEMICOLON; }
"="                 { return ASSIGN; }
"("                 { return LPAREN; }
")"                 { return RPAREN; }

[ \t\n]+            { /* skip whitespace */ }
.                   { printf("Mystery character %c\n", *yytext); }

%%
