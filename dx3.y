
%{
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>
#include "functions.c"

#define MAX_VARIABLES 10
#define NOT_DEF "ND"

//Default mandatory functions
extern FILE *yyin;
extern int yylex();
void yyerror(char *msg);
int yywrap();

//Symbol table functions
int lookup(char id[]);
int insert(char id[], float val);

//Symbol table variables
float table[10]; //values
char labels[10][10]; //labels
int next = 0; //next free position

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
	| ID '=' EXP {int res = lookup($1); if(res == -1 && next < MAX_VARIABLES) res = insert($1, $3); }
	| NUMBER  {$$ = $1;}
	| ID {int index = lookup($1); $$ = table[index];};
   
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
	FILE *fh;
    	if (argc == 2 && (fh = fopen(argv[1], "r")))
        	yyin = fh;
	
	yyparse();
	return 0;
	}	

//lookup to check if a given variable name is already in use
int lookup(char id[]){
	//we traverse the whole list of variable
	for(int i = 0; i < MAX_VARIABLES; i++){
		if(strcmp(id, labels[i]) == 0) //if we find it we return the id
			return i;
	}
	
	return -1;
}

//Insert to add a new value if the label of the variable is not present. 
//Executed only if we still have space to store new variables.
int insert(char id[], float val){
	
	//We copy the label in the next free location
	strcpy(labels[next], id);
	table[next] = val; //we add the value in the corresponding position
	
	next++; //we increase the index for the next free position
	
	return next-1; //and we return the one we just add
		
}


