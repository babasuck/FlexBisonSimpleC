%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
%}

%union {
    int intValue;
    double doubleValue;
    bool boolValue;
    char* string;
    ASTNode *node;
}

%token <intValue> INT_NUMBER
%token <doubleValue> DOUBLE_NUMBER
%token <boolValue> BOOL_VALUE
%token <string> IDENTIFIER
%token START END INT DOUBLE BOOL AND OR XOR
%token PLUS MINUS MULT DIV ASSIGN SEMICOLON LPAREN RPAREN

%type <node> program statements statement expression declaration

%code {
    int yylex(void);
    extern FILE *yyin;
}

%%

program:
    START statements END
    ;

statements:
    
    | statements statement
    ;

statement:
      declaration SEMICOLON
    | expression SEMICOLON
    ;

declaration:
      INT IDENTIFIER { $$ = createVariableDeclarationNode("int", $2); }
    | DOUBLE IDENTIFIER { $$ = createVariableDeclarationNode("double", $2); }
    | BOOL IDENTIFIER { $$ = createVariableDeclarationNode("bool", $2); }
    ;

expression:
      INT_NUMBER { $$ = createIntNode($1); }
    | DOUBLE_NUMBER { $$ = createDoubleNode($1); }
    | BOOL_VALUE { $$ = createBoolNode($1); }
    | IDENTIFIER { $$ = createIdentifierNode($1); }
    | expression PLUS expression { $$ = createBinaryOpNode('+', $1, $3);}
    | expression MINUS expression { $$ = createBinaryOpNode('-', $1, $3); }
    | expression MULT expression { $$ = createBinaryOpNode('*', $1, $3); }
    | expression DIV expression { $$ = createBinaryOpNode('/', $1, $3); }
    | IDENTIFIER ASSIGN expression { $$ = createAssignmentNode($1, $3); }
    | LPAREN expression RPAREN { $$ = $2; }
    ;

%%

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <source file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror(argv[1]);
        return 1;
    }

    yyin = file;
    int parseResult = yyparse();
    fclose(file);

    if (parseResult == 0) {
        printf("Parsing successful.\n");
    } else {
        printf("Parsing failed.\n");
    }

    return parseResult;
}
