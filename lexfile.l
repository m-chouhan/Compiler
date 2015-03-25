%{
	extern void yyerror(const char *ch);	
	#include "y.tab.h"
	#include <string.h>
	char buffer[100];
%}

digit [0-9]
digits [0-9]+
alpha [a-zA-Z]+
float [digits]\.[digits]
alphanum [a-zA-Z]+[a-zA-Z0-9]+

%%

"if"  	 {
		//printf("\nLex\tKEYWORD:%s\n",yytext);
		return IF; 
	 }
"else"   {
		//printf("\nLex\tKEYWORD:%s\n",yytext);
		return ELSE; 
	 }

"while"  {
		//printf("\nLex\tKEYWORD:%s\n",yytext);
		return WHILE; 
	 }
"declare"  {
		//printf("\nLex\tKEYWORD %s\n",yytext);
		return DECLARE;
	 }
{alpha}  {
		//printf("\nLex\tAlphabet:%s\n",yytext);
		strcpy(buffer,yytext);
		strtok(buffer," ");
		strcpy(yylval.symbol,buffer);
		return ALPHA; 
	 }
{digits}\.{digits}	{
				//printf("\nLex\tFloating:%s\n",yytext);
				yylval.fvalue = atof(yytext);
				return FLOAT; 
			}
{digits} { 	
		yylval.ivalue = atoi(yytext);
		return INTEGER;
	 }

[\n] 	 	yylineno++; 

[ \t]+    ;

"=="		return EQ;
"!="		return NEQ;
">="		return GEQ;	
"<="		return LEQ;
	
[-+*/;()={}<>]  {
			return *yytext;
		}

. 	{ 
		yyerror("Invalid Token");
		return 0; 
	}

%%

int yywrap(void)
{
	return 1;
}
/*
void main(void)
{
	yylex();
	printf("\n%d",yylineno);
}
*/
