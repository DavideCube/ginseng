
%{
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>

extern int yylex();
void yyerror(char *msg);
int yywrap();


%}

%union{
	float value;
}
	

%token NUMBER
%token ID
%type<value> NUMBER EXP ID


%right '='
%left 'p'
%left '+' '-'
%left '*' '/'

%%

P: S '.' {return 0;};

S: 	EXP
	|OP
	| EXP ';' S
	| OP ';' S;


OP: 	'p' EXP {printf("Result: %f\n", $2);};


EXP:    
	 EXP '+' EXP {$$ = $1 + $3; printf("Calculating %f + %f\n", $1, $3);}
	| EXP '-' EXP {$$ = $1 - $3;}
	| EXP '*' EXP {$$ = $1 * $3;}
	| EXP '/' EXP {$$ = $1 / $3;}
	| '(' EXP ')' {$$ = $2;}
	| ID '=' EXP {$1 = $3;}
	|NUMBER  {$$ = $1;}
	|ID {$$ = $1;};
   
%%

void yyerror(char *msg) {
	fprintf(stderr, "%s\n", msg);
	exit(1);
	}

int yywrap()
{
        return 1;
}

int main() {
	yyparse();
	return 0;
	}	
