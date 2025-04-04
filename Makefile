CC=g++
CFLAGS = -Wall -g -O3 -std=c++20


all:automa 

automa: main.o runtime.o ast_tree.o automaTokenDef.o grammer_def.o operator.o  path.o vm_compiler.o
	$(CC) $(CFLAGS) -o automa main.o runtime.o ast_tree.o automaTokenDef.o grammer_def.o operator.o  path.o vm_compiler.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

runtime.o: include/impl/runtime.cpp
	$(CC) $(CFLAGS) -c include/impl/runtime.cpp

ast_tree.o: grammar/ast/ast_tree.cpp
	$(CC) $(CFLAGS)  -c grammar/ast/ast_tree.cpp

automaTokenDef.o: grammar/lexer/automaTokenDef.cpp
	$(CC) $(CFLAGS) -c grammar/lexer/automaTokenDef.cpp

grammer_def.o: grammar/grammarAutoma/grammer_def.cpp
	$(CC) $(CFLAGS) -c grammar/grammarAutoma/grammer_def.cpp

operator.o: include/impl/operator.cpp
	$(CC) $(CFLAGS) -c include/impl/operator.cpp

path.o: include/impl/path.cpp
	$(CC) $(CFLAGS) -c include/impl/path.cpp
vm_compiler.o: include/impl/vm_compiler.cpp
	$(CC) $(CFLAGS) -c include/impl/vm_compiler.cpp
# clean all the .o and executable files
clean:
	rm -f *.o automa