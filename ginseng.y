
%{
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "libs/core/arithmetic.h"
#include "libs/core/intro.h"
#include "libs/data/LinkedList.h"
#include "libs/data/set.h"


//Default mandatory functions
extern FILE *yyin;
extern int yylex();
extern int yylineno;
void yyerror(char *msg);
int yywrap();


//Symbol table variable (cremo is now a contributor yeee)
Node *start = NULL;
Node *arrTemp = NULL;
struct set_t* setTemp = NULL;
struct set_t* setTemp2 = NULL;
Node *ifTable = NULL;
int indexArr = 0;
char tempLab[12];

//Flow of control variables
int execute = 1;
int restore;
int elseVal = 0;

int ifCount = 0;
double exec;
%}


%union{
	double value;
	char name[20];
	char *strval;
	
}
	

%token NUMBER
%token ID SET
%token PRINT LENGTH IF THEN ELSE STATLIST
%token EQUAL NOTEQUAL LESS GREATER LESSEQUAL GREATEREQUAL
%token UNION DIFFERENCE INTERSECTION SUBSET SETEQUALS CONTAINS
%token<strval> STRING ARRID
%token GINSENG
%type<value> NUMBER EXP
%type<name> ID SET


%right '=' '_'
%left "print"
%left '+' '-' UNION INTERSECTION DIFFERENCE
%left '*' '/' '^' '%' '!'

%%

P: S '.' {return 0;};

S: 	|ASSIGNMENT
	|OP
	| ASSIGNMENT ';' S
	| OP ';' S
	| IFSTAT S;


OP: 	PRINT PRINTABLE {if(execute) printf("\n");};

PRINTABLE:  EXP { if(execute) printf("%f", $1);}
	   | STRING { if(execute) printf("%s", $1);}
	   | SET { if(execute) {Node *res = find(start, $1); if (res != NULL && res->array == NULL) _print(res->setType); else yyerror("Syntax error: used of an undeclared set"); } }
	   | ARRID { if(execute) print_array($1, &start);}
	   | PRINTABLE '_' EXP {if(execute) printf("%f", $3);} 
	   | PRINTABLE '_' STRING {if(execute) printf("%s", $3);}
	   | PRINTABLE '_' ARRID {if(execute) print_array($3, &start);}
	   | PRINTABLE '_' SET {if(execute) {Node *res = find(start, $3); if (res != NULL && res->array == NULL) _print(res->setType); else yyerror("Syntax error: used of an undeclared set");} }
	   | GINSENG {if(execute) cup();};

ASSIGNMENT: 
	ID '=' EXP {if(execute) define(&start, $1, $3, NULL, NULL);}
	|ARRID '=' ARRAY {if(execute) {define(&start, $1, 0.0, arrTemp, NULL); arrTemp = NULL;} }
	|ARRID '[' EXP ']' '=' EXP {if(execute) setArrayItem(&start, $1, $3, $6);}
	|SET '=' {setTemp = _create(); setTemp2 = _create();} SET_EXPRESSION {define(&start, $1, 0.0, NULL, setTemp);};;

SET_EXPRESSION: '{' SETLIST '}' 
				| UNION_EXP
				| DIFF_EXP
				| INT_EXP;

UNION_EXP: SET {Node *setOne = find(start, $1); if(setOne != NULL) setTemp = setOne->setType; else yyerror("Syntax error: used of an undeclared set");}
			| EXP {_insert(setTemp, $1);}
			| UNION_EXP UNION EXP {_insert(setTemp, $3);};
			| UNION_EXP UNION SET {Node *setOne = find(start, $3); if(setOne != NULL) setTemp = _union(setOne->setType, setTemp); else yyerror("Syntax error: used of an undeclared set");};

INT_EXP : SET {Node *setOne = find(start, $1); if(setOne != NULL) setTemp = setOne->setType; else yyerror("Syntax error: used of an undeclared set");}
			|INT_EXP INTERSECTION SET {Node *setOne = find(start, $3); if(setOne != NULL) setTemp = _intersect(setTemp, setOne->setType); else yyerror("Syntax error: used of an undeclared set");}

DIFF_EXP: SET {printf("Temp contains now a set\n"); Node *setOne = find(start, $1); if(setOne != NULL) setTemp = setOne->setType; else yyerror("Syntax error: used of an undeclared set");}
			| DIFF_EXP DIFFERENCE EXP {printf("Removing from temp %f\n", $3); _remove(setTemp, $3);};
			| DIFF_EXP DIFFERENCE SET {Node *setOne = find(start, $3); if(setOne != NULL) setTemp = _diff(setTemp, setOne->setType); else yyerror("Syntax error: used of an undeclared set");};

SETLIST: EXP {_insert(setTemp, $1);}
		|EXP ',' SETLIST {_insert(setTemp, $1);};
EXP:    
	 EXP '+' EXP {$$ = $1 + $3; }
	| EXP '-' EXP {$$ = $1 - $3;}
	| EXP '*' EXP {$$ = $1 * $3;}
	| EXP '/' EXP {$$ = $1 / $3;}
	| EXP '^' EXP {$$ = _pow($1,$3);}
	| EXP '%' EXP {$$ = (double)((int)$1 % (int)$3);}
	| EXP '!' {$$ = $1 >= 0 ? _fac($1) : -1;}
	| '(' EXP ')' {$$ = $2;}
	| NUMBER  {$$ = $1;}
	| '-' NUMBER {$$ = -$2;}
	|ARRID '[' EXP ']'{$$ = returnArrayItem( &start, $1, (int) $3); }
	| LENGTH '(' ARRID ')' {$$ = arrayLength(&start, $3);}
	| SUBSET '(' SET ',' SET ')' {Node *setOne = find(start, $3); Node *setTwo = find(start, $5); if(setOne != NULL && setTwo != NULL) $$ = _is_subset(setOne->setType, setTwo->setType); else yyerror("Syntax error: used of an undeclared set");}
	| SETEQUALS '(' SET ',' SET ')' {Node *setOne = find(start, $3); Node *setTwo = find(start, $5); if(setOne != NULL && setTwo != NULL) $$ = _equals(setOne->setType, setTwo->setType); else yyerror("Syntax error: used of an undeclared set");}
	| CONTAINS '(' SET ',' EXP ')' {Node *setOne = find(start, $3); if(setOne != NULL) $$ = _contains(setOne->setType, $5); else yyerror("Syntax error: used of an undeclared set");}
	| ID {Node *res = find(start, $1); if (res != NULL && res->array == NULL) $$ = res->value; else yyerror("Syntax error: use of an undeclared/wrong type variable");};
 
ARRAY: '[' ELEM ']';

ELEM :  ID {sprintf(tempLab, "%d", indexArr); Node *res = find(start, $1); if (res != NULL && res->array == NULL){ define(&arrTemp,tempLab, res->value, NULL, NULL); indexArr++; }  else yyerror("Syntax error: use of an undeclared/wrong type variable");}
	| NUMBER {sprintf(tempLab, "%d", indexArr); define(&arrTemp,tempLab, $1, NULL, NULL); indexArr++;}
	| ID {sprintf(tempLab, "%d", indexArr); Node *res = find(start, $1); if (res != NULL && res->array == NULL){ define(&arrTemp,tempLab, res->value, NULL, NULL); indexArr++; }  else yyerror("Syntax error: use of an undeclared/wrong type variable");} ',' ELEM 
	| NUMBER {sprintf(tempLab, "%d", indexArr); define(&arrTemp,tempLab, $1, NULL, NULL); indexArr++;} ',' ELEM ;


IFSTAT: IF CONDITION THEN '{' S '}' { execute = ifTable->restore; pop(&ifTable); ifCount--;}
		|IF CONDITION THEN '{' S '}' {execute = (int) ifTable->value; }  ELSE '{' S '}' {execute = ifTable->restore; pop(&ifTable); ifCount--;};


CONDITION: EXP EQUAL EXP { restore = execute; if (execute) {execute = ($1 == $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL); }
			| EXP NOTEQUAL EXP { restore = execute; if (execute) {execute = ($1 != $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL); }
		   |EXP LESSEQUAL EXP {restore = execute; if (execute) {execute = ($1 <= $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL);}
		   |EXP GREATEREQUAL EXP {restore = execute; if (execute) {execute = ($1 >= $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL);}
		   |EXP LESS EXP {restore = execute; if (execute) {execute = ($1 < $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL);}
		   |EXP GREATER EXP {restore = execute; if (execute) {execute = ($1 > $3? 1:0); elseVal = (execute==1? 0:1); } else{elseVal = 0;} ifCount++; sprintf(tempLab, "%d", ifCount); addIf(&ifTable, tempLab, elseVal, restore, NULL);};
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
		
	setTemp = _create();
	yyparse();
	return 0;
	}	