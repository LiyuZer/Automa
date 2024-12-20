#include <unordered_map>
#include <string>
#include <vector>
#include "../utilities.h"
#include "grammer_def.h"
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
        CreateParen('('),
        CreateToken("DOUBLE_COLON"),
        CreateRule("nodeTypes"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),

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
        CreateRule("varDefenition"), // Condition name
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("varDefenition"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple conditions
        CreateParen(')'),
        CreateSpecialSymbol('?'), 
    }},
    {"varDefenition", {
        CreateRule("variable"),
        CreateToken("COLON"),
        CreateRule("expression"),
    }},
    // expression : level1 | ( level1 )
    // level1 : binary_operations | assignment | level2
    // level2 : unary_operations |  variable | literal 
    // binary_operations : level2 binary_operators expression 
    // unary_operations : unary_operators
    // assignment : variable = expression
    // binary_operations : + * / % == && || or and <= >= < > == 
    // unary_operators : ! 
    // (((5 + 2)))
    //(5 * 2) * 2
    {"expression", {
        CreateToken("LEFT_PAREN"),
        CreateRule("expression"),
        CreateToken("RIGHT_PAREN"),
        CreateOr(),
        CreateRule("level1"),
 
    }},

    {"level1", {
        CreateRule("binary_operations"), 
        CreateOr(),
        CreateRule("assignment"), 
        CreateOr(),
        CreateRule("level2"), 
    }},

    {"level2", {
        CreateRule("unary_operations"), // Handles unary operations first
        CreateOr(),
        CreateRule("variable"), 
        CreateOr(),
        CreateRule("literal"), 
    }},
    {"assignment", {
        CreateRule("variable"), // Handles unary operations first
        CreateToken("ASSIGN"), 
        CreateRule("expression"), 
    }},
    {"unary_operations", {
        CreateToken("NOT"), 
        CreateRule("expression"),
    }},

    {"binary_operations", {
        CreateRule("level2"),
        CreateRule("binary_operators"), 
        CreateRule("expression"),
        CreateOr(),
        CreateToken("LEFT_PAREN"),
        CreateRule("expression"), 
        CreateToken("RIGHT_PAREN"),
        CreateRule("binary_operators"),
        CreateRule("expression"), 
    }},

    {"binary_operators", {
        CreateToken("PLUS"),
        CreateOr(),
        CreateToken("MINUS"),
        CreateOr(),
        CreateToken("STAR"),
        CreateOr(),
        CreateToken("DIV"),
        CreateOr(),
        CreateToken("MOD"),
        CreateOr(),
        CreateToken("AND"),
        CreateOr(),
        CreateToken("OR"),
        CreateOr(),
        CreateToken("EQUAL"),
        CreateOr(),
        CreateToken("NOT_EQUAL"),
        CreateOr(),
        CreateToken("LESS"),
        CreateOr(),
        CreateToken("LESS_EQUAL"),
        CreateOr(),
        CreateToken("GREATER"),
        CreateOr(),
        CreateToken("GREATER_EQUAL"),
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
    }},
    {"variable", {
        CreateToken("IDENTIFIER")
    }}


};
