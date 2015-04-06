%{
	extern void yyerror(const char *ch);	
	#include "y.tab.h"
	#include <string.h>
	char buffer[100];
%}

digit [0-9]
digits [0-9]+
alpha [a-zA-Z]+

%%

"if"  	 {
		//printf("\nLex\tKEYWORD:%s\n",yytext);
		return IF; 
	 }
"then"	 {
		return THEN;
	 }
"else"   {
		return ELSE; 
	 }

"while"  {
		return WHILE; 
	 }
"do"	 {
		return DO;
	 }
"read"	{	
		//printf("Read Token\n");	
		return READ;
	}
"print" {
		return PRINT;
	}
{alpha}  {
		strcpy(buffer,yytext);
		strtok(buffer," ");
		strcpy(yylval.symbol,buffer);
		//printf("\nLex\tAlphabet:%s\n",yylval.symbol);
		return ALPHA; 
	 }
{digits} { 	
		//printf("\nLex\tnumber:%s\n",yytext); 
		yylval.ivalue = atoi(yytext);
		return INTEGER;
	 }

[\n] 	 { 	
		yylineno++; 
	 }

[ \t]+    ;

"=="	{
		//ECHO;
		return EQ;
	}
"!="	{
		//ECHO;
		return NEQ;
	}
">="	{
		//ECHO;	
		return GEQ;
	}
"<="	{
		//ECHO;
		return LEQ;
	}

[-+*/;()={}]  	{
			//ECHO;
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
