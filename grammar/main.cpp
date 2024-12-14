#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "lexer.h"
#include "parser.h"

int main(){
Lexer myLexer;

string input_text;
readFile("input.txt", input_text);

Parser myParser;
myParser.parse(myLexer,input_text);
return 0;
}