%{
#include <stdio.h>
#include "y.tab.h"
%}



%option noyywrap

%%
[0-9]+           	{yylval.value=atof(yytext); return NUMBER;}
"p"			{return yytext[0];}
[a-zA-Z_][a-zA-Z0-9_]*  {return ID;} 
[-+*/().=;]		{return yytext[0];}
[\t\v\f]+		{;}/*ignore end of line*/
" "			{;}

%%
