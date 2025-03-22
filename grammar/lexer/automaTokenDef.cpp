#include <unordered_map>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include "automaTokenDef.h"

using namespace std;

std::unordered_map<std::string, std::string> keywords = {
        {"transitions", "TRANSITIONS"},
        {"memory", "MEMORY"},
        {"graph", "GRAPH"},
        {"accept", "ACCEPT"},
        {"symbols", "SYMBOLS"},
        {"array", "ARRAY"},
        {"dict", "DICT"},
        {"tuple", "TUPLE"},
        {"conditions", "CONDITIONS"},
        {"operations", "OPERATIONS"},
        {"None", "NONE"},
        {"nodes", "NODE_DEF"},
        {"ST", "START_NODE"},
        {"AC", "ACCEPT_NODE"},
        {"RJ", "REJECT_NODE"},
        {"operator", "OPERATOR"},
        {"edgeDef" , "EDGE_DEF" }, 
        {"true" , "TRUE" },
        {"false" , "FALSE" }, 
        {"return" , "RETURN" },
        {"def" , "DEFINITION" }
    };

std::unordered_map<std::string, std::string> operators = {
        {"->", "ARROW"},
        {"=>", "ARROW_EQUALS"},
        {"(", "LEFT_PAREN"},
        {")", "RIGHT_PAREN"},
        {"[", "LEFT_BRACKET"},
        {"]", "RIGHT_BRACKET"},
        {"{", "LEFT_BRACE"},
        {"}", "RIGHT_BRACE"},
        {"+", "PLUS"},
        {"-", "MINUS"},
        {"*", "STAR"},
        {"/", "DIV"},
        {"%", "MOD"},
        {"&&", "AND"},
        {"||", "OR"},
        {"~", "TILDE"},
        {"!", "NOT"},
        {"=", "ASSIGN"},
        {"<", "LESS"},
        {">", "GREATER"},
        {"==", "EQUAL"},
        {"!=", "NOT_EQUAL"},
        {"<=", "LESS_EQUAL"},
        {">=", "GREATER_EQUAL"},
        {";", "SEMICOLON"},
        {"::", "DOUBLE_COLON"},
        {":", "COLON"},
        {"\"", "QUOTES"},
        {"\'", "SINGLE_QUOTES"},
        {",", "COMMA"}, 
        {".", "DOT"}
    };

