
yacpp:
	yacc -d yaccFile.y
	lex lexfile.l
	g++ -g lex.yy.c y.tab.c Node.cpp -o compiler -lfl
generate:
	./compiler < myass.c
	nasm -felf64 Assembly.asm
	gcc Assembly.o
	./a.out
nasm:	Assembly.asm
	nasm -felf64 Assembly.asm
	gcc Assembly.o
	./a.out
