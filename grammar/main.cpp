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
cout << myParser.parse(myLexer,input_text, rules) << endl;
return 0;
}