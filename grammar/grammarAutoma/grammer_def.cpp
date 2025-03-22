#include <unordered_map>
#include <string>
#include <vector>
#include "../utilities.h"
#include "grammer_def.h"
using namespace std;

/*
Sample grammer 
program : IDENTIFIER : [a]

How would one design a parser language 
One file for the grammer another file for the lexer 
*/

std::unordered_map<std::string, std::vector<SymbolPtr> > rules = {
    {"program", {
        CreateRule("graphDec"),
        CreateSpecialSymbol('*')
    }},
    {"graphDec", {
        CreateToken("DEFINITION"), // Keyword "graph"
        CreateToken("IDENTIFIER"), // Graph name
        CreateRule("parameterDef"), // Memory definition
        CreateToken("COLON"),
        CreateRule("graphDef"),
    }},
    {"graphDef", {
        CreateRule("nodeDef"),
        CreateSpecialSymbol('?'),
        CreateRule("transitionDef"), 
        CreateSpecialSymbol('?'),
        CreateRule("accept"), 
        CreateSpecialSymbol('?'),
    }},
    {"parameterDef", {
        CreateToken("LEFT_PAREN"),
        CreateRule("parameterItem"),
        CreateToken("RIGHT_PAREN"),
    }},
    {"nodeDef", {
        CreateToken("NODE_DEF"),
        CreateToken("COLON"),
        CreateParen('('),
        CreateRule("nodeDefStatement"),
        CreateToken("SEMICOLON"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
    }},
    {"nodeDefStatement", {
        CreateToken("IDENTIFIER"),
        CreateParen('('),
        CreateToken("DOUBLE_COLON"),
        CreateRule("nodeTypes"),
        CreateParen(')'),
        CreateSpecialSymbol('?'),

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
        CreateToken("COLON"),
        CreateParen('('),
        CreateRule("transitionStatement"),
        CreateToken("SEMICOLON"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
    }},
    {"transitionStatement", {
        CreateRule("fromNode"), 
        CreateToken("ARROW"), 
        CreateRule("toNode"), 
        CreateToken("ARROW_EQUALS"),
        CreateRule("conditions"),
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
        CreateRule("conditionStatement"),
    }},
    {"conditionStatement", {
        CreateParen('('),
        CreateRule("expression"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('?'), // Allow multiple conditions
    }},
    {"operations", {
        CreateRule("operationStatement"),
    }},
    {"operationStatement", {
        CreateParen('('),
        CreateRule("expression"), // Condition name
        CreateParen('('),
        CreateToken("SEMICOLON"),
        CreateRule("expression"), // Condition name 
        CreateParen(')'),
        CreateSpecialSymbol('*'), // Allow multiple conditions
        CreateParen(')'),
        CreateSpecialSymbol('?'), 
    }},
    /*
    accept{
        return expression
    }
    */
    {"accept", {
        CreateToken("ACCEPT"),
        CreateToken("COLON"),
        CreateToken("RETURN"),
        CreateRule("expression"),
        CreateToken("SEMICOLON"), 
        
    }},
    {"parameterItem", {
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
    {"keyValue", {
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"),
        CreateRule("expression"),
    }},
    {"varDefenition", {
        CreateToken("IDENTIFIER"),
        CreateToken("COLON"),
        CreateRule("expression"),
    }},

    {"expression", {
        CreateRule("assignment"),
        CreateOr(),
        CreateRule("prec3"),
    }},

    {"prec0", {
        CreateRule("unary_operators"),
        CreateSpecialSymbol('?'),
        CreateRule("term"),
        
    }},

    {"prec1", {
        CreateRule("term"),
        CreateParen('('),
        CreateRule("bin1"),
        CreateParen('('),
        CreateRule("term"),
        CreateRule("bin1"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateRule("prec1"),
        CreateParen(')'),
        CreateOr(),
        CreateRule("prec0"),
        CreateParen('('),
        CreateRule("bin1"),
        CreateRule("prec1"),
        CreateParen(')'),
        CreateSpecialSymbol('?')
    
    }},
    {"prec2", {
        CreateRule("term"),
        CreateParen('('),
        CreateRule("bin2"),
        CreateParen('('),
        CreateRule("term"),
        CreateRule("bin2"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateRule("prec2"),
        CreateParen(')'),
        CreateOr(),
        CreateRule("prec1"),
        CreateParen('('),
        CreateRule("bin2"),
        CreateRule("prec2"),
        CreateParen(')'),
        CreateSpecialSymbol('?')
    }},
    {"prec3", {
        CreateRule("term"),
        CreateParen('('),
        CreateRule("bin3"),
        CreateParen('('),
        CreateRule("term"),
        CreateRule("bin3"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateRule("prec3"),
        CreateParen(')'),
        CreateOr(),
        CreateRule("prec2"),
        CreateParen('('),
        CreateRule("bin3"),
        CreateRule("prec3"),
        CreateParen(')'),
        CreateSpecialSymbol('?')



    }},
    {"binary_operators", {
        CreateRule("firstPrec"),
        CreateOr(),
        CreateRule("secondPrec"),
        CreateOr(),
        CreateRule("thirdPrec"),
    }},
    {"unaryfactor", {
        CreateRule("unary_operators"),
        CreateRule("expression"),
    }},
    {"term", {
        CreateRule("graphCall"),
        CreateOr(),
        CreateRule("memoryContainer"),
        CreateOr(),
        CreateRule("listAccess"), // The reason why list access is here is because list access has a variable,and as the parser is greedy it will always try to match the first rule
        CreateOr(),
        CreateRule("listSlice"), // The reason why list access is here is because list access has a variable,and as the parser is greedy it will always try to match the first rule
        CreateOr(),
        CreateRule("variable"), 
        CreateOr(),
        CreateRule("literal"), 
        CreateOr(),
        CreateRule("list"), 
        CreateOr(),
        CreateToken("LEFT_PAREN"),
        CreateRule("expression"),
        CreateToken("RIGHT_PAREN"),

    }},

    {"firstClass", { // We might not need this after all
        CreateRule("listAccess"), // The difference between this and the term rule is that there is no expression here, these are all the first class citizens
        CreateOr(),
        CreateRule("listSlice"), 
        CreateOr(),
        CreateRule("variable"), 
        CreateOr(),
        CreateRule("literal"), 
        CreateOr(),
        CreateRule("list"), 
    }},


    { "list" , { 
        CreateToken("LEFT_BRACKET"), 
        CreateParen('('),
        CreateRule("expression"), 
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("expression"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_BRACKET")

    }},
    { "memoryContainer" , {  // Our defined memory container class this is 
        CreateToken("LEFT_BRACE"),
        CreateParen('('),
        CreateRule("keyValue"),
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("keyValue"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_BRACE")
    }},
    {"listAccess", {
        CreateRule("variable"), 
        CreateToken("LEFT_BRACKET"), 
        CreateToken("INTEGER_LITERAL"),
        CreateToken("RIGHT_BRACKET"), 
    }},
    {"listSlice", {
        CreateRule("variable"), 
        CreateToken("LEFT_BRACKET"), 
        CreateToken("INTEGER_LITERAL"),
        CreateToken("COLON"),
        CreateToken("INTEGER_LITERAL"),
        CreateToken("RIGHT_BRACKET"), 
    }},

    {"assignment", {
        CreateRule("variable"), 
        CreateToken("ASSIGN"), 
        CreateRule("expression"), 
    }},
    {"unary_operators", {
        CreateToken("NOT"), 
    }},
    {"bin1", {
        CreateToken("STAR"),
        CreateOr(),
        CreateToken("DIV"),
        CreateOr(),
        CreateToken("MOD"),
    }},
    {"bin2", {
        CreateToken("PLUS"),
        CreateOr(),
        CreateToken("MINUS"),
     }},
    {"bin3", {
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

    // Defining a graph call here
    {"graphCall", {
        CreateToken("IDENTIFIER"),
        CreateToken("LEFT_PAREN"),
        CreateParen('('),
        CreateRule("expression"),
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("expression"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_PAREN"),
        }
    },

    {"literal", {
        CreateToken("STRING_LITERAL"),
        CreateOr(),
        CreateRule("decimalLiteral"),
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
    {"decimalLiteral", {
        CreateRule("integerPart"),
        CreateToken("DOT"),
        CreateRule("decimalPart"),
    }},
    {"integerPart", {
        CreateToken("INTEGER_LITERAL"),
    }},
    {"decimalPart", {
        CreateToken("INTEGER_LITERAL"),
    }},
    {"variable", {
        CreateToken("IDENTIFIER")
    }}


};
