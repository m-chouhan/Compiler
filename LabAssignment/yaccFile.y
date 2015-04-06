%{
	#include <iostream>
	#include <stdio.h>
	#include <vector>
	#include <assert.h>
	#include "NodeHeader2.h"
	extern int yylineno;
	extern int yylex(void);
	extern void yyerror(const char *);

	using namespace std;
	int id;
	Stack St;
%}

%union{
	int ivalue;
	char symbol[50];
	class Node *nptr;
	class BlockNode *bptr;
}

%token <ivalue> INTEGER
%token <symbol> ALPHA
%token IF ELSE WHILE THEN DO READ PRINT
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
						St.Process();	
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
	'}'				{
						
						//printf("....}->");
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
		|IF expr THEN block		{ 
							$$ = Create($2,$4,IF);
							//printf("IF{}\n");
							St.Add($$);
						
						}
		|IF expr THEN block ELSE block	{
							Node *ptr = Create($4,$6,ELSE);
							$$ = Create($2,ptr,IF); 
							St.Add($$);
							//printf("IF{}ELSE{}\n");
						}

		|WHILE expr DO block	{ 
						$$ = Create($2,$4,WHILE);
						St.Add($$);
						//printf("WHILE{}\n");
					}

		|block			{
						if($1->size > 0);
							St.Add($1);
					}
		|READ ALPHA ';'		{
						St.AddSymbol($2);
						Node *ptr = Create($2);
						$$ = Create(0,ptr,READ);
						St.Add($$);	
					}
		|PRINT expr ';'		{
						$$ = Create(0,$2,PRINT);
						St.Add($$);	
					}
		;
expr:
	INTEGER				{ 
						$$ = Create($1,INTEGER);		
					}
	|ALPHA				{
						St.AddSymbol($1);
						$$ = Create($1);
					}
	|'(' expr ')'			{ 	$$ = $2;	}
	|'(' '-' expr ')'		{
					}
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
	| expr NEQ expr			{
						$$ = Create($1,$3,NEQ);		
					}
	| expr EQ  expr			{
						$$ = Create($1,$3,EQ);		
					}
	| expr GEQ expr			{
						$$ = Create($1,$3,GEQ);		
					}
	| expr LEQ expr			{
						$$ = Create($1,$3,LEQ);		
					}
	|ALPHA '=' expr 		{
						St.AddSymbol($1); 
						Node *ptr = Create($1);
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

