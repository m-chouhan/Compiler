%{
	#include <iostream>
	#include <stdio.h>
	#include <vector>
	#include "NodeHeader2.h"
	extern int yylineno;
	extern int yylex(void);
	extern void yyerror(const char *);

	using namespace std;
	int id;
	Stack St;
%}

%union{
	char byte;
	int ivalue;
	double dvalue;
	char symbol[50];
	class Node *nptr;
	class BlockNode *bptr;
}

%token <ivalue> INTEGER
%token <dvalue> DOUBLE
%token <byte> BYTE
%token <symbol> ALPHA
%token OBJECT
%token IF ELSE WHILE
%token DECLARE
%token EQ NEQ LEQ GEQ

%type <nptr> expr statement statements
%type <bptr> block

%left EQ NEQ LEQ GEQ
%right '='
%right '+' '-' 
%right '*' 
%right '/'

%%

start:
	statements			{
						printf("\nEND\n");
						St.B[0]->Process();	
						//$1->Process();
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
					}
	;
bclose:
	'}'
	;
objtype:
	INTEGER
	|DOUBLE
	|BYTE
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

		|DECLARE ALPHA ':' objtype ';' 	{
							St.AddSymbol($2,$4);
						}
		|block			{
						if($1->size > 0);
							St.Add($1);
					}
		;
expr:
	INTEGER				{ 
						$$ = Create($1,INTEGER);		
					}
	|ALPHA				{
						int pos = St.FindSymbol($1); 
						$$ = Create($1,pos);
					}
	|DOUBLE				{}
	|BYTE				{}
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
						int pos = St.FindSymbol($1); 
						Node *ptr = Create($1,pos);
						$$ = Create(ptr,$3,'=');		
					}
	;

%%

void yyerror(const char *ch)
{
	printf("\n%s on lineNo:%d\n",ch,yylineno);
	exit(0);
}

int main()
{
	yyparse();
	return 0;
}

