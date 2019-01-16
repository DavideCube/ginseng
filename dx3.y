
%{
#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

#define MAX_STRING_LENGTH 10

//Default mandatory functions
extern int yylex();
void yyerror(char *msg);
int yywrap();

//Symbol table functions
int lookup(char id[]);
int insert(char id[], int val);

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
%left '*' '/'

%%

P: S '.' {return 0;};

S: 	EXP
	|OP
	| EXP ';' S
	| OP ';' S;


OP: 	'p' EXP {printf("Output: %f\n", $2);};


EXP:    
	 EXP '+' EXP {$$ = $1 + $3; }
	| EXP '-' EXP {$$ = $1 - $3;}
	| EXP '*' EXP {$$ = $1 * $3;}
	| EXP '/' EXP {$$ = $1 / $3;}
	| '(' EXP ')' {$$ = $2;}
	| ID '=' EXP {int res = lookup($1); if(res == -1) res = insert($1, $3); }
	|NUMBER  {$$ = $1;}
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

int main() {
	yyparse();
	return 0;
	}	

//lookup to check if a given variable name is already in use
int lookup(char id[]){
	//we traverse the whole list of variable
	for(int i = 0; i < 10; i++){
		if(strcmp(id, labels[i]) == 0) //if we find it we return the id
			return i;
	}
	
	return -1;
}

int insert(char id[], int val){
	
	//labels[next] = id;
	strcpy(labels[next], id);
	table[next] = val;
	
	next++;
	
	return next-1;
}
