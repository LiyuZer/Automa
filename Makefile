CC=g++
CFLAGS = -Wall -g -std=c++17


all:automa 

automa: main.o runtime.o ast_tree.o automaTokenDef.o grammer_def.o
	$(CC) -o automa main.o runtime.o ast_tree.o automaTokenDef.o grammer_def.o

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



