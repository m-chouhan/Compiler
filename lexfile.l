%{
	extern void yyerror(const char *ch);	
	#include "y.tab.h"
	#include <string.h>
	char buffer[100];
%}

digit [0-9]
digits [0-9]+
alpha [a-zA-Z]+
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
"declare" return DECLARE;

"print"	  return PRINT;
	
"int"	return KEY_INT;
	
"byte"  return KEY_BYTE;

"double" return KEY_DOUBLE;	

{alpha}  {
		//printf("\nLex\tAlphabet:%s\n",yytext);
		strcpy(buffer,yytext);
		strtok(buffer," ");
		strcpy(yylval.symbol,buffer);
		return ALPHA; 
	 }

"'"[a-zA-Z0-9]"'"	{
				yylval.byte = yytext[1];
				//printf("%s\n",yytext);
				return BYTE;	
			}

{digits}\.{digits}	{
				//printf("\nLex\tFloating:%s\n",yytext);
				yylval.dvalue = atof(yytext);
				return DOUBLE; 
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
	
[-+*/,;()={}<>:]  {
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
