%{
#include <stdio.h>
#include "y.tab.h"


%}



%option noyywrap

%%

(([1-9][0-9]*)|0)(\.[0-9]+)?           	{yylval.value=atof(yytext); return NUMBER;} //it is a number, we return the value
"p"			{return yytext[0];}
[a-zA-Z_][a-zA-Z0-9_]*  {strcpy(yylval.name,yytext); return ID;} //it is a string, we copy it in the value
[-+*/().=;^]		{return yytext[0];}
[\t\v\f\n]+		{;}/*ignore end of line*/
" "			{;}
"//".*			{;} //ignore comments in C style

%%

