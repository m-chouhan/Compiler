%{
	//#define INTEGER 300
	extern void yyerror(char *ch);	
	#include "y.tab.h"
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
		yylval.sindex = *yytext - 'a';
		return ALPHA; 
	 }
{digits}\.{digits}	{
				//printf("\nLex\tFloating:%s\n",yytext);
				yylval.ivalue = atof(yytext);
				return FLOAT; 
			}
{digits} { 	
		//printf("\nLex\tnumber:%s\n",yytext); 
		yylval.ivalue = atoi(yytext);
		return INTEGER;
	 }

[\n] 	 { 	
		yylineno++; 
		//return *yytext; 
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
