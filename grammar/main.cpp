#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "grammarAutoma/grammer_def.h"
#include "ast/ast_tree.h"

int main(){
Lexer myLexer;

string input_text;
readFile("input.txt", input_text);

Parser myParser;
shared_ptr<ParseNode> ptr;
cout << myParser.parse(myLexer,input_text, rules, ptr) << endl;

if(ptr){
    ptr->collapseDynamicNodes();
    ptr->toDot("parser.dot");
    // AbstractTreeGenerator ast_generator;
    // shared_ptr<AstNode> ast_ptr = ast_generator.generateTree(ptr);
    // write_ast_to_dot(ast_ptr, "graph.dot");
}
return 0;
}