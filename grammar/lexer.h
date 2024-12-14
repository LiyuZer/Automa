#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include "utilities.h"
#include <memory>

#pragma once

using namespace std;
class Lexer{
    public :

   bool skip(char c){

    if(isspace(c) || c == '\n' || c == '\t' || c == '\r'){
        return true;
    }
    return false;
   }



    shared_ptr<Token> run(int& currentPos, string& input){
        while (currentPos < input.length() && skip(input[currentPos])) {
            currentPos++;
        }
        if (currentPos >= input.length()) {
            shared_ptr<Token> ptr(new Token("EOF", ""));
            return ptr;
        }

        size_t start = currentPos;

        // Check for identifiers and keywords
        if (std::isalpha(input[currentPos])) {
            while (currentPos < input.length() && std::isalnum(input[currentPos])) {
                currentPos++;
            }
            std::string value = input.substr(start, currentPos - start);

            if (keywords.find(value) != keywords.end()) {
                shared_ptr<Token> ptr(new Token(keywords[value], value));
                return ptr;
            } else {
                shared_ptr<Token> ptr(new Token("IDENTIFIER", value));
                return ptr;
            }
        }
        // Check for ints floats
        else if (std::isalnum(input[currentPos])) {
            while (currentPos < input.length() && std::isalnum(input[currentPos])) {
                currentPos++;
            }
            std::string value = input.substr(start, currentPos - start);
            shared_ptr<Token> ptr(new Token("IntegerLiteral", value));
            return ptr;
        }
        // Check for operators
        else {
            // As most of our operators are only two characters we can get up to two character 

            if(((currentPos + 1) < input.length()) && !skip(input[currentPos]) && !skip(input[currentPos + 1])){
                std::string value = input.substr(start, (currentPos + 2) - start);
                if (operators.find(value) != operators.end()) {
                    shared_ptr<Token> ptr(new Token(operators[value], value));
                    currentPos = currentPos + 2;
                    return ptr;
                } 
            }
            if(((currentPos) < input.length()) && !skip(input[currentPos])){
                std::string value = input.substr(start, (currentPos + 1) - start);
                if (operators.find(value) != operators.end()) {
                    shared_ptr<Token> ptr(new Token(operators[value], value));
                    currentPos = currentPos + 1;
                    return ptr;
                } 
            }


        }
        currentPos++;
        shared_ptr<Token> ptr(new Token("Ignore", ""));
        return ptr;

    }



};
