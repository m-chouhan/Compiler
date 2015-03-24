
lex:
	lex lexfile.l
	gcc lex.yy.c
	./a.out

yacc:
	yacc -d yaccFile.y
	lex lexfile.l
	gcc lex.yy.c y.tab.c -o compiler -lfl
yacpp:
	yacc -d yaccFile.y
	lex lexfile.l
	g++ lex.yy.c y.tab.c -o compiler -lfl
