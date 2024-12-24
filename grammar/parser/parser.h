#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <memory>
#include "../grammarAutoma/grammer_def.h"
#include "../lexer/lexer.h"
#include <stack>
#include "parse_tree.h"
#pragma once
/*
Here we will create a parser class, why create a custom modular parser that can generate a wide array of 
grammar rules? The idea is to not constrain the language, everytime a feature is added I  
just have to update the grammar rule, not the actual parser, then make some adjustments to the AST creation 
that is it! Plus I thought it would be cool to create a custom greedy parser, with a slightly unconventional 
approach for parsing and lexing. 

If you want to check out Automa's grammar go to the grammar_def.cpp. There you will see it!
*/

/*
The idea is explore every uing rule the visit rule function, this takes in a a rule and then 
goes iteratively through rules until either two things happen:

    We see a rule, then when it does return a stack, this new stack will have the updated string with the new current pos 
    and then after the visit rule call we see that the stack pointer is not null, so we add this to the stack and continue the process 

    We see no more symbols, the rule is thus valid, we set the true flag, and return a nullptr. This means
    the rule has been validated. 

In some more complex cases if the parse function returns a null and bool, tand if the current rule has 
in fact a special symbol associated with it then the parse function will either :

    If bool is true a kleene star is the symbol and the value is true, do not pop, go on, but update the value of input_string and currentPos in the stack

    If bool is false and a kleene star is the symbol then do not update the top of the stack, just pop 

    Do similar logic for + and ? 
    
    
*/
using namespace std;
class Parser{
    public:

struct stack_location {
    bool is_dynamic;
    bool has_looped; // For kleene stars, if they have looped set this to true
    char special_rule;
    int current_index;
    int current_pos;
    int original_pos;
    string rule_str;
    string input;
    shared_ptr<ParseNode> node;
    shared_ptr<ParseNode> prev_node;
    // Constructor initializing members in the same order as their declaration
    stack_location(char sr, int ci, int cp, string& rs, string& inp, bool is_dynamic=false)
        : special_rule(sr), current_index(ci), current_pos(cp), rule_str(rs), input(inp), is_dynamic(is_dynamic), original_pos(cp), has_looped(false){
            node = shared_ptr<ParseNode>(new ParseNode(rs, "", is_dynamic));
            prev_node = shared_ptr<ParseNode>(new ParseNode(rs, "", is_dynamic));
        }
    void reset(){
        node = shared_ptr<ParseNode>(new ParseNode(rule_str, "", is_dynamic));
    }
};

    std::unordered_map<std::string, shared_ptr<stack_location>> dynamicRuleMap;


    // The generate rule function is generated by GPT4 Omni
    // Member variable to keep track of subrule numbering
    int subrule_counter;

    Parser() : subrule_counter(0) {}



    // Function to generate a new rule from a subsection of symbols within parentheses
    // Generates a unique rule name and adds the new rule to the rules map
    // Parameters:
    // - symbols: The list of symbols from the current rule
    // - current_index: The index where '(' was found; will be updated to after ')'
    // - rules: The map of all existing rules to which the new rule will be added
    // Returns:
    // - The unique name of the newly created subrule
    string generateRule(const vector<SymbolPtr>& symbols, int& current_index, 
                       unordered_map<string, vector<SymbolPtr>>& rules, string rule_str) {

        int start = current_index + 1; // Position after '('
        int end = start;
        int parenthesis_count = 1; // To handle nested parentheses

        // Iterate to find the matching ')'
        while (end < symbols.size() && parenthesis_count > 0) {

            if(symbols[end]->paren()){
                shared_ptr<ParenSymbol> paren_symbol = dynamic_pointer_cast<ParenSymbol>(symbols[end]);
                char type = paren_symbol->parenType;
                if (type == '(') {
                    parenthesis_count++;
                } else if (type == ')') {
                    parenthesis_count--;
                }
            }
            end++;
        }

        if (parenthesis_count != 0) {
            throw runtime_error("Unmatched parentheses in rule definition.");
        }

        string potential_match = rule_str + to_string(current_index);
        auto it = rules.find(potential_match); 
        if(it != rules.end()){
            current_index = end;
            return potential_match;
        }
        else{
        // Extract the subsection of symbols inside the parentheses
        vector<SymbolPtr> subsection(symbols.begin() + start, symbols.begin() + end - 1);

        // Add the new rule to the rules map
        rules[potential_match] = subsection;

        current_index = end;

        return potential_match;
        }
    }

    int search_or(const vector<SymbolPtr>& symbols, int current_index){
        /*
        This is the trickiest bit, when in the case a symbol is invalidated
        we search the rule until we see another rule, if we do we 
        then we go and look at that rule 
        The trick is we have to skip any rules in deeper parentheses so only see 'or' symbols 
        that are in the outside of our scope ie A B C (D| B) | L in this case the or before L would be used not (D|B) 
        */
        int start = current_index; // Position after '('
        int end = start;
        int parenthesis_count = 0; // To handle nested parentheses

        // Iterate to find the matching ')'
        while (end < symbols.size()) {
            if(symbols[end]->paren()){
                shared_ptr<ParenSymbol> paren_symbol = dynamic_pointer_cast<ParenSymbol>(symbols[end]);
                char type = paren_symbol->parenType;
                if (type == '(') {
                    parenthesis_count++;
                } else if (type == ')') {
                    parenthesis_count--;
                }
            }
            if(parenthesis_count == 0 && symbols[end]->or_symbol()){
                return end + 1;
            }
            end++;
        }

        return -1;

    }
    void addToNodeFromVec(shared_ptr<ParseNode> node, vector<shared_ptr<ParseNode>> parse_vec ){
        for(shared_ptr<ParseNode> i : parse_vec){
            node->addChildren(i->getType(), i);
        }
        return;
    }
    void addNodeFromStack(stack<shared_ptr<stack_location>> executionStack, shared_ptr<ParseNode> child_node ){
        if(!executionStack.empty()){
            executionStack.top()->node->addChildren(child_node->getType(), child_node);
        }
        return;
    }
    bool terminated(Lexer& x, vector<SymbolPtr>& v, int& i, int& current_pos, string& input, shared_ptr<ParseNode>& node, string ruleDebug=""){
        shared_ptr<Token> token_symbol = dynamic_pointer_cast<Token>(v[i]);

        int temp_current_pos = current_pos;// The temp current pos and temp_input are here to save the last valid current pos and input
        string temp_input = input;

        vector<shared_ptr<ParseNode>> vec; // Our vector storing all our nodes, as a token might have a * ? or + thus may be 
        //appear more than one time
        shared_ptr<Token> current_token = x.run(temp_current_pos, temp_input); // Get the current token from the lexer

        cout<<"******"<<endl;
        cout<<"Current symbol " << current_token->value<<endl;
        cout<<"Token "<<token_symbol->type<<endl;
        cout<<ruleDebug<<endl;
        cout<<"******"<<endl;
        if(current_token->type == "EOF"){
            return false;
        }
        if(i < (v.size() - 1) && v[i + 1]->special()){
            shared_ptr<SpecialSymbol> special_symbol = dynamic_pointer_cast<SpecialSymbol>(v[i + 1]);
            if(special_symbol->type == '*'){
                while (token_symbol->type == current_token->type){
                    current_pos = temp_current_pos;
                    input = temp_input;
                    vec.push_back(shared_ptr<ParseNode>(new ParseNode(current_token->type, current_token->value)));// Push before we increment lexer
                    current_token = x.run(temp_current_pos, temp_input);
                }
            }
            else if(special_symbol->type == '+'){
                if (token_symbol->type == current_token->type){// If the current symbol and current_token match 
                // Then update teh current pos and input
                    current_pos = temp_current_pos;
                    input = temp_input;
                    vec.push_back(shared_ptr<ParseNode>(new ParseNode(current_token->type, current_token->value)));// Push before we increment lexer
                } 
                else{
                    i = i + 2;
                    return false;
                }

                while (token_symbol->type == current_token->type){
                    current_pos = temp_current_pos;
                    input = temp_input;
                    vec.push_back(shared_ptr<ParseNode>(new ParseNode(current_token->type, current_token->value)));// Push before we increment lexer
                    current_token = x.run(temp_current_pos, temp_input);
                }
            }
            else if(special_symbol->type == '?'){
                if (token_symbol->type == current_token->type){
                    current_pos = temp_current_pos;
                    input = temp_input;
                    vec.push_back(shared_ptr<ParseNode>(new ParseNode(current_token->type, current_token->value)));// Push before we increment lexer
                } 
            }
            i = i + 2; // You have to skip the special operator
        }

        else{
            if(token_symbol->type != current_token->type){
                i = i + 1;
                return false;
            }
            else{
                current_pos = temp_current_pos;
                input = temp_input;
                vec.push_back(shared_ptr<ParseNode>(new ParseNode(current_token->type, current_token->value)));// Push before we increment lexer
            }
            
            i = i + 1;
        }    
        addToNodeFromVec(node, vec);// Adding the vector to the nodes children one by one
        return true;
    }



    shared_ptr<stack_location> visit_rule(Lexer& x, int& current_index, string current_rule, string& input_string, int& current_pos, bool& found, std::unordered_map<std::string, std::vector<SymbolPtr>>& rules, shared_ptr<ParseNode>& node){
        vector<SymbolPtr> v = rules[current_rule];// Our current rule
        while(current_index < v.size()){
            // If the current token is supposed to be terminating
            int i = current_index; // Makes it easier than writing current_index over again;
            if(v[i]->terminating()){
                found = terminated(x, v, current_index, current_pos, input_string, node, current_rule);
                if(!found){// Return false and a null ptr
                    found = false;
                    return shared_ptr<stack_location>(nullptr);
                }
            }
            else if(!(v[i]->terminating()) && !(v[i]->special()) &&!(v[i]->or_symbol()) && !(v[i]->paren())){ // This is a rule symbol
                shared_ptr<Rule> rule_symbol = dynamic_pointer_cast<Rule>(v[i]);
                if(i < (v.size() - 1) && v[i + 1]->special()){ // Special Symbol case
                    // We will return a stack shared object pointer, that will not be null.
                    // This way we can check later on and do as necessary
                    shared_ptr<SpecialSymbol> special_symbol = dynamic_pointer_cast<SpecialSymbol>(v[i + 1]); 
                    current_index = current_index + 2; // We are also skipping the next symbol as well
                    return shared_ptr<stack_location>(new stack_location(special_symbol->type, 0, current_pos, rule_symbol->next_rule, input_string));
                }
                else{
                    // Case where there is no symbol
                    current_index++; 
                    return shared_ptr<stack_location>(new stack_location(' ', 0, current_pos, rule_symbol->next_rule, input_string)); 
                }

            }
            else if(v[i]->paren()){
                /*
                How do we handle parentheses(I really can't spell that lol) you say? Well 
                we use dynamic on the fly rule creation. If a parentheses is created we call a function 
                generateRule(current_index, vector) this will loop through the rule and then add 1 for every 
                ( parent and -1 for every ) when a ) is detected such that the value becomes zero
                then we take the vector elements up to that index and return them, with the 
                current_index now updated to be past the extarcted chunk and added with a unique 
                string the the map. And 
                true.
                */
               string new_rule = generateRule(rules[current_rule], current_index, rules, current_rule);

               char special_symbol_char = ' ';
               // Now we need to check if the rule has a special symbol after
               // Not current index is already on the next token
               if(current_index < v.size() && v[current_index]->special()){ // Special Symbol case
                    shared_ptr<SpecialSymbol> special_symbol = dynamic_pointer_cast<SpecialSymbol>(v[current_index]); 
                    special_symbol_char = special_symbol->type;
                    current_index++;
               }
               return shared_ptr<stack_location>(new stack_location(special_symbol_char, 0, current_pos, new_rule, input_string, true)); 
            }
            else if(v[i]->or_symbol()){
                break;
            }
        }
        found = true;
        return nullptr;
    }

    bool parse(Lexer& x, string input, std::unordered_map<std::string, std::vector<SymbolPtr>>& rules, shared_ptr<ParseNode>& head){
        int current_pos = 0;
        std::stack<shared_ptr<stack_location>> executionStack; 
        string current_rule = "program";
        executionStack.push( shared_ptr<stack_location>(new stack_location(' ', 0, current_pos, current_rule, input)) ); 
        head = executionStack.top()->node;

        start:
        while(!executionStack.empty()){
          // We will define the variables for our visit here
          int& current_index = executionStack.top()->current_index;
          current_rule = executionStack.top()->rule_str; 
          input = executionStack.top()->input;  
          current_pos = executionStack.top()->current_pos;   
          bool found = false;
          // Visit the rule note curent index will never backtrace and so no need to create a copy
          shared_ptr<stack_location> current_output_ptr = visit_rule(x, current_index, current_rule, input, current_pos, found, rules, executionStack.top()->node);
          cout<<"Rule "<< current_rule<<" " << found <<endl;
          cout<< "index " << current_index<<endl;
          if (!current_output_ptr){
                if(found){ // Pop stack and update the top of the previous stack with the new string
                    if (executionStack.top()->special_rule == '*'){
                         //We have to rest the current index to go through the whole input
                        executionStack.top()->current_index = 0;
                        executionStack.top()->has_looped = true; // The kleene star has looped
                        executionStack.top()->original_pos = current_pos; // Now the original position is this pos
                        executionStack.top()->prev_node = executionStack.top()->node->copy();
    
                    }
                    else if (executionStack.top()->special_rule == '+'){
                        // We do the same as * the only difference is in the not found case 
                        // In that case we check if the top stacks pos is the same as the 
                        // The second topmost stack elem(thus no change) return false
                        executionStack.top()->current_index = 0;
                    }

                    else if (executionStack.top()->special_rule != '*'){ // If it is a kleene star then try again
                        shared_ptr<ParseNode> ptr = executionStack.top()->node;
                        executionStack.pop();
                        // If the execution stack is not empty then update the children of the top stack
                        addNodeFromStack(executionStack, ptr);
                    }

                    if(!executionStack.empty()){// Only do this if the stack is not empty
                        executionStack.top()->current_pos = current_pos;
                        executionStack.top()->input = input;
                    }
                }
                else if(executionStack.top()->special_rule != ' '){ // If the top has some special rule 
                    check_symbol:
                    // Do special logic with the current symbol 
                    if(executionStack.top()->special_rule == '*'){

                        vector<SymbolPtr> v = rules[executionStack.top()->rule_str];
                        int pos = search_or(v, executionStack.top()->current_index);
                        if(pos != -1){ // In the case where we have a * rule and found is false 
                        // Then check if there is an or, if so go and start from that index
                            executionStack.top()->current_index = pos; 
                            executionStack.top()->reset();
                            goto start;
                        }    

                        // We are creating a temp_pos and tempInput because 
                        // the * could have run multiple times, so we want to take the 
                        // last valid position                       
                        int temp_pos = executionStack.top()->original_pos;
                        string temp_input = executionStack.top()->input;
                        shared_ptr<ParseNode> ptr = executionStack.top()->prev_node; // Node to add to children
                        bool has_looped = executionStack.top()->has_looped;
                        executionStack.pop(); 
                        if(!executionStack.empty()){// Only do this if the stack is not empty
                            cout<< "Specific rule : "<< executionStack.top()->rule_str<<endl;
                            cout<<temp_pos<<endl;
                            cout<<executionStack.top()->current_pos<<endl;
                            cout<<input.substr(executionStack.top()->current_pos, 10)<<endl;
                            if(has_looped){// If the pos has not changed then ignore
                                addNodeFromStack(executionStack, ptr);// Added children here
                                executionStack.top()->current_pos = temp_pos; // Update the top of the stack, as there as been atleast one successful parsing
                                executionStack.top()->input = temp_input;
                            }
                        }
                    }
                    else if(executionStack.top()->special_rule == '+'){
                        vector<SymbolPtr> v = rules[executionStack.top()->rule_str];
                        int pos = search_or(v, executionStack.top()->current_index);
                        if(pos != -1){
                            executionStack.top()->current_index = pos; 
                            goto start;
                        }
                        
                        int old_current_pos = executionStack.top()->current_pos;
                        string old_input = executionStack.top()->input;
                        shared_ptr<ParseNode> ptr = executionStack.top()->node; // Node to add to children
                        executionStack.pop();
                        if(!executionStack.empty() && (old_current_pos == executionStack.top()->current_pos)){
                            while(!executionStack.empty()){
                                /* A detailed explanation of what the hell is happening here
                                While we are iteratively reducing the stack to see if there is some element 
                                with a special symbol(for extra computation say * for example) we also 
                                check to see if that stack member has an or rule, if it does 
                                then great! We move the current index there and start computing baby!
                                */
                                if(executionStack.top()->special_rule != ' '){
                                    found = false;
                                    goto check_symbol;
                                }
                                executionStack.pop();
                            }
                        }
                        if(!executionStack.empty() ){// If the execution stack is not empty
                            executionStack.top()->current_pos = old_current_pos;
                            executionStack.top()->input = old_input;
                            addNodeFromStack(executionStack, ptr);//Added children here
                        }
                        else{ 
                            return false; 
                        }
                    }
                    else if(executionStack.top()->special_rule == '?'){
                        vector<SymbolPtr> v = rules[executionStack.top()->rule_str];
                        int pos = search_or(v, executionStack.top()->current_index);
                        if(pos != -1){ // In the case where we have a * rule and found is false 
                        // Then check if there is an or, if so go and start from that index
                            executionStack.top()->current_index = pos; 
                            executionStack.top()->reset();
                            goto start;
                        }    
                        executionStack.pop();// Pop it, as you do not need this anymore
                    }  
 
                }
                else { 
                    // This case you should pop the stack until either you reach a special 
                    //Symbol or the stack is empty, if it is empty return false 
                    while(!executionStack.empty()){
                    /* 
                    A detailed repeated explanation of what the hell is happening here
                    While we are iteratively poping the stack to see if there is some element 
                    with a special symbol(for extra computation say * for example) we also 
                    check to see if that stack member has an or rule, if it does 
                    then great! We move the current index there and start computing baby!
                    */
                        found = false;
                        vector<SymbolPtr> v = rules[executionStack.top()->rule_str];
                        int pos = search_or(v, executionStack.top()->current_index);
                        if(pos != -1){
                            executionStack.top()->current_index = pos; 
                            executionStack.top()->current_pos = executionStack.top()->original_pos;
                            executionStack.top()->reset();
                            goto start;
                        }

                        if(executionStack.top()->special_rule != ' '){
                            goto check_symbol;
                        }
                        cout<<"Popping " << executionStack.top()->rule_str<<endl;

                        executionStack.pop();
                    }
                    return false;
                    }
            }
         else{
            // The return shared_ptr is not null so you add this to the stack and then evaluate the top
         // But before you need to make sure that teh current pos and string is the same
            executionStack.top()->current_pos = current_pos;
            executionStack.push(current_output_ptr);
            }
        }
    shared_ptr<Token> current_token = x.run(current_pos, input); // If the lexer has more tokens
    if(current_token->type != "EOF"){
            return false;
        }
    return true;
    };

};
