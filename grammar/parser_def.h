#include <unordered_map>
#include <string>
#include <vector>
#include "utilities.h"

#pragma once

using namespace std;

/*
Sample grammer 

program : IDENTIFIER : [a]

*/

std::unordered_map<std::string, std::vector<SymbolPtr>> rules = {
    {"program", {
        CreateParen('('),
        CreateRule("tupleDef"), // The program starts with a tuple rule
        CreateOr(),
        CreateRule("listDef"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
    }},
    {"tupleDef", {
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"),
        CreateToken("LEFT_PAREN"), // Opening parenthesis for the tuple
        CreateParen('('),
        CreateToken("IDENTIFIER"), // First identifier
        CreateSpecialSymbol('*'),  // Optional repetition for additional identifiers with commas
        CreateParen('('),
        CreateToken("COMMA"),
        CreateToken("IDENTIFIER"), // First identifier
        CreateParen(')'),
        CreateSpecialSymbol('*'), 
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_PAREN") // Closing parenthesis for the tuple
    }},
    {"listDef", {
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"),
        CreateToken("LEFT_BRACKET"), // Opening parenthesis for the tuple
        CreateParen('('),
        CreateToken("IDENTIFIER"), // First identifier
        CreateSpecialSymbol('*'),  // Optional repetition for additional identifiers with commas
        CreateParen('('),
        CreateToken("COMMA"),
        CreateToken("IDENTIFIER"), // First identifier
        CreateParen(')'),
        CreateSpecialSymbol('*'), 
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_BRACKET") // Closing parenthesis for the tuple
    }}
};