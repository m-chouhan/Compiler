%{
	#include <stdio.h>
	#include "NodeHeader.h"
	extern int yylineno;
	extern int yylex(void);
	extern void yyerror(char *);

	int symbolTable[50];
	int id;
%}

%union{
	int ivalue;
	char sindex;
	Node *nptr;
}

%token <ivalue> INTEGER
%token KEYWORD
%token FLOAT
%token <sindex> ALPHA
%token IF
%token ELSE
%token WHILE
%token DECLARE
%token EQ
%token NEQ
%token LEQ
%token GEQ

%type <nptr> block expr statement statements

%left EQ NEQ LEQ GEQ
%left '+' '-' 
%left '*' '/'

%%

start:
	block
	;
block:
	bopen statements bclose	 	{ 
						printf("{}->"); 
					}
	;
bopen:
	'{'				{
						id = 0;
						printf("{ ...");
					}
	;
bclose:
	'}'				{
						//id = pop_id();
						printf("....}->");
					}
	;
statements:	
		statements statement	{  }
		|
		;
statement:
		expr ';'		{ $$ = $1;
					  printf("Exp:ID:%d\t val:%d\n",id++,$1); 	    
					}	
		|';'
		|IF expr block		{ printf("IF{}\n");}
		|IF expr block ELSE block	{ printf("IF{}ELSE{}\n");}

		|WHILE expr block	{ printf("WHILE{}\n");}

		|DECLARE ALPHA ';' 	{
			 			symbolTable[$2] = 0; 
						//$$ = symbolTable[$2];
					}
		;
expr:
	INTEGER				{ $$ = $1;		}
	|FLOAT
	|ALPHA				{ 
						//$$ = symbolTable[$1]; 
					}
	|'(' expr ')'			{ $$ = $2;		}
	| expr '+' expr			{ 
						$$ = $1+$3;		
					}
	| expr '-' expr			{ 
						$$ = $1-$3;		
					}
	| expr '*' expr			{ 
						$$ = $1*$3;		
					}
	| expr '/' expr			{ 
						$$ = $1/$3;		
					}
	|ALPHA '=' expr 		{
						symbolTable[$1] = $3;
						//$$ = symbolTable[$1];
					}
	;

%%

void yyerror(char *ch)
{
	printf("\n%s on lineNo:%d\n",ch,yylineno);
}

int main()
{
	yyparse();
	return 0;
}

