CC = g++
CFLAGS = -g -Wall -std=c++11

LEX = flex
YACC = bison

lex.yy.c: lex.l
	$(LEX) -o $@ $<

y.tab.c: yacc.y
	$(YACC) -o $@ -d $<

AST: y.tab.c lex.yy.c AST.cpp def.h AST.h
	$(CC) -o $@ $^ -lfl

clean:
	@echo "Cleaning up..."
	@rm -f *.o lex.yy.c y.tab.c y.tab.h AST
	@echo "Cleaned up."

.PHONY: clean