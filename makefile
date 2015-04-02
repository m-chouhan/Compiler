
yacpp:
	yacc -d yaccFile.y
	lex lexfile.l
	g++ -g lex.yy.c y.tab.c Node.cpp -o compiler -lfl
