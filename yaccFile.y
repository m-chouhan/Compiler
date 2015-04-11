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
	extern ofstream out;
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
%token OBJLIST

%token <ivalue> KEY_INT KEY_DOUBLE KEY_BYTE OBJECT
%token <symbol> ALPHA
%token IF ELSE WHILE
%token DECLARE	PRINT
%token EQ NEQ LEQ GEQ

%type <nptr> expr statement statements objlist
%type <bptr> block
%type <ivalue> objtype
%right EQ NEQ LEQ GEQ '<' '>'
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
	'}'
	;
objtype:
	KEY_INT		{$$ = INTEGER; }
	|KEY_DOUBLE	{$$ = DOUBLE; }
	|KEY_BYTE	{$$ = BYTE; }
	;
objlist:
	ALPHA ',' objlist	{ $$ = Create(Create($1,Tuple(0,0)),$3,OBJLIST);}
	|ALPHA			{ $$ = Create($1,Tuple(0,0)); }
	;
statements:	
		statements statement	
		|
		;
statement:
		expr ';'		{ 
						$$ = $1;
					 	St.Add($1,yylineno);
					  	//printf("Exp:ID:%d\t val:%d\n",id++,$1); 	    
					}	
		|';'
		|IF expr block		{ 
						$$ = Create($2,$3,IF);
						//printf("IF{}\n");
						St.Add($$,yylineno);
						
					}
		|IF expr block ELSE block	{
							Node *ptr = Create($3,$5,ELSE);
							$$ = Create($2,ptr,IF); 
							St.Add($$,yylineno);
							//printf("IF{}ELSE{}\n");
						}

		|WHILE expr block	{ 
						$$ = Create($2,$3,WHILE);
						St.Add($$,yylineno);
						//printf("WHILE{}\n");
					}

		|DECLARE objtype objlist ';' 	{
							St.AddSymbols($2,$3);
						}
		|block			{
						if($1->size > 0);
							St.Add($1,yylineno);
					}
		|PRINT expr ';'		{
						$$ = Create(0,$2,PRINT);
						St.Add($$,yylineno);
					}
		;
expr:
	INTEGER				{ 
						$$ = Create($1,INTEGER);		
					}
	|ALPHA				{
						Tuple pos = St.FindSymbol($1); 
						$$ = Create($1,pos);
					}
	|DOUBLE				{	$$ = Create($1,DOUBLE);}
	|BYTE				{	$$ = Create($1,BYTE);  }
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
	| expr '<' expr			{ 
						$$ = Create($1,$3,'/');		
					}
	| expr '>' expr			{ 
						$$ = Create($1,$3,'/');		
					}
	| expr LEQ expr			{ 
						$$ = Create($1,$3,'/');		
					}
	| expr GEQ  expr		{ 
						$$ = Create($1,$3,'/');		
					}
	| expr NEQ  expr		{ 
						$$ = Create($1,$3,'/');		
					}
	| expr EQ  expr			{ 
						$$ = Create($1,$3,'/');		
					}
	|ALPHA '=' expr 		{
						Tuple pos = St.FindSymbol($1); 
						Node *ptr = Create($1,pos);
						$$ = Create(ptr,$3,'=');		
					}
	;

%%

void yyerror(const char *ch)
{
	printf("\nError: %s on lineNo:%d\n",ch,yylineno);
	exit(0);
}
void yywarning(const char *ch)
{
	printf("\nWarning: %s on lineNo:%d\n",ch,yylineno);
}

int main()
{
	yyparse();
	return 0;
}

