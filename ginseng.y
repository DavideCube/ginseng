
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "libs/core/arithmetic.h"
#include "libs/core/intro.h"
#include "libs/data/LinkedList.h"

#define NOT_DEF "ND"

//Default mandatory functions
extern FILE *yyin;
extern int yylex();
extern int yylineno;
void yyerror(char *msg);
int yywrap();


//Symbol table variable (cremo is now a contributor yeee)
Node *start = NULL;

%}


%union{
	double value;
	char name[20];
	char *strval;
}
	

%token NUMBER
%token ID
%token PRINT
%token<strval> STRING
%token GINSENG
%type<value> NUMBER EXP
%type<name> ID


%right '=' '_'
%left "print"
%left '+' '-'
%left '*' '/' '^' '%' '!'

%%

P: S '.' {return 0;};

S: 	EXP
	|OP
	| EXP ';' S
	| OP ';' S;


OP: 	PRINT PRINTABLE {printf("\n");};


PRINTABLE:  EXP {printf("%f", $1);}
	   | STRING {printf("%s", $1);}
	   | PRINTABLE '_' EXP {printf("%f", $3);} 
	   | PRINTABLE '_' STRING {printf("%s", $3);} ;
	   | GINSENG {cup();}

EXP:    
	 EXP '+' EXP {$$ = $1 + $3; }
	| EXP '-' EXP {$$ = $1 - $3;}
	| EXP '*' EXP {$$ = $1 * $3;}
	| EXP '/' EXP {$$ = $1 / $3;}
	| EXP '^' EXP {$$ = _pow($1,$3);}
	| EXP '%' EXP {$$ = (double)((int)$1 % (int)$3);}
	| EXP '!' {$$ = $1 >= 0 ? _fac($1) : -1;}
	| '(' EXP ')' {$$ = $2;}
	| ID '=' EXP {define(&start, $1, $3);}
	| NUMBER  {$$ = $1;}
	| '-' NUMBER {$$ = -$2;}
	| ID {Node *res = find(start, $1); if (res != NULL) $$ = res->value; else yyerror("Syntax error: use of an undeclared variable");};

%%


void yyerror(char *msg) {
	fprintf(stderr, "Line %d - %s\n", yylineno, msg);
	exit(1);
	}

int yywrap()
{
        return 1;
}

int main(int argc, char* argv[]) {
	
	FILE *fh;
    	if (argc == 2 && (fh = fopen(argv[1], "r")))
        	yyin = fh;
	else{
		intro();
	}
		
	
	yyparse();
	return 0;
	}	

