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
        CreateRule("graphDec"),
        CreateSpecialSymbol('*'),
        CreateRule("mainGraph"), // Main graph as the entry point
        CreateRule("graphDec"),
        CreateSpecialSymbol('*'),

    }},
    {"graphDec", {
        CreateToken("GRAPH"), // Keyword "graph"
        CreateToken("IDENTIFIER"), // Graph name
        CreateToken("LEFT_BRACE"),
        CreateRule("graphDef"),
        CreateToken("RIGHT_BRACE") // Closing brace
    }},
    {"mainGraph", {
        CreateToken("GRAPH"), // Keyword "graph"
        CreateToken("MAIN"), // Graph name
        CreateToken("LEFT_BRACE"),
        CreateRule("graphDef"),
        CreateToken("RIGHT_BRACE") // Closing brace
    }},
    {"graphDef", {
        CreateParen('('),
        CreateRule("memoryDef"),
        CreateRule("nodeDef"),
        CreateRule("transitionDef"), // Include transitions
        CreateRule("afterAccept"), // Include transitions
        CreateRule("afterReject"), // Include transitions
        CreateParen(')'),
        CreateSpecialSymbol('?')
    }},
    {"memoryDef", {
        CreateToken("MEMORY"),
        CreateToken("LEFT_BRACE"),
        CreateRule("tupleItems"),
        CreateToken("RIGHT_BRACE"),
    }},
    {"nodeDef", {
        CreateToken("NODE_DEF"),
        CreateToken("LEFT_BRACE"),
        CreateParen('('),
        CreateRule("nodeDefStatement"),
        CreateToken("SEMICOLON"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateToken("RIGHT_BRACE"),
    }},
    {"nodeDefStatement", {
        CreateToken("IDENTIFIER"),
        CreateToken("DOUBLE_COLON"),
        CreateRule("nodeTypes"),
    }},
    {"nodeTypes", {
        CreateToken("START_NODE"),
        CreateOr(),
        CreateToken("ACCEPT_NODE"),
        CreateOr(),
        CreateToken("REJECT_NODE")
    }},
    {"transitionDef", {
        CreateToken("TRANSITIONS"), // Keyword "transitions"
        CreateToken("LEFT_BRACE"),
        CreateParen('('),
        CreateRule("transitionStatement"),
        CreateToken("SEMICOLON"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateToken("RIGHT_BRACE")
    }},
    {"transitionStatement", {
        CreateRule("fromNode"), 
        CreateToken("ARROW"), 
        CreateRule("toNode"), 
        CreateToken("ARROW_EQUALS"),
        CreateToken("CONDITIONS"),
        CreateToken("COLON"),
        CreateRule("conditions"),
        CreateToken("COMMA"),
        CreateToken("OPERATIONS"),
        CreateToken("COLON"),
        CreateRule("operations")
    }},
    {"fromNode", {
        CreateToken("IDENTIFIER"), 
    }},
    {"toNode", {
        CreateToken("IDENTIFIER"), 
    }},
    {"conditions", {
        CreateToken("LEFT_PAREN"),
        CreateRule("conditionStatement"),
        CreateToken("RIGHT_PAREN"),
    }},
    {"conditionStatement", {
        CreateParen('('),
        CreateRule("expression"), // Condition name
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("expression"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple conditions
        CreateParen(')'),
        CreateSpecialSymbol('?'), 
    }},
    {"operations", {
        CreateToken("LEFT_PAREN"),
        CreateRule("operationStatement"),
        CreateToken("RIGHT_PAREN"),
    }},
    {"operationStatement", {
        CreateParen('('),
        CreateRule("expression"), // Condition name
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("expression"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple conditions
        CreateParen(')'),
        CreateSpecialSymbol('?'), 
    }},
    {"afterAccept", {
        CreateToken("AFTER_ACCEPT"),
        CreateToken("LEFT_BRACE"), 
        CreateRule("expression"),
        CreateToken("SEMICOLON"), 
        CreateToken("RIGHT_BRACE"), 
    }},
    {"afterReject", {
        CreateToken("AFTER_REJECT"),
        CreateToken("LEFT_BRACE"), 
        CreateRule("expression"),
        CreateToken("SEMICOLON"), 
        CreateToken("RIGHT_BRACE"), 
    }},
    {"tupleItems", {
        CreateParen('('),
        CreateRule("keyValuePair"), // Condition name
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("keyValuePair"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple conditions
        CreateParen(')'),
        CreateSpecialSymbol('?'), 
    }},
    {"keyValuePair", {
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"),
        CreateRule("literal"),
    }},
    {"expression", {
        CreateParen('('),
        CreateRule("literal"),
        CreateOr(),
        CreateToken("IDENTIFIER"),
        CreateParen(')'), 
        CreateSpecialSymbol('+'),
    }},
    {"literal", {
        CreateToken("STRING_LITERAL"),
        CreateOr(),
        CreateToken("INTEGER_LITERAL"),
        CreateOr(),
        CreateRule("boolLiteral"),
        CreateOr(),
        CreateToken("CHAR_LITERAL"),
    }},
    {"boolLiteral", {
        CreateParen('('),
        CreateToken("TRUE"),
        CreateOr(),
        CreateToken("FALSE"),
        CreateParen(')'),
    }}


};
