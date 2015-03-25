%{
	#include <iostream>
	#include <stdio.h>
	#include <vector>
	#include "NodeHeader2.h"
	extern int yylineno;
	extern int yylex(void);
	extern void yyerror(char *);

	using namespace std;
	int symbolTable[50];
	int id;
	Stack St;
%}

%union{
	int ivalue;
	char *symbol;
	class Node *nptr;
}

%token <ivalue> INTEGER
%token KEYWORD FLOAT
%token <symbol> ALPHA
%token IF ELSE WHILE
%token DECLARE
%token EQ NEQ LEQ GEQ

%type <nptr> block expr statement statements

%left EQ NEQ LEQ GEQ
%right '+' '-' 
%left '*' '/'

%%

start:
	block				{
						printf("\nEND\n");
						$1->Process();
					}
	;
block:
	bopen statements bclose	 	{ 
						$$ = St.Pop();
						//printf("{}->"); 
					}
	;
bopen:
	'{'				{
						St.Push();
						//id = 0;
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
		statements statement	
		|
		;
statement:
		expr ';'		{ 
						$$ = $1;
					 	St.Add($1);
					  	//printf("Exp:ID:%d\t val:%d\n",id++,$1); 	    
					}	
		|';'
		|IF expr block		{ 
						$$ = Create($2,$3,IF);
						//printf("IF{}\n");
						St.Add($$);
						
					}
		|IF expr block ELSE block	{
							Node *ptr = Create($3,$5,ELSE);
							$$ = Create($2,ptr,IF); 
							St.Add($$);
							//printf("IF{}ELSE{}\n");
						}

		|WHILE expr block	{ 
						$$ = Create($2,$3,WHILE);
						St.Add($$);
						//printf("WHILE{}\n");
					}

		|DECLARE ALPHA ';' 	{
			 			//symbolTable[$2] = 0; 
						//$$ = Create($2,ALPHA);//change to Declare() alpha
						St.AddSymbol($2);
					}
		|block			{
						St.Add($1);
					}
		;
expr:
	INTEGER				{ 
						$$ = Create($1,INTEGER);		
					}
	|ALPHA				{ 
						$$ = Create($1);
					}
	|'(' expr ')'			{ 	$$ = $2;	}
	| expr '+' expr			{ 
						$$ = Create($1,$3,'+');		
					}
	| expr '-' expr			{ 
						$$ = Create($1,$3,'-');		
					}
	| expr '*' expr			{ 
						$$ = Create($1,$3,'*');		
					}
	| expr '/' expr			{ 
						$$ = Create($1,$3,'/');		
					}
	|ALPHA '=' expr 		{
						Node *ptr = Create($1,ALPHA);
						$$ = Create(ptr,$3,'=');		
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

