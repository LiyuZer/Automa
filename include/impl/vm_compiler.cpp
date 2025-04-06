#include "../core/runtime.h"
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/graph.h"
#include "../core/vm_compiler.h"   
#include <stack>
#include <iostream>
using namespace std;
void VMCompiler :: decode_expression(shared_ptr<AstNode> expression_val, shared_ptr<InstructionSet>  instruction_set ){
    /*
        Here we will have to decode the expression and create the instruction. 

        For example binary operators we have:-
        a = (a + b) + (c * (e + f))
        the ast tree will look like 
                            +
                        /       \
                      +          *
                     / \        / \
                    a   b      c   +
                                  / \
                                 e   f
        We want this to be converted to a series of instructions increment the stack 
        
        We will load operate on a and  b load them on the stack 
        // 1. Compute (a + b)
        LOAD R1 a
        LOAD R2 b
        ADD  R3 R1 R2          // R3 = a + b
        STORE STACK[SP] R3     // push
        ADD SP SP 1

        // 2. Compute c
        LOAD R1 c
        STORE STACK[SP] R1     // push
        ADD SP SP 1

        // 3. Compute (e + f)
        LOAD R1 e
        LOAD R2 f
        ADD  R3 R1 R2          // R3 = e + f

        // 4. Compute c * (e + f)
        SUB SP SP 1            // pop c
        MUL  R3 STACK[SP] R3   // R3 = c * (e + f)

        // 5. Compute (a + b) + (c * (e + f))
        SUB SP SP 1            // pop (a + b)
        ADD  R3 STACK[SP] R3   // R3 = (a + b) + (c * (e + f))

        // 6. Store result in `a`
        STORE a R3

        The essential aspect of this is we find the left most leaf node and then if the right node is a leaf node we will
        compute the value and store it in the stack.
        If the right node is not a leaf node we store this value in the stack and then go to the right node
        and repeat the process until we reach a leaf node.
        We will then pop the stack and compute the value and store it in the left node
        This way we will be able to compute arbitrary expressions with minimal register usage, and more optimization 
        can be done later on.
    */
   cout<<"Decoding expression" << endl;
    // Use a stack to explore 
    stack<shared_ptr<AstNode>> stack;
    // Use a stack to store the instructions
    vector<shared_ptr<InstructionSet>> instruction_stack;
    stack.push(expression_val);
    while(stack.size() > 0){
        // Get the top node
        shared_ptr<AstNode> node = stack.top();
        stack.pop();
        // Check the type of the node
        string type = node->get_type();      
        if(type == "binaryExpression"){
            /* So there are three cases
             1. The left node is a leaf node and the right node is a leaf node
             2. The left node is a leaf node and the right node is not a leaf node
             3. The left node is not a leaf node and the right node is a leaf node
             2 and 3 are the same, we have a left associative system for now
             so we first explore the left node and then the right node
             If we find that both leaves are there we can just simply add the operator instruction 
             and store the result in R3 
             The trick is every time we execute an operation instruction we store the result to R3 
             */
            shared_ptr<binaryExpression> binary_node = dynamic_pointer_cast<binaryExpression>(node);
            // Get the left and right node
            shared_ptr<AstNode> left_node = binary_node->get_leftSide();
            shared_ptr<AstNode> right_node = binary_node->get_rightSide();
            // Check if the left node is a leaf node, ie it is a variable or a literal
            bool left_leaf = false;
            bool right_leaf = false;
            string left_type = left_node->get_type();
            string right_type = right_node->get_type();
            if(left_type == "variable" || left_type == "integerLiteral" || left_type == "stringLiteral" || left_type == "boolLiteral" || left_type == "charLiteral"){
                left_leaf = true;
            }
            if(right_type == "variable" || right_type == "integerLiteral" || right_type == "stringLiteral" || right_type == "boolLiteral" || right_type == "charLiteral"){
                right_leaf = true;
            }
            string operand = binary_node->get_operation();
            // If both are leaf nodes we can just compute the value and store it in R3        
            if(left_leaf && right_leaf){
                // Get the left and right value 
                string left_value = "";
                string right_value = "";
                array<shared_ptr<AstNode>, 2> values = {left_node, right_node};
                for (int i = 0; i < 2; i++){
                    shared_ptr<AstNode> value = values[i];
                    string value_type = value->get_type();
                    // Register 1 is the left value
                    // Register 2 is the right value
                    RegisterType reg;
                    if(i == 0){
                        reg = RegisterType::R1;
                    }else{
                        reg = RegisterType::R2;
                    }
                    if(value_type == "variable"){
                        shared_ptr<variable> value_ptr = dynamic_pointer_cast<variable>(value);
                        string value_name = value_ptr->get_variableName();
                        // We will LOAD the variable to R1
                        Instruction load;
                        load.type = InstructionType::LOAD;
                        load.variable_name = value_name;
                        load.reg1 = reg;
                        // We can add it directly to the instruction set
                        instruction_set->instructions.push_back(load);
                    }    
                    else if(value_type == "integerLiteral"){
                        shared_ptr<integerLiteral> value_ptr = dynamic_pointer_cast<integerLiteral>(value);
                        string value_integer = value_ptr->get_integerLiteral();
                        // We will LOAD_CONST the variable to R3
                        Instruction load;
                        load.type = InstructionType::LOAD_CONST;
                        load.reg1 = reg;
                        load.constant = Constant(stoi(value_integer));
                        instruction_set->instructions.push_back(load);
                    }
                    else if(value_type == "stringLiteral"){
                        shared_ptr<stringLiteral> value_ptr = dynamic_pointer_cast<stringLiteral>(value);
                        string value_string = value_ptr->get_stringLiteral();
                        // We will LOAD_CONST the variable to R3
                        Instruction load;
                        load.type = InstructionType::LOAD_CONST;
                        load.reg1 = reg;
                        load.constant = Constant(value_string);
                        instruction_set->instructions.push_back(load);
                    }
                    else if(value_type == "boolLiteral"){
                        shared_ptr<boolLiteral> value_ptr = dynamic_pointer_cast<boolLiteral>(value);
                        bool value_bool = value_ptr->get_boolLiteral();
                        // We will LOAD_CONST the variable to R3
                        Instruction load;
                        load.type = InstructionType::LOAD_CONST;
                        load.reg1 = reg;
                        load.constant = Constant(value_bool);
                        instruction_set->instructions.push_back(load);
                    }
                    else if(value_type == "charLiteral"){
                        shared_ptr<charLiteral> value_ptr = dynamic_pointer_cast<charLiteral>(value);
                        char value_char = value_ptr->get_charLiteral();
                        // We will LOAD_CONST the variable to R3
                        Instruction load;
                        load.type = InstructionType::LOAD_CONST;
                        load.reg1 = reg;
                        load.constant = Constant(value_char);
                        instruction_set->instructions.push_back(load);
                    }
                    else if(value_type == "decimalLiteral"){
                        shared_ptr<decimalLiteral> value_ptr = dynamic_pointer_cast<decimalLiteral>(value);
                        string value_decimal = value_ptr->get_decimalLiteral();
                        // We will LOAD_CONST the variable to R3
                        Instruction load;
                        load.type = InstructionType::LOAD_CONST;
                        load.reg1 = reg;
                        load.constant = Constant(stod(value_decimal));
                        instruction_set->instructions.push_back(load);
                    }
                }
                //Now we will compute the value and store it in R3
                string operation = binary_node->get_operation();
                if(operation == "+"){
                    Instruction add;
                    add.type = InstructionType::ADD;
                    add.reg1 = RegisterType::R1;
                    add.reg2 = RegisterType::R2;
                    add.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(add);
                }
                else if(operation == "-"){
                    Instruction sub;
                    sub.type = InstructionType::SUB;
                    sub.reg1 = RegisterType::R1;
                    sub.reg2 = RegisterType::R2;
                    sub.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(sub);
                }
                else if(operation == "*"){
                    Instruction mul;
                    mul.type = InstructionType::MUL;
                    mul.reg1 = RegisterType::R1;
                    mul.reg2 = RegisterType::R2;
                    mul.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(mul);
                }
                else if(operation == "/"){
                    Instruction div;
                    div.type = InstructionType::DIV;
                    div.reg1 = RegisterType::R1;
                    div.reg2 = RegisterType::R2;
                    div.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(div);
                } // For now only these operations are supported, but we will soon add more
            }
            else if(left_leaf || right_leaf){
            /* Now for the cases where 
            we have left or right_leaf available, we will treat them similarly essentially 
            we will add an instruction that increments the stack and pushes the value to the stack
            And to the (if you are a programmer working on this read this please)*** instruction stack***
            we will push an operation that take the value on the stack and the value on the R3 performs the operation 
            and stores the result in R3 then decrements the stack
            Only later will we add the elements of the instruction stack to the instruction set
            */
           shared_ptr<AstNode> leaf_node;
           shared_ptr<AstNode> non_leaf_node;
           if(left_leaf){
                leaf_node = left_node;
                non_leaf_node = right_node;
            }
            else if(right_leaf){
                leaf_node = right_node;
                non_leaf_node = left_node;
            }
            // Now time for action 
            // Load the leaf node to the stack
            string leaf_type = leaf_node->get_type();
            string non_leaf_type = non_leaf_node->get_type();

            // Increment the stack
            Instruction increment;
            increment.type = InstructionType::INC;
            increment.val = 1; // Increment the stack by 1
            instruction_set->instructions.push_back(increment);


            // We will store the leaf node in the stack
            // Now we wills store to the stack the lead node after we load it 
            // Load it to R1
            if(leaf_type == "variable"){
                Instruction load;
                load.type = InstructionType::LOAD;
                shared_ptr<variable> leaf_node_ptr = dynamic_pointer_cast<variable>(leaf_node);
                load.variable_name = leaf_node_ptr->get_variableName(); 
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            }
            else if(leaf_type == "integerLiteral"){
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                shared_ptr<integerLiteral> leaf_node_ptr = dynamic_pointer_cast<integerLiteral>(leaf_node);
                load.constant = Constant(stoi(leaf_node_ptr->get_integerLiteral()));
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            }
            else if(leaf_type == "stringLiteral"){
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                shared_ptr<stringLiteral> leaf_node_ptr = dynamic_pointer_cast<stringLiteral>(leaf_node);
                load.constant = Constant(leaf_node_ptr->get_stringLiteral());
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            }
            else if(leaf_type == "boolLiteral"){
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                shared_ptr<boolLiteral> leaf_node_ptr = dynamic_pointer_cast<boolLiteral>(leaf_node);
                load.constant = Constant(leaf_node_ptr->get_boolLiteral());
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            }
            else if(leaf_type == "charLiteral"){
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                shared_ptr<charLiteral> leaf_node_ptr = dynamic_pointer_cast<charLiteral>(leaf_node);
                load.constant = Constant(leaf_node_ptr->get_charLiteral());
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            }
            else if(leaf_type == "decimalLiteral"){
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                shared_ptr<decimalLiteral> leaf_node_ptr = dynamic_pointer_cast<decimalLiteral>(leaf_node);
                load.constant = Constant(stod(leaf_node_ptr->get_decimalLiteral()));
                load.reg1 = RegisterType::R1;
                instruction_set->instructions.push_back(load);
            } 
            // Now we will store the value in the stack
            Instruction store;
            store.type = InstructionType::STORE;
            store.reg1 = RegisterType::STACK;
            store.reg2 = RegisterType::SP;
            store.reg3 = RegisterType::R1; // Store the value in R1
            instruction_set->instructions.push_back(store);


            // We are now done! Man I wish that was the case, we still have to push the value to the instruction stack
            // That is the operation that takes in the value from the stack and the value from R3 and operates 

            Instruction operation;

            //Check the operation
            string operation_type = binary_node->get_operation();
            if(operation_type == "+"){
                operation.type = InstructionType::ADD;
            }
            else if(operation_type == "-"){
                operation.type = InstructionType::SUB;
            }
            else if(operation_type == "*"){
                operation.type = InstructionType::MUL;
            }
            else if(operation_type == "/"){
                operation.type = InstructionType::DIV;
            }
            else if(operation_type == "%"){
                operation.type = InstructionType::MOD;
            }
            // Now we will perform the operation
            operation.reg1 = RegisterType::R1;
            operation.reg2 = RegisterType::R3;
            operation.reg3 = RegisterType::R3; // Store the result in R3
            instruction_stack.push_back(instruction_set);
    
            // pop to R1
            Instruction pop;
            pop.type = InstructionType::POP;
            pop.reg1 = RegisterType::R1;
            instruction_stack.push_back(instruction_set);

            // Now push the other value to the stack
            stack.push(non_leaf_node);
        }
        else{
            // We have both nodes as non leaf nodes
            // We will push the left node to the stack
            stack.push(left_node);
            // Now we will push the right node to the stack
            stack.push(right_node);
        }
            

        }else if(type == "unaryExpression"){
            // Get the unary expression
            shared_ptr<unaryExpression> unary_node = dynamic_pointer_cast<unaryExpression>(node);
            // Get the operand
            string operand = unary_node->get_operation();
            // Push the operand to the stack
            shared_ptr<AstNode> operand_node = unary_node->get_operand();
            stack.push(operand_node);
            // Now we define the operation 
            Instruction operation;
            // For not we only have the not operator 
            operation.type = InstructionType::NOT;
            operation.reg1 = RegisterType::R3;
            // Push the operation to the instruction stack 
            instruction_stack.push_back(instruction_set);
            // That is it

        }else if(type == "variable"){
            // Simple as loading the variable to R3 
            shared_ptr<variable> variable_node = dynamic_pointer_cast<variable>(node);
            string variable_name = variable_node->get_variableName();
            // We will LOAD the variable to R3
            Instruction load;
            load.type = InstructionType::LOAD;
            load.variable_name = variable_name;
            load.reg1 = RegisterType::R3;
            // We can add it directly to the instruction set
            instruction_set->instructions.push_back(load);
        }else if(type == "integerLiteral"){
            // We will LOAD_CONST the variable to R3
            shared_ptr<integerLiteral> integer_node = dynamic_pointer_cast<integerLiteral>(node);
            string integer_value = integer_node->get_integerLiteral();
            Instruction load;
            load.type = InstructionType::LOAD_CONST;
            load.reg1 = RegisterType::R3;
            load.constant = Constant(stoi(integer_value));
            instruction_set->instructions.push_back(load);
        
        }else if(type == "decimalLiteral"){
            // We will LOAD_CONST the variable to R3
            shared_ptr<decimalLiteral> decimal_node = dynamic_pointer_cast<decimalLiteral>(node);
            string decimal_value = decimal_node->get_decimalLiteral();
            Instruction load;
            load.type = InstructionType::LOAD_CONST;
            load.reg1 = RegisterType::R3;
            load.constant = Constant(stod(decimal_value));
            instruction_set->instructions.push_back(load);
        }else if(type == "boolLiteral"){
            // We will LOAD_CONST the variable to R3
            shared_ptr<boolLiteral> bool_node = dynamic_pointer_cast<boolLiteral>(node);
            bool bool_value = bool_node->get_boolLiteral();
            Instruction load;
            load.type = InstructionType::LOAD_CONST;
            load.reg1 = RegisterType::R3;
            load.constant = Constant(bool_value);
            instruction_set->instructions.push_back(load);
        }else if(type == "charLiteral"){
            // We will LOAD_CONST the variable to R3
            shared_ptr<charLiteral> char_node = dynamic_pointer_cast<charLiteral>(node);
            char char_value = char_node->get_charLiteral();
            Instruction load;
            load.type = InstructionType::LOAD_CONST;
            load.reg1 = RegisterType::R3;
            load.constant = Constant(char_value);
            instruction_set->instructions.push_back(load);
        }else if(type == "stringLiteral"){
            // We will LOAD_CONST the variable to R3
            shared_ptr<stringLiteral> string_node = dynamic_pointer_cast<stringLiteral>(node);
            string string_value = string_node->get_stringLiteral();
            Instruction load;
            load.type = InstructionType::LOAD_CONST;
            load.reg1 = RegisterType::R3;
            load.constant = Constant(string_value);
            instruction_set->instructions.push_back(load);
        }else if(type == "assignmentExpression"){
            // Similar to unary expression, store the expression in the stack
            // Get the assignment expression
            shared_ptr<assignmentExpression> assignment_node = dynamic_pointer_cast<assignmentExpression>(node);
            // Get the variable name
            string variable_name = assignment_node->get_variableName();
            // Get the expression
            shared_ptr<AstNode> expression_node = assignment_node->get_expression();
            // Push the expression to the stack
            stack.push(expression_node);
            // Now we create a Store instruction that takes the value from R3 and stores it in the variable
            Instruction store;
            store.type = InstructionType::STORE;
            store.variable_name = variable_name;
            store.reg1 = RegisterType::R3;
            instruction_set->instructions.push_back(store);
            // We are done with the assignment expression
        }
        else if(type == "expression"){
            // Just push the expression to the stack
            shared_ptr<expression> expression_node = dynamic_pointer_cast<expression>(node);
            // Get the expression
            shared_ptr<AstNode> expression_node_ptr = expression_node->get_expression();
            // Push the expression to the stack
            stack.push(expression_node_ptr);
        }
    }
    // Now we will go through the instruction stack and add the instructions to the instruction set but from last to first
    while (!instruction_stack.empty()) {
        shared_ptr<InstructionSet> deferred = instruction_stack.back();
        instruction_stack.pop_back();
    
        // Append each instruction from the deferred set to the main set
        instruction_set->instructions.insert(
            instruction_set->instructions.end(),
            deferred->instructions.begin(),
            deferred->instructions.end()
        );
    }         
}
// Define the compile function  
shared_ptr<InstructionSet> VMCompiler :: compile(shared_ptr<Graph> graph_ptr){
    // We will go through each node and each transition in the node first and create markers 
    // for each node labelled by the node name
    // Then we will go through each transition and create a set of instructions for each transition
    // The arrangement will be as follows
    /*
    Node 1
    Transition 1
        LOAD R1 a 
        LOAD_CONST R2 b
        CMP R3 R1 R2
        JMP_IF R3, Node 2
        JMP_NOT R3, Transition 2
    Transition 2
        LOAD R1 a 
        LOAD_CONST R2 b
        CMP R3 R1 R2
        JMP_IF R3, Node 3
        JMP_NOT R3, Transition 3
    Node 2
    Transition 1
        LOAD R1 a 
        LOAD_CONST R2 b
        CMP R3 R1 R2
        JMP_IF R3, Node 4
        JMP_NOT R3, Transition 4
    ... and so on until the final transition of the accept node
    Node 3 // Accept node 
    Transition 1
        LOAD R1 a 
        LOAD_CONST R2 b
        CMP R3 R1 R2
        JMP_IF R3, Node 5
        JMP_NOT R3, Accept // Meaning we are on the accept node and no more transitions are available 
    
    Accept // This is a marker for the accept node
        LOAD R1 a // Random instructions
        LOAD_CONST R2 b
        ADD R3 R1 R2
        STORE R3 a // Store the result in a
        RETURN // Return the result(yield to the operator) The operator will take the value of R3
    */

    // Now get the nodes list 
    vector<string> nodes = graph_ptr->return_node_list();
    
    // Create the instruction set
    shared_ptr<InstructionSet> instructionSet = shared_ptr<InstructionSet>(new InstructionSet);

    // We will go through each node and fetch each instruction
    for(auto node : nodes){
        //Fetch the transitions for the node
        vector<transition> transitions = graph_ptr->get_transitions(node);

        // Add the marker for the node
        Instruction marker;
        marker.type = InstructionType::MARKER;
        marker.marker = node; 
        instructionSet->instructions.push_back(marker);
        instructionSet->markers[node] = instructionSet->instructions.size() - 1; // Add the marker to the map

        // Now we will go through each transition and create a set of instructions for each transition
        int transition_count = 0;
        for(auto transition : transitions){
            /*
                Now we will convert each condition and operation to an instruction
                Note these are just expressions the key difference is after a conditions 
                if it is true we will jump to the next node, if it is false we will jump to the next transition
                jumping to the next transition is equivalent to just moving the pc(we are just moving forward)
                Additionally at the end of each node section(after all transitions) we will have a reject instruction
                Why? Because if we have not jumped to any node then we are in a reject state, no condition was true
            */
           // Mark the transitions as node_transition_count
           Instruction marker;
           marker.type = InstructionType::MARKER;
           marker.marker = node + "_transition_" + to_string(transition_count);
           instructionSet->instructions.push_back(marker);
           instructionSet->markers[node + "_transition_" + to_string(transition_count)] = instructionSet->instructions.size() - 1; // Add the marker to the map
           transition_count++;
           // Now we decode the expression
           // Get the condition
           shared_ptr<AstNode> condition = transition.condition;
           //Decode the expression
           decode_expression(condition, instructionSet);
           // Print the instructions
           print_instructions(instructionSet);
        }
    }
    return nullptr;
}

void VMCompiler::print_instructions(const shared_ptr<InstructionSet>& instructionSet) {
    cout << "=== Instruction Set ===" << endl;
    for (const auto& instr : instructionSet->instructions) {
        switch (instr.type) {
            case InstructionType::LOAD:
                cout << "LOAD " << "R" << int(instr.reg1) << " " << instr.variable_name << endl;
                break;
            case InstructionType::LOAD_CONST:
                cout << "LOAD_CONST " << "R" << int(instr.reg1) << " ";
                if (instr.constant.type == ConstantType::Integer) {
                    // Look at the variant as an int
                    cout << std::get<int>(instr.constant.value);
                } else if (instr.constant.type == ConstantType::Float) {
                    // Look at the variant as a float
                    cout << std::get<double>(instr.constant.value);
                } else if (instr.constant.type == ConstantType::String) {
                    cout << "\"" << std::get<std::string>(instr.constant.value) << "\"";
                } else if (instr.constant.type == ConstantType::Bool) {
                    cout << (std::get<bool>(instr.constant.value) ? "true" : "false");
                } else if (instr.constant.type == ConstantType::Char) {
                    cout << "'" << std::get<char>(instr.constant.value) << "'";
                } 
                cout << endl;
                break;
            case InstructionType::STORE:
                if (instr.variable_name != "") {
                    cout << "STORE " << instr.variable_name << " R" << int(instr.reg1) << endl;
                } else {
                    cout << "STORE STACK[R" << int(instr.reg1) << "] R" << int(instr.reg2) << endl;
                }
                break;
            case InstructionType::ADD:
                cout << "ADD R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            case InstructionType::SUB:
                cout << "SUB R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            case InstructionType::MUL:
                cout << "MUL R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            case InstructionType::DIV:
                cout << "DIV R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            case InstructionType::MOD:
                cout << "MOD R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            case InstructionType::POP:
                cout << "POP R" << int(instr.reg1) << endl;
                break;
            case InstructionType::INC:
                cout << "INC SP " << instr.val << endl;
                break;
            case InstructionType::MARKER:
                cout << "-- MARKER " << instr.marker << " --" << endl;
                break;
            case InstructionType::RETURN:
                cout << "RETURN" << endl;
                break;
            case InstructionType::JMP:
                cout << "JMP " << instr.marker << endl;
                break;
            case InstructionType::JMP_IF:
                cout << "JMP_IF R" << int(instr.reg1) << " -> " << instr.marker << endl;
                break;
            case InstructionType::JMP_NOT:
                cout << "JMP_NOT R" << int(instr.reg1) << " -> " << instr.marker << endl;
                break;
            case InstructionType::NOT:
                cout << "NOT R" << int(instr.reg1) << endl;
                break;
            case InstructionType::CMP:
                cout << "CMP R" << int(instr.reg3) << " R" << int(instr.reg1) << " R" << int(instr.reg2) << endl;
                break;
            default:
                cout << "UNKNOWN INSTRUCTION" << endl;
                break;
        }
    }
    cout << "=======================" << endl;
}
