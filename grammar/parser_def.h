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
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"), 
        CreateToken("LEFT_BRACKET"),
        CreateToken("IDENTIFIER"),
        CreateToken("RIGHT_BRACKET"),
        CreateSpecialSymbol('?'),
    }},

    };