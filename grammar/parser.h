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
        char special_rule;
        int current_index;
        int current_pos;
        string rule_str;
        string input;
    };
    bool terminated(Lexer& x, vector<SymbolPtr>& v, int& i, shared_ptr<Token>& current_token, int& current_pos, string& input){
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
                    return false;
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
                return false;
            }
            current_token = x.run(current_pos, input); 
        }
    return true;

    }
    void parse(Lexer& x, string input){
        int current_pos = 0;
        shared_ptr<Token> current_token = x.run(current_pos, input);

        std::stack<stack_location> executionStack; 
        executionStack.push({0, "program", ' '}); 

        start:
        while(!executionStack.empty()){
            stack_location& current_top = executionStack.top();
            string current_rule = current_top.rule_str;
            vector<SymbolPtr> v = rules[current_rule];
            
            for(int i = current_top.current_index; i < v.size(); i++){
                if(v[i]->terminating()){// This is for a terminal symbol
                    bool found = terminated(x, v, i, current_token, current_pos, input);
                    if (!found && (current_top.special_rule == '*')){
                       executionStack.pop(); 
                       goto start;
                    }
                    else if (!found){
                        cerr << "Not found " << current_token->type << endl;
                        exit(0);
                    }
                }
                
                if(!(v[i]->terminating()) && !(v[i]->special()) &&!(v[i]->or_symbol()) && !(v[i]->paren())){ // Why don't you just have an is_rule method oh dear!
                /*
                    Here we have the rule method, it will take a rule and then put it on the stack for execution
                */
                    shared_ptr<Rule> rule_symbol = dynamic_pointer_cast<Rule>(v[i]);
                    current_top.current_index = i + 1;
                    if(i < (v.size() - 1) && v[i + 1]->special()){
                        shared_ptr<SpecialSymbol> special_symbol = dynamic_pointer_cast<SpecialSymbol>(v[i + 1]);
                        if(i + 1 >= v.size()){
                            executionStack.pop(); // Because we do not care for this rule anymore ie it would have been done 
                        }
                        executionStack.push({0, rule_symbol->next_rule, special_symbol->type});
                    }
                    else{
                        if(i + 1 >= v.size()){
                            executionStack.pop(); // Because we do not care for this rule anymore ie it would have been done 
                        }
                        executionStack.push({0, rule_symbol->next_rule, ' '});
 
                    }

                    goto start;
                }
            }
            if(!(current_top.special_rule == '*')){
                executionStack.pop();
            }
              
        }
        if(current_token->type != "EOF"){
            cerr << "Extra Code after this why?" << endl;
        }

    };

};

