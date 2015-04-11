
yacpp:
	yacc -d yaccFile.y
	lex lexfile.l
	g++ -g lex.yy.c y.tab.c Node.cpp -o compiler -lfl
assemble:
	./compiler < myass.c
	nasm -felf64 Assembly.asm
	gcc Assembly.o
	./a.out
