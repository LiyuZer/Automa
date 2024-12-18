#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>

using namespace std;

#pragma once
class Symbol {
    private:
        bool is_terminating;
        bool is_special;
        bool is_or;
        bool is_paren;
    public:
        Symbol(bool is_terminating, bool is_special, bool is_or=false, bool is_paren=false)
            : is_terminating(is_terminating), is_special(is_special), is_or(is_or), is_paren(is_paren) {}

        virtual bool terminating(){
            return is_terminating;
        }
        virtual bool special(){
            return is_special;
        }
        virtual bool or_symbol(){
            return is_or;
        }
        virtual bool paren(){
            return is_paren;
        }
 
        virtual void print(){
            cout << "Symbol" << endl;
        }
};

class Token : public Symbol {
    public:
        string type;
        string value;
        Token(string type, string value)
            : Symbol(true, false), type(type), value(value){};
        Token(string type)
            : Symbol(true, false), type(type), value(" "){};
        virtual void print(){
            cout << "Token" << endl;
        }
};

class Rule : public Symbol {
    public:
        string next_rule;
        Rule(string next_rule)
            : Symbol(false, false), next_rule(next_rule){};
        virtual void print(){
            cout << "Rule" << endl;
        }
};

class SpecialSymbol : public Symbol {
    public:
        char type;
        SpecialSymbol(char type)
            : Symbol(false, true), type(type){};
        virtual void print(){
            cout << "Special Symbol" << endl;
        }
};

class OrSymbol : public Symbol {
public:
    OrSymbol() : Symbol(false, false, true, false) {}
    virtual void print() {
        cout << "Or Symbol" << endl;
    }
};

class ParenSymbol : public Symbol {
public:
    char parenType;
    ParenSymbol(char type) : Symbol(false, false, false, true), parenType(type) {}
    virtual void print() {
        cout << "Paren Symbol: " << parenType << endl;
    }
};


// OLD OrSymbol class removed here

using SymbolPtr = std::shared_ptr<Symbol>;

static SymbolPtr CreateToken(const std::string& name) {
    return std::make_shared<Token>(name);
}

static SymbolPtr CreateRule(const std::string& ruleName) {
    return std::make_shared<Rule>(ruleName);
}

static SymbolPtr CreateSpecialSymbol(char symbol) {
    return std::make_shared<SpecialSymbol>(symbol);
}

static SymbolPtr CreateParen(char symbol) {
    return std::make_shared<ParenSymbol>(symbol);
}

static SymbolPtr CreateOr() {
    return std::make_shared<OrSymbol>();
}

static int readFile(string filePath, string& input){
    ifstream file(filePath);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filePath << endl;
        return 1;
    }
    string line;
    while (getline(file, line)) {
        input = input + line;
    }
    file.close();
    return 0;
}

