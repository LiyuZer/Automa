#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "grammer_def.h"
#include "ast_tree.h"

int main(){
Lexer myLexer;

string input_text;
readFile("input.txt", input_text);

Parser myParser;
shared_ptr<ParseNode> ptr;
cout << myParser.parse(myLexer,input_text, rules, ptr) << endl;

if(ptr){
    ptr->collapseDynamicNodes();
    AbstractTreeGenerator ast_generator;
    ast_generator.generateTree(ptr);
}
return 0;
}