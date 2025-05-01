/*
We will have all the test functions here
*/
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <stdexcept>
#include "test.h"
#include "../grammar/lexer/lexer.h"

// Create the test Handler class
// This will be used to run all the tests
// First ever test will be for the lexer

TestHandler testHandler;

bool emptyFileTestLexer(string filename) {
    Lexer x;
    std::string input = ""; // We don't need a file for this test
}
