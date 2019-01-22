
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "libs/core/arithmetic.h"
#include "libs/data/LinkedList.h"

#define NOT_DEF "ND"

//Default mandatory functions
extern FILE *yyin;
extern int yylex();
void yyerror(char *msg);
int yywrap();

//Symbol table variable
Node *start = NULL;

%}


%union{
	float value;
	char name[10];
}
	

%token NUMBER
%token ID
%type<value> NUMBER EXP
%type<name> ID


%right '='
%left 'p'
%left '+' '-'
%left '*' '/' '^' '%' '!'

%%

P: S '.' {return 0;};

S: 	EXP
	|OP
	| EXP ';' S
	| OP ';' S;


OP: 	'p' EXP {printf("%f\n", $2);};


EXP:    
	 EXP '+' EXP {$$ = $1 + $3; }
	| EXP '-' EXP {$$ = $1 - $3;}
	| EXP '*' EXP {$$ = $1 * $3;}
	| EXP '/' EXP {$$ = $1 / $3;}
	| EXP '^' EXP {$$ = myPow($1,$3);}
	| EXP '%' EXP {$$ = (float)((int)$1 % (int)$3);}
	| EXP '!' {$$ = $1 >= 0 ? fac($1) : -1;}
	| '(' EXP ')' {$$ = $2;}
	| ID '=' EXP {define(&start, $1, $3);}
	| NUMBER  {$$ = $1;}
	| ID {Node *res = find(start, $1); if (res != NULL) $$ = res->value; else yyerror("Syntax error: use of an undeclared variable");};

%%

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
	}

int yywrap()
{
        return 1;
}

int main(int argc, char* argv[]) {
	printf("<---Welcome to DX3 command-line!--->\n");
	FILE *fh;
    	if (argc == 2 && (fh = fopen(argv[1], "r")))
        	yyin = fh;
	
	yyparse();
	return 0;
	}	

