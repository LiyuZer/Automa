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
    // Use a stack to explore 
    stack<stackElem> stack;
    // Use a stack to store the instructions
    vector<Instruction> instruction_stack;
    stackElem stack_elem;
    stack_elem.value = expression_val;
    stack.push(stack_elem);
    while(stack.size() > 0){
        // Get the top node
        // If the stack elem is an instruction add it to the instruction set
        if(stack.top().is_instruction){
            instruction_set->instructions.push_back(stack.top().instruction);
            stack.pop();
            continue;
        }
        shared_ptr<AstNode> node = stack.top().value;
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
                else if(operation == "%"){
                    Instruction mod;
                    mod.type = InstructionType::MOD;
                    mod.reg1 = RegisterType::R1;
                    mod.reg2 = RegisterType::R2;
                    mod.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(mod);
                }
                else if(operation == "=="){
                    Instruction EQ;
                    EQ.type = InstructionType::EQ;
                    EQ.reg1 = RegisterType::R1;
                    EQ.reg2 = RegisterType::R2;
                    EQ.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(EQ);

                }
                else if (operation == "&&"){
                    Instruction AND;
                    AND.type = InstructionType::AND;
                    AND.reg1 = RegisterType::R1;
                    AND.reg2 = RegisterType::R2;
                    AND.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(AND);
                }
                else if(operation == "||"){
                    Instruction OR;
                    OR.type = InstructionType::OR;
                    OR.reg1 = RegisterType::R1;
                    OR.reg2 = RegisterType::R2;
                    OR.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(OR);
                }
                else if(operation == "!="){
                    Instruction NEQ;
                    NEQ.type = InstructionType::NEQ;
                    NEQ.reg1 = RegisterType::R1;
                    NEQ.reg2 = RegisterType::R2;
                    NEQ.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(NEQ);
                }
                else if(operation == ">"){
                    Instruction GT;
                    GT.type = InstructionType::GT;
                    GT.reg1 = RegisterType::R1;
                    GT.reg2 = RegisterType::R2;
                    GT.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(GT);
                }
                else if(operation == "<"){
                    Instruction LT;
                    LT.type = InstructionType::LT;
                    LT.reg1 = RegisterType::R1;
                    LT.reg2 = RegisterType::R2;
                    LT.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(LT);
                }
                else if(operation == "<="){
                    Instruction LE;
                    LE.type = InstructionType::LE;
                    LE.reg1 = RegisterType::R1;
                    LE.reg2 = RegisterType::R2;
                    LE.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(LE);
                }
                else if(operation == ">="){
                    Instruction GE;
                    GE.type = InstructionType::GE;
                    GE.reg1 = RegisterType::R1;
                    GE.reg2 = RegisterType::R2;
                    GE.reg3 = RegisterType::R3;
                    instruction_set->instructions.push_back(GE);
                }
            }
            else if(left_leaf || right_leaf){
            /* Now for the cases where 
            we have left or right_leaf available, but not both. We have to check which one is available
            as we have to obey the left associative property of the language.
            1. Check if the left node is a leaf node
                1. (LEFT NODE CASE) push STORE instruction the left val in the instruction stack 
                2. push the Operation Instruction to the stack 
                3. push the pop instruction to the stack
                4. push the right node to the stack for later evaluation 
            2. Check if the right node is the leaf node
                1. push the operation instruction to the stack 
                2. push LOAD instruction the right val in the instruction stack 
                3. push the left node into the evaluation stack 
            */
           if(left_leaf){
            // Left is the leaf node 
            // 1. (LEFT NODE CASE) push STORE instruction the left val in the instruction stack 
            // Store the value of the left node in the stack
            // check the type of the left node and load it to R3
            if(left_node->get_type() == "variable"){
                shared_ptr<variable> left_variable_node = dynamic_pointer_cast<variable>(left_node);
                string left_variable_name = left_variable_node->get_variableName();
                Instruction load;
                load.type = InstructionType::LOAD;
                load.variable_name = left_variable_name;
                load.reg1 = RegisterType::R3;
                instruction_set->instructions.push_back(load);
            }
            else if(left_node->get_type() == "integerLiteral"){
                shared_ptr<integerLiteral> left_integer_node = dynamic_pointer_cast<integerLiteral>(left_node);
                string left_integer_value = left_integer_node->get_integerLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R3;
                load.constant = Constant(stoi(left_integer_value));
                instruction_set->instructions.push_back(load);
            }
            else if(left_node->get_type() == "stringLiteral"){
                shared_ptr<stringLiteral> left_string_node = dynamic_pointer_cast<stringLiteral>(left_node);
                string left_string_value = left_string_node->get_stringLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R3;
                load.constant = Constant(left_string_value);
                instruction_set->instructions.push_back(load);
            }
            else if(left_node->get_type() == "boolLiteral"){
                shared_ptr<boolLiteral> left_bool_node = dynamic_pointer_cast<boolLiteral>(left_node);
                bool left_bool_value = left_bool_node->get_boolLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R3;
                load.constant = Constant(left_bool_value);
                instruction_set->instructions.push_back(load);
            }
            else if(left_node->get_type() == "charLiteral"){
                shared_ptr<charLiteral> left_char_node = dynamic_pointer_cast<charLiteral>(left_node);
                char left_char_value = left_char_node->get_charLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R3;
                load.constant = Constant(left_char_value);
                instruction_set->instructions.push_back(load);
            }
            else if(left_node->get_type() == "decimalLiteral"){
                shared_ptr<decimalLiteral> left_decimal_node = dynamic_pointer_cast<decimalLiteral>(left_node);
                string left_decimal_value = left_decimal_node->get_decimalLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R3;
                load.constant = Constant(stod(left_decimal_value));
                instruction_set->instructions.push_back(load);
            }
            //INC and STORE the value in the stack
            Instruction INC;
            INC.type = InstructionType::INC;
            INC.val = 1; // Increment the stack by 1
            instruction_set->instructions.push_back(INC);
            Instruction store;
            store.type = InstructionType::STORE;
            store.reg1 = RegisterType::R3; // Store the value in R3
            store.val = -1; // -1 denotes the final value, so we are storing the R1 at the end of the stack
            instruction_set->instructions.push_back(store);

            // 2. push the Operation Instruction to the stack
            Instruction operation;
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
            else if(operation_type == "&&"){
                operation.type = InstructionType::AND;
            }
            else if(operation_type == "||"){
                operation.type = InstructionType::OR;
            }
            else if(operation_type == "=="){
                operation.type = InstructionType::EQ;
            }
            else if(operation_type == "!="){
                operation.type = InstructionType::NEQ;
            }
            else if(operation_type == ">"){
                operation.type = InstructionType::GT;
            }
            else if(operation_type == "<"){
                operation.type = InstructionType::LT;
            }
            else if(operation_type == "<="){
                operation.type = InstructionType::LE;
            }
            else if(operation_type == ">="){
                operation.type = InstructionType::GE;
            }
            operation.reg1 = RegisterType::R1;
            operation.reg2 = RegisterType::R3;
            operation.reg3 = RegisterType::R3; // Store the result in R3
            // Now the trick is to push this on the stack not the instruction stack
            stackElem operation_elem;
            operation_elem.is_instruction = true;
            operation_elem.instruction = operation;
            stack.push(operation_elem);

            // 3. push the pop instruction to the stack
            Instruction pop;
            pop.type = InstructionType::POP;
            pop.reg1 = RegisterType::R1;
            stackElem pop_elem;
            pop_elem.is_instruction = true;
            pop_elem.instruction = pop;
            stack.push(pop_elem);

            // 4. push the right node to the stack for later evaluation
            stackElem right_node_elem;
            right_node_elem.value = right_node;
            stack.push(right_node_elem);

            // We are done
           }
           else{
            // Right is the leaf node
            // 1. push the operation instruction to the stack
            Instruction operation;
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
            else if(operation_type == "&&"){
                operation.type = InstructionType::AND;
            }
            else if(operation_type == "||"){
                operation.type = InstructionType::OR;
            }
            else if(operation_type == "=="){
                operation.type = InstructionType::EQ;
            }
            else if(operation_type == "!="){
                operation.type = InstructionType::NEQ;
            }
            else if(operation_type == ">"){
                operation.type = InstructionType::GT;
            }
            else if(operation_type == "<"){
                operation.type = InstructionType::LT;
            }
            else if(operation_type == "<="){
                operation.type = InstructionType::LE;
            }
            else if(operation_type == ">="){
                operation.type = InstructionType::GE;
            }
            operation.reg1 = RegisterType::R1;
            operation.reg2 = RegisterType::R3;
            operation.reg3 = RegisterType::R3; // Store the result in R3
            stackElem operation_elem;
            operation_elem.is_instruction = true;
            operation_elem.instruction = operation;
            stack.push(operation_elem);
            // 2. push LOAD instruction the right val in the instruction stack 
            // Load based on the type of the right node
            if(right_node->get_type() == "variable"){
                shared_ptr<variable> right_variable_node = dynamic_pointer_cast<variable>(right_node);
                string right_variable_name = right_variable_node->get_variableName();
                Instruction load;
                load.type = InstructionType::LOAD;
                load.variable_name = right_variable_name;
                load.reg1 = RegisterType::R1;
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            else if(right_node->get_type() == "integerLiteral"){
                shared_ptr<integerLiteral> right_integer_node = dynamic_pointer_cast<integerLiteral>(right_node);
                string right_integer_value = right_integer_node->get_integerLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R1;
                load.constant = Constant(stoi(right_integer_value));
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            else if(right_node->get_type() == "stringLiteral"){
                shared_ptr<stringLiteral> right_string_node = dynamic_pointer_cast<stringLiteral>(right_node);
                string right_string_value = right_string_node->get_stringLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R1;
                load.constant = Constant(right_string_value);
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            else if(right_node->get_type() == "boolLiteral"){
                shared_ptr<boolLiteral> right_bool_node = dynamic_pointer_cast<boolLiteral>(right_node);
                bool right_bool_value = right_bool_node->get_boolLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R1;
                load.constant = Constant(right_bool_value);
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            else if(right_node->get_type() == "charLiteral"){
                shared_ptr<charLiteral> right_char_node = dynamic_pointer_cast<charLiteral>(right_node);
                char right_char_value = right_char_node->get_charLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R1;
                load.constant = Constant(right_char_value);
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            else if(right_node->get_type() == "decimalLiteral"){
                shared_ptr<decimalLiteral> right_decimal_node = dynamic_pointer_cast<decimalLiteral>(right_node);
                string right_decimal_value = right_decimal_node->get_decimalLiteral();
                Instruction load;
                load.type = InstructionType::LOAD_CONST;
                load.reg1 = RegisterType::R1;
                load.constant = Constant(stod(right_decimal_value));
                stackElem load_elem;
                load_elem.is_instruction = true;
                load_elem.instruction = load;
                stack.push(load_elem);
            }
            // 3. push the left node into the evaluation stack
            // We have to push the left node to the stack
            stackElem left_node_elem;
            left_node_elem.value = left_node;
            stack.push(left_node_elem);

            }
    
            }
            else{
            /*
            This is a bit tricky we have to two leaf nodes that we have to push 
            to the stack and then we have to perform the operation. So we push intermediate 
            operations that are not ast nodes but instructions. Why? Because we cannot put the value of left leaf and 
            right leaf in R3, we need to put one in the stack, additionally we need to have an operation 

            Note that we are pushing to a stack so we be inserting in the reverse direction 
            
            This is the push order 
            1. Push the operation instruction(Operating R1 and R3 and storing the result in R3)
            2. Push the pop instruction(Popping the value from the stack to R1)
            3. Push the right_node
            4. Push the STORE INSTRUCTION(Storing the value of R3 to the stack)
            5. INC the stack
            6. Push the left_node

            This way we store the value of the left node in the stack and then we pop it to R1
            and then use the value of R1 and R3 to perform the operation and store the result in R3
            */
            //Push the operation instruction(Operating R1 and R3 and storing the result in R3)
            Instruction operation;
            string operation_type = binary_node->get_operation();
            if (operation_type == "+"){
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
            else if(operation_type == "&&"){
                operation.type = InstructionType::AND;
            }
            else if(operation_type == "||"){
                operation.type = InstructionType::OR;
            }
            else if(operation_type == "=="){
                operation.type = InstructionType::EQ;
            }
            else if(operation_type == "!="){
                operation.type = InstructionType::NEQ;
            }
            else if(operation_type == ">"){
                operation.type = InstructionType::GT;
            }
            else if(operation_type == "<"){
                operation.type = InstructionType::LT;
            }
            else if(operation_type == "<="){
                operation.type = InstructionType::LE;
            }
            else if(operation_type == ">="){
                operation.type = InstructionType::GE;
            }
            operation.reg1 = RegisterType::R1;
            operation.reg2 = RegisterType::R3;
            operation.reg3 = RegisterType::R3; // Store the result in R3
            stackElem operation_elem;
            operation_elem.is_instruction = true;
            operation_elem.instruction = operation;
            stack.push(operation_elem);

            //2. Push the pop instruction(Popping the value from the stack to R1)
            Instruction pop;
            pop.type = InstructionType::POP;
            pop.reg1 = RegisterType::R1;
            stackElem pop_elem;
            pop_elem.is_instruction = true;
            pop_elem.instruction = pop;
            stack.push(pop_elem);

            //3. Push the right_node
            stackElem right_node_elem;
            right_node_elem.value = right_node;
            stack.push(right_node_elem);


            //4 Push the STORE INSTRUCTION(Storing the value of R3 to the stack)  
            Instruction store;
            store.type = InstructionType::STORE;
            store.reg1 = RegisterType::R3; // Store the value in R3
            store.val = -1; // -1 denotes the final value, so we are storing the R1 at the end of the stack
            stackElem store_elem; 
            store_elem.is_instruction = true;
            store_elem.instruction = store;
            stack.push(store_elem);

            //5. INC the stack
            Instruction increment;
            increment.type = InstructionType::INC;
            increment.val = 1; // Increment the stack by 1
            stackElem increment_elem;
            increment_elem.is_instruction = true;
            increment_elem.instruction = increment;
            stack.push(increment_elem);

            //6. Push the left_node
            stackElem left_node_elem;
            left_node_elem.value = left_node;
            stack.push(left_node_elem);            


        }
            

        }else if(type == "unaryExpression"){
            // Get the unary expression
            shared_ptr<unaryExpression> unary_node = dynamic_pointer_cast<unaryExpression>(node);
            // Get the operand
            string operand = unary_node->get_operation();
            // Push the operand to the stack
            shared_ptr<AstNode> operand_node = unary_node->get_operand();
            stackElem operand_elem;
            operand_elem.value = operand_node;
            stack.push(operand_elem);
            // Now we define the operation 
            Instruction operation;
            // For not we only have the not operator 
            operation.type = InstructionType::NOT;
            operation.reg1 = RegisterType::R3;
            // Push the operation to the instruction stack 
            instruction_stack.push_back(operation);
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
            stackElem expression_elem;
            expression_elem.value = expression_node;
            stack.push(expression_elem);
            // Now we create a Store instruction that takes the value from R3 and stores it in the variable
            Instruction store;
            store.type = InstructionType::STORE_VAR;
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
            stackElem expression_elem;
            expression_elem.value = expression_node_ptr;
            stack.push(expression_elem);
        }
    }
    // Now we will go through the instruction stack and add the instructions to the instruction set but from last to first
    while (!instruction_stack.empty()) {
        // Get the last instruction
        Instruction* deferred = &instruction_stack.back();
        instruction_stack.pop_back();
    
        // Append each instruction from the deferred set to the main set
        instruction_set->instructions.push_back(*deferred);
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

        //If the node is a start node will will update the current index 
        if(graph_ptr->get_start_node() == node){
            instructionSet->instruction_start = instructionSet->instructions.size() - 1;
        }
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
            string next_node = transition.toNode;
            // Once the expression is decoded we add an instruction 
            // that checks jump to the next transition if the condition is false
            // where the result is stored in R3
            Instruction jmp_if;
            jmp_if.type = InstructionType::JMP_IF;
            jmp_if.reg1 = RegisterType::R3; // The result of the condition is in R3
            jmp_if.marker = node + "_transition_" + to_string(transition_count); // The next node is the marker 
            instructionSet->instructions.push_back(jmp_if);
            //Decode the operations 
            // Get the operation
            vector<shared_ptr<AstNode>> operations = transition.operations;
            //Decode the expression
            for(auto operation : operations){
                // Decode the expression
                decode_expression(operation, instructionSet);
            }
            // Now we have to add the jump instruction to the next node
            Instruction jmp;
            jmp.type = InstructionType::JMP;
            jmp.marker = next_node; // The next node is the marker
            instructionSet->instructions.push_back(jmp);
        }
        // If this is the accept node we will add a return instruction
        if(graph_ptr->is_accept_node(node)){
            // Before accepting we will decode accept nodes expression
            // Get the accept node
            shared_ptr<AstNode> accept_node = graph_ptr->get_accept();
            // Decode the expression
            decode_expression(accept_node, instructionSet);
            Instruction return_instr;
            return_instr.type = InstructionType::RETURN;
            instructionSet->instructions.push_back(return_instr);
        }
        else{
            // In this case we want to add a reject instruction
            // We will add a reject instruction at the end of the node
            Instruction reject;
            reject.type = InstructionType::REJECT;
            instructionSet->instructions.push_back(reject);
        }
    }    
    print_instructions(instructionSet);
    return instructionSet;
}

void VMCompiler::print_instructions(const shared_ptr<InstructionSet>& instructionSet) {
    cout << "=== Instruction Set ===" << endl;
    for (const auto& instr : instructionSet->instructions) {
        switch (instr.type) {
            case InstructionType::LOAD:
                cout << "LOAD R" << int(instr.reg1) + 1 << " " << instr.variable_name << endl;
                break;

            case InstructionType::LOAD_CONST:
                cout << "LOAD_CONST R" << int(instr.reg1) + 1 << " ";
                if (instr.constant.type == ConstantType::Integer) {
                    cout << std::get<int>(instr.constant.value);
                } else if (instr.constant.type == ConstantType::Float) {
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
                if (instr.val == -1) {
                    cout << "STORE STACK[SP - 1] R" << int(instr.reg1) + 1 << endl;
                } else {
                    cout << "STORE STACK[" << instr.val << "] R" << int(instr.reg1) + 1 << int(instr.reg3) + 1 << endl;
                }
                break;
            case InstructionType::STORE_VAR:
                cout << "STORE_VAR " << instr.variable_name << " R" << int(instr.reg1) + 1 << endl;
                break;
            case InstructionType::ADD:
                cout << "ADD R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::SUB:
                cout << "SUB R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::MUL:
                cout << "MUL R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::DIV:
                cout << "DIV R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::MOD:
                cout << "MOD R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::POP:
                cout << "POP R" << int(instr.reg1) + 1 << endl;
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
                cout << "JMP_IF R" << int(instr.reg1) + 1 << " -> " << instr.marker << endl;
                break;

            case InstructionType::JMP_NOT:
                cout << "JMP_NOT R" << int(instr.reg1) + 1 << " -> " << instr.marker << endl;
                break;

            case InstructionType::NOT:
                cout << "NOT R" << int(instr.reg1) + 1 << endl;
                break;

            case InstructionType::CMP:
                cout << "CMP R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;

            case InstructionType::EQ:
                cout << "EQ R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::NEQ:
                cout << "NEQ R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::GT:
                cout << "GT R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::LT:
                cout << "LT R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::LE:
                cout << "LE R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::GE:
                cout << "GE R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::AND:
                cout << "AND R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::OR:
                cout << "OR R" << int(instr.reg3) + 1 << " R" << int(instr.reg1) + 1 << " R" << int(instr.reg2) + 1 << endl;
                break;
            case InstructionType::REJECT:
                cout << "REJECT" << endl;
                break;



            default:
                cout << "UNKNOWN INSTRUCTION" << endl;
                break;
        }
    }
    cout << "=======================" << endl;
}
