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
        {"afterReject", "AFTER_REJECT"},
        {"afterAccept", "AFTER_ACCEPT"},
        {"symbols", "SYMBOLS"},
        {"array", "ARRAY"},
        {"dict", "DICT"},
        {"tuple", "TUPLE"},
        {"conditions", "CONDITIONS"},
        {"operations", "OPERATIONS"},
        {"None", "NONE"},
        {"nodeDef", "NODE_DEF"},
        {"startNode", "START_NODE"},
        {"acceptNode", "ACCEPT_NODE"},
        {"rejectNode", "REJECT_NODE"},
        {"operator", "OPERATOR"},
        {"edgeDef" , "EDGE_DEF" }, 
        {"true" , "TRUE" },
        {"false" , "FALSE" }
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

