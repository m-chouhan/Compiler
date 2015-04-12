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
#define IN 271
#define EQ 272
#define NEQ 273
#define LEQ 274
#define GEQ 275
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
extern YYSTYPE yylval;
