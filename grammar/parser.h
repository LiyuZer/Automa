#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "parser_def.h"
#include "lexer.h"
#include <stack>

/*
Here we will create a parser class
*/
using namespace std;
class Parser{
    public:
    struct stack_location{
        int current_index;
        string rule_str;
        char special_rule;
    };
    void parse(Lexer& x, string input){
        int current_pos = 0;
        shared_ptr<Token> current_token = x.run(current_pos, input);

        std::stack<stack_location> executionStack; 
        executionStack.push({0, "program", ' '}); 

        while(!executionStack.empty()){
            if(current_token->type == "EOF"){
                return;
            }
            stack_location& current_top = executionStack.top();
            string current_rule = current_top.rule_str;
            vector<SymbolPtr> v = rules[current_rule];

            for(int i = current_top.current_index; i < v.size(); i++){
                if(v[i]->terminating()){// This is for a terminal symbol
                    shared_ptr<Token> token_symbol = dynamic_pointer_cast<Token>(v[i]);
                    cout<<token_symbol->type<<endl;
                    if(i < (v.size() - 1) && v[i + 1]->special()){
                        shared_ptr<SpecialSymbol> special_symbol = dynamic_pointer_cast<SpecialSymbol>(v[i + 1]);
                        if(special_symbol->type == '*'){
                            while (token_symbol->type == current_token->type){
                                current_token = x.run(current_pos, input);
                            }
                        }
                        else if(special_symbol->type == '+'){
                            if (token_symbol->type == current_token->type){
                               current_token = x.run(current_pos, input);
                            } 
                            else{
                                cerr<< current_token->value << " not a " << token_symbol->type;
                            }
                          while (token_symbol->type == current_token->type){
                                current_token = x.run(current_pos, input);
                            }
                        }
                        else if(special_symbol->type == '?'){
                            if (token_symbol->type == current_token->type){
                               current_token = x.run(current_pos, input);
                            } 
                        }
                        i = i + 1;
                    }

                    else{
                        if(token_symbol->type != current_token->type){
                            cerr<< current_token->value << " not a " << token_symbol->type;
                            return;
                        }
                        current_token = x.run(current_pos, input); 
                    }
                }
            }
            executionStack.pop();  
        }
        if(current_token->type != "EOF"){
            cout<< "Extra Code after this why?" << endl;
        }

    };

};

