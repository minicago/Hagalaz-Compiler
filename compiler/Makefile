CC = g++
CFLAGS = -g -Wall -std=c++17
ANSC = arm-linux-gnueabihf-gcc
QEMU = qemu-arm-static
LIB_DIR = .
LIB = $(LIB_DIR)/libsysy.a
LD_OPT = -I$(LIB_DIR) -L$(LIB_DIR) -static -lsysy
LEX = flex
YACC = bison

.PHONY: all clean run

lex.yy.c: lex.l
	$(LEX) -o $@ $<

y.tab.c: yacc.y
	$(YACC) -o $@ -d $<

hagalaz: y.tab.c lex.yy.c AST.cpp displayAST.cpp output.cpp main.cpp genIR.cpp tool.cpp scope.cpp type.cpp ir.cpp lir.cpp
	$(CC) -o $@ $^ -lfl

test.c : test.sy
	cp $< $@

test.ans.S : test.c
	$(ANSC) -S -o $@ $<

test.S : test.sy hagalaz
	./hagalaz -S -o test.S test.sy

test: test.S
	$(ANSC) -o test $< $(LD_OPT)

test.ans : test.ans.S
	$(ANSC) -o test.ans $< $(LD_OPT)

run: test
	@echo "Running test..."
	@-$(QEMU) test; \
		echo $$?
	@echo "Test completed."

run-ans: test.ans
	@echo "Running test.ans..."
	@-$(QEMU) test.ans; \
		echo $$?
	@echo "Test.ans completed."


clean:
	@echo "Cleaning up..."
	@rm -f *.o lex.yy.c y.tab.c y.tab.h hagalaz
	@echo "Cleaned up."

.PHONY: clean