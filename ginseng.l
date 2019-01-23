%{
#include <stdio.h>
#include "y.tab.h"

char* stringResize(char* text);
%}



%option noyywrap
%option yylineno
%%

(([1-9][0-9]*)|0)(\.[0-9]+)?           	{yylval.value=atof(yytext); return NUMBER;} //it is a number, we return the value
"print"			{ return PRINT;}
"ginseng"		{return GINSENG;}
[a-zA-Z][a-zA-Z0-9_]*  {strcpy(yylval.name,yytext); return ID;} //it is a string, we copy it in the value
\"[^\"]*\"	{yylval.strval = stringResize(yytext); return STRING;}
[-+*/()\.%!=;^_\[\],]		{return yytext[0];}
\<[a-zA-Z][a-zA-Z0-9_]*\> {yylval.strval = strdup(yytext); return ARRID;}
[\t\v\f\n]+		{;}/*ignore special characters*/
" "			{;} //ignore spaces
"//".*			{;} //ignore comments in C style

%%


char* stringResize(char* text){
	char* res = (char*)malloc( sizeof(char) * strlen(text) - 2 ); 
	
	for(int i = 1; i < strlen(text)-1; i++){
		res[i-1] = text[i];
	}
	
	return res;
}
