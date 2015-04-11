#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20110908

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "yaccFile.y"
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
#line 16 "yaccFile.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{
	char byte;
	int ivalue;
	double dvalue;
	char symbol[50];
	class Node *nptr;
	class BlockNode *bptr;
} YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 48 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#define YYERROR_DECL() yyerror(const char *s)
#define YYERROR_CALL(msg) yyerror(msg)

extern int YYPARSE_DECL();

#define INTEGER 257
#define DOUBLE 258
#define BYTE 259
#define OBJLIST 260
#define KEY_INT 261
#define KEY_DOUBLE 262
#define KEY_BYTE 263
#define OBJECT 264
#define ALPHA 265
#define IF 266
#define ELSE 267
#define WHILE 268
#define DECLARE 269
#define PRINT 270
#define EQ 271
#define NEQ 272
#define LEQ 273
#define GEQ 274
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    5,    7,    8,    6,    6,    6,    4,    4,    3,
    3,    2,    2,    2,    2,    2,    2,    2,    2,    1,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,    1,    1,    1,
};
static const short yylen[] = {                            2,
    1,    3,    1,    1,    1,    1,    1,    3,    1,    2,
    0,    2,    1,    3,    5,    3,    4,    1,    3,    1,
    1,    1,    1,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,
};
static const short yydefred[] = {                        11,
    0,    0,   20,   22,   23,    0,    0,    0,    0,    0,
    3,   13,    0,    0,   10,   18,   11,    0,    0,    0,
    5,    6,    7,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,   12,    0,    0,    0,
   16,    0,    0,   19,   24,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    4,    2,    0,    0,   17,
   15,    8,
};
static const short yydgoto[] = {                          1,
   14,   15,    2,   43,   16,   24,   17,   57,
};
static const short yysindex[] = {                         0,
    0,   77,    0,    0,    0,  -56,  -40,  -40, -168,  -40,
    0,    0,  -40,   38,    0,    0,    0,  -40,   45,   45,
    0,    0,    0, -251,   59,  -10,  -40,  -40,  -40,  -40,
  -40,  -40,  -40,  -40,  -40,  -40,    0,   37,   98, -249,
    0,  -25,  -37,    0,    0,   67,   67,   67,   67,   67,
   67,   98,   98,  -30,  -23,    0,    0,  -94, -251,    0,
    0,    0,
};
static const short yyrindex[] = {                         0,
    0,   34,    0,    0,    0,  -39,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    7,    1,
    0,  -20,    0,    0,    0,  -34,  -15,   -3,   -1,   14,
   27,   12,   16,    2,  -32,    0,    0,    0,    0,    0,
    0,    0,
};
static const short yygindex[] = {                         0,
  145,    0,   19,  -17,   -4,    0,    0,    0,
};
#define YYTABLESIZE 347
static const short yytable[] = {                         13,
   14,   21,   21,   21,   18,   21,   34,   21,   28,   28,
   28,   35,   28,   42,   40,   41,   36,   58,   59,   21,
   21,   60,   21,   36,   34,   33,   28,   28,   11,   28,
   45,   35,   33,    1,   34,   38,   36,   31,    9,   32,
   14,   62,   27,   33,   27,    0,   27,   35,    0,   31,
    0,   32,   25,   61,   29,   31,   26,   32,    0,   14,
   27,   27,    0,   27,    0,   35,   35,   30,   35,    0,
   25,   25,   29,   25,   26,   26,   13,   26,    0,   35,
   33,    0,   34,   21,   36,   30,   35,   33,   34,   34,
   28,   36,   21,   22,   23,   12,   37,   31,    0,   32,
   35,   33,    0,   34,   31,   36,   32,   33,   35,   33,
    0,   34,    0,   36,    0,    0,   13,   44,   31,   31,
   32,   32,    0,   14,   27,   14,   31,    0,   32,   35,
    0,    0,    0,    0,   25,   12,   29,    0,   26,   35,
   33,    0,   34,    0,   36,    0,    0,    0,    0,   30,
    0,   19,   20,    0,   25,    0,    0,   26,    0,   11,
    0,   56,   39,    0,    0,    0,    0,   11,    0,    0,
    0,   46,   47,   48,   49,   50,   51,   52,   53,   54,
   55,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   11,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    3,    4,    5,    0,
    0,    0,    0,    0,    6,    0,    0,    0,    0,    0,
    0,   21,   21,   21,   21,    0,    0,    0,   28,   28,
   28,   28,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   14,   14,   14,
   27,   28,   29,   30,    0,   14,   14,    0,   14,   14,
   14,    0,   27,   27,   27,   27,    0,   35,   35,   35,
   35,    0,   25,   25,   25,   25,   26,   26,   26,   26,
    0,    0,    0,    3,    4,    5,    0,    0,    0,    0,
    0,    6,    7,    0,    8,    9,   10,    0,   27,   28,
   29,   30,    0,    0,    0,   27,   28,   29,   30,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   27,
   28,   29,   30,    3,    4,    5,    0,   27,   28,   29,
   30,    6,    7,    0,    8,    9,   10,
};
static const short yycheck[] = {                         40,
    0,   41,   42,   43,   61,   45,   41,   47,   41,   42,
   43,   42,   45,  265,   19,   20,   47,  267,   44,   59,
   60,   59,   62,   47,   59,   41,   59,   60,  123,   62,
   41,   42,   43,    0,   45,   17,   47,   41,   59,   41,
   40,   59,   41,   59,   43,   -1,   45,   41,   -1,   60,
   -1,   62,   41,   58,   41,   59,   41,   59,   -1,   59,
   59,   60,   -1,   62,   -1,   59,   60,   41,   62,   -1,
   59,   60,   59,   62,   59,   60,   40,   62,   -1,   42,
   43,   -1,   45,  123,   47,   59,   42,   43,  123,   45,
  123,   47,  261,  262,  263,   59,   59,   60,   -1,   62,
   42,   43,   -1,   45,   60,   47,   62,  123,   42,   43,
   -1,   45,   -1,   47,   -1,   -1,   40,   59,   60,  123,
   62,  123,   -1,  123,  123,  125,   60,   -1,   62,  123,
   -1,   -1,   -1,   -1,  123,   59,  123,   -1,  123,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   -1,   -1,  123,
   -1,    7,    8,   -1,   10,   -1,   -1,   13,   -1,  123,
   -1,  125,   18,   -1,   -1,   -1,   -1,  123,   -1,   -1,
   -1,   27,   28,   29,   30,   31,   32,   33,   34,   35,
   36,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,   -1,
   -1,   -1,   -1,   -1,  265,   -1,   -1,   -1,   -1,   -1,
   -1,  271,  272,  273,  274,   -1,   -1,   -1,  271,  272,
  273,  274,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  257,  258,  259,
  271,  272,  273,  274,   -1,  265,  266,   -1,  268,  269,
  270,   -1,  271,  272,  273,  274,   -1,  271,  272,  273,
  274,   -1,  271,  272,  273,  274,  271,  272,  273,  274,
   -1,   -1,   -1,  257,  258,  259,   -1,   -1,   -1,   -1,
   -1,  265,  266,   -1,  268,  269,  270,   -1,  271,  272,
  273,  274,   -1,   -1,   -1,  271,  272,  273,  274,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  271,
  272,  273,  274,  257,  258,  259,   -1,  271,  272,  273,
  274,  265,  266,   -1,  268,  269,  270,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 274
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,0,0,0,
"';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"'{'",0,"'}'",0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,"INTEGER","DOUBLE","BYTE","OBJLIST","KEY_INT","KEY_DOUBLE",
"KEY_BYTE","OBJECT","ALPHA","IF","ELSE","WHILE","DECLARE","PRINT","EQ","NEQ",
"LEQ","GEQ",
};
static const char *yyrule[] = {
"$accept : start",
"start : statements",
"block : bopen statements bclose",
"bopen : '{'",
"bclose : '}'",
"objtype : KEY_INT",
"objtype : KEY_DOUBLE",
"objtype : KEY_BYTE",
"objlist : ALPHA ',' objlist",
"objlist : ALPHA",
"statements : statements statement",
"statements :",
"statement : expr ';'",
"statement : ';'",
"statement : IF expr block",
"statement : IF expr block ELSE block",
"statement : WHILE expr block",
"statement : DECLARE objtype objlist ';'",
"statement : block",
"statement : PRINT expr ';'",
"expr : INTEGER",
"expr : ALPHA",
"expr : DOUBLE",
"expr : BYTE",
"expr : '(' expr ')'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr LEQ expr",
"expr : expr GEQ expr",
"expr : expr NEQ expr",
"expr : expr EQ expr",
"expr : ALPHA '=' expr",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 169 "yaccFile.y"

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

#line 327 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 48 "yaccFile.y"
	{
						printf("\nEND\n");
						
						St.Process();	
						/*$1->Process();*/
					}
break;
case 2:
#line 56 "yaccFile.y"
	{ 
						yyval.bptr = St.Pop();
						/*printf("{}->"); */
					}
break;
case 3:
#line 62 "yaccFile.y"
	{
						St.Push();
					}
break;
case 5:
#line 70 "yaccFile.y"
	{yyval.ivalue = INTEGER; }
break;
case 6:
#line 71 "yaccFile.y"
	{yyval.ivalue = DOUBLE; }
break;
case 7:
#line 72 "yaccFile.y"
	{yyval.ivalue = BYTE; }
break;
case 8:
#line 75 "yaccFile.y"
	{ yyval.nptr = Create(Create(yystack.l_mark[-2].symbol,Tuple(0,0)),yystack.l_mark[0].nptr,OBJLIST);}
break;
case 9:
#line 76 "yaccFile.y"
	{ yyval.nptr = Create(yystack.l_mark[0].symbol,Tuple(0,0)); }
break;
case 12:
#line 83 "yaccFile.y"
	{ 
						yyval.nptr = yystack.l_mark[-1].nptr;
					 	St.Add(yystack.l_mark[-1].nptr,yylineno);
					  	/*printf("Exp:ID:%d\t val:%d\n",id++,$1); 	    */
					}
break;
case 14:
#line 89 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-1].nptr,yystack.l_mark[0].bptr,IF);
						/*printf("IF{}\n");*/
						St.Add(yyval.nptr,yylineno);
						
					}
break;
case 15:
#line 95 "yaccFile.y"
	{
							Node *ptr = Create(yystack.l_mark[-2].bptr,yystack.l_mark[0].bptr,ELSE);
							yyval.nptr = Create(yystack.l_mark[-3].nptr,ptr,IF); 
							St.Add(yyval.nptr,yylineno);
							/*printf("IF{}ELSE{}\n");*/
						}
break;
case 16:
#line 102 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-1].nptr,yystack.l_mark[0].bptr,WHILE);
						St.Add(yyval.nptr,yylineno);
						/*printf("WHILE{}\n");*/
					}
break;
case 17:
#line 108 "yaccFile.y"
	{
							St.AddSymbols(yystack.l_mark[-2].ivalue,yystack.l_mark[-1].nptr);
						}
break;
case 18:
#line 111 "yaccFile.y"
	{
						if(yystack.l_mark[0].bptr->size > 0);
							St.Add(yystack.l_mark[0].bptr,yylineno);
					}
break;
case 19:
#line 115 "yaccFile.y"
	{
						yyval.nptr = Create(0,yystack.l_mark[-1].nptr,PRINT);
						St.Add(yyval.nptr,yylineno);
					}
break;
case 20:
#line 121 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[0].ivalue,INTEGER);		
					}
break;
case 21:
#line 124 "yaccFile.y"
	{
						Tuple pos = St.FindSymbol(yystack.l_mark[0].symbol); 
						yyval.nptr = Create(yystack.l_mark[0].symbol,pos);
					}
break;
case 22:
#line 128 "yaccFile.y"
	{	yyval.nptr = Create(yystack.l_mark[0].dvalue,DOUBLE);}
break;
case 23:
#line 129 "yaccFile.y"
	{	yyval.nptr = Create(yystack.l_mark[0].byte,BYTE);  }
break;
case 24:
#line 130 "yaccFile.y"
	{ 	yyval.nptr = yystack.l_mark[-1].nptr;	}
break;
case 25:
#line 131 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'+');		
					}
break;
case 26:
#line 134 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'-');		
					}
break;
case 27:
#line 137 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'*');		
					}
break;
case 28:
#line 140 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 29:
#line 143 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 30:
#line 146 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 31:
#line 149 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 32:
#line 152 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 33:
#line 155 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 34:
#line 158 "yaccFile.y"
	{ 
						yyval.nptr = Create(yystack.l_mark[-2].nptr,yystack.l_mark[0].nptr,'/');		
					}
break;
case 35:
#line 161 "yaccFile.y"
	{
						Tuple pos = St.FindSymbol(yystack.l_mark[-2].symbol); 
						Node *ptr = Create(yystack.l_mark[-2].symbol,pos);
						yyval.nptr = Create(ptr,yystack.l_mark[0].nptr,'=');		
					}
break;
#line 722 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
