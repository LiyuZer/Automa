#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../core/vm_compiler.h"
#include "../../grammar/ast/ast_node.h"
#include "../core/vm_compiler.h"
#include "../core/processor.h"
#include "../typesdef/num.h"
#include "../typesdef/bool.h"
#include "../typesdef/char.h"
#include "../typesdef/list.h"
#include "../typesdef/string.h"

using namespace std;

/*
execute_instruction definitions here
-------------------------------------------------
*/

void execute_load(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<Path> path){
    // Two cases one is loading from a variable to a register or loading from a register to a register
    // If the instruction is a load from a variable to a register we have an actual variable name
    if(instruction->variable_name == ""){
        // Load the variable to the register, note the registers are 0 indexed 
        register_set->registers.at((size_t)instruction->reg1).value = 
            register_set->registers.at((size_t)instruction->reg2).value;
    }
    else{
        // Load from a local variable to a register 
        shared_ptr<AutomaObject> value = path->get_local_variable(instruction->variable_name);
        register_set->registers.at((size_t)instruction->reg1).value = value;
    }
}

void execute_load_const(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Load the constant to the register, based on the type of the constant
    ConstantType type = instruction->constant.type;
    if(type == ConstantType::Integer){
        register_set->registers.at((size_t)instruction->reg1).value = 
            shared_ptr<Num>(new Num(std::get<int>(instruction->constant.value)));}
    else if(type == ConstantType::String){
        register_set->registers.at((size_t)instruction->reg1).value = 
            shared_ptr<String>(new String(std::get<string>(instruction->constant.value)));}
    else if(type == ConstantType::Char){
        register_set->registers.at((size_t)instruction->reg1).value = 
            shared_ptr<Char>(new Char(std::get<char>(instruction->constant.value)));}
    else if(type == ConstantType::Bool){
        register_set->registers.at((size_t)instruction->reg1).value = 
            shared_ptr<Bool>(new Bool(std::get<bool>(instruction->constant.value)));}
    else if(type == ConstantType::Float){
        register_set->registers.at((size_t)instruction->reg1).value = 
            shared_ptr<Num>(new Num(std::get<double>(instruction->constant.value)));}
}
void execute_add(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Add the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Num> result = shared_ptr<Num>(new Num(left->get_val() + right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_sub(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Subtract the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Num> result = shared_ptr<Num>(new Num(left->get_val() - right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_mul(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Multiply the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Num> result = shared_ptr<Num>(new Num(left->get_val() * right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_div(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Divide the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Num> result = shared_ptr<Num>(new Num(left->get_val() / right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_mod(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Mod the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    // TODO : Check for if both are ints 
    shared_ptr<Num> result = shared_ptr<Num>(new Num((int)left->get_val() % (int)right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_cmp(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Compare the two registers and store the result in the third register
    // This is wrong TODO : Fix this
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() == right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}

void execute_not(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Not the value of the register and store the result in the third register
    shared_ptr<Bool> left = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(!left->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_and(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // And the two registers and store the result in the third register
    shared_ptr<Bool> left = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Bool> right = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() && right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_or(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Or the two registers and store the result in the third register
    shared_ptr<Bool> left = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Bool> right = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() || right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_gt(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Greater than the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() > right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_lt(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Less than the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() < right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_ge(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Greater than or equal to the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() >= right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_le(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Less than or equal to the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() <= right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_eq(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Equal to the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() == right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_neq(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set){
    // Not equal to the two registers and store the result in the third register
    shared_ptr<Num> left = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg1).value);
    shared_ptr<Num> right = dynamic_pointer_cast<Num>(register_set->registers.at((size_t)instruction->reg2).value);
    shared_ptr<Bool> result = shared_ptr<Bool>(new Bool(left->get_val() != right->get_val()));
    register_set->registers.at((size_t)instruction->reg3).value = result;
}
void execute_inc(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<stackRegister> stack_register){
    // Increment the value of the stack register(add the value to the stack pointer and also add value nullptrs to the 
    // stack)
    // Get the stack pointer form register set, called SP and increment it by val
    register_set->SP.index = instruction->val + register_set->SP.index;
    // Now we will add the value to the stack
    for(int i = 0; i < instruction->val; i++){
        stack_register->stack.push_back(shared_ptr<AutomaObject>(nullptr));
    }


}
void execute_pop(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<stackRegister> stack_register){
    // Pop the value from the stack and store it in the register
    shared_ptr<AutomaObject> value = stack_register->stack.at(register_set->SP.index);
    // Store the value in the register
    register_set->registers.at((size_t)instruction->reg1).value = value;
    // Decrement the stack pointer
    register_set->SP.index = register_set->SP.index - 1;
}
void execute_store(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<stackRegister> stack_register){
    // a store instruction the formate is STORE <reg1> <val>
    // Get the value from the register
    shared_ptr<AutomaObject> value = register_set->registers.at((size_t)instruction->reg1).value;
    // Store the value in the stack, and the value of the store from the instruction
    // is stored in the val field of the instruction
    // If val is -1, then we will store the value in the stack pointer 

    if(instruction->val == -1){
        // Store the value in the stack pointer
        stack_register->stack.at(register_set->SP.index) = value;
    }
    else{
        // Store the value in the stack at the val index
        stack_register->stack.at(instruction->val) = value;
    }
}

void execute_store_var(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<Path> path){
    // This stores a registers value in a local variable, if the variable does not exist, create it
    // Get the value from the register
    shared_ptr<AutomaObject> value = register_set->registers.at((size_t)instruction->reg1).value;
    // Store the value in the local variable
    // Check if the variable exists in the local variables
    shared_ptr<AutomaObject> it = path->get_local_variable(instruction->variable_name);
    if(it == nullptr){
        // Create the variable
        path->set_local_variable(instruction->variable_name, value);
    }
    else{
        // Update the variable
        path->set_local_variable(instruction->variable_name, value);
    }
}
void execute_store_const(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<stackRegister> stack_register){
    // Store the value in the stack, and the value of the store from the instruction
    // is stored in the variable name field of the instruction
    // Get the value from the register
    shared_ptr<AutomaObject> value = register_set->registers.at((size_t)instruction->reg1).value;
    // Store the value in the stack, based on val field of the instruction
    stack_register->stack.at(instruction->val) = value;
}

// JMP_IF, JMP_NOT, JMP, these change the program counter 

void execute_jmp_if(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<InstructionSet> instruction_set, int& instruction_index){
    // Jump if the condition is true
    // Get the value of the register
    shared_ptr<Bool> condition = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg1).value);
    if(condition->get_val()){
        // Jump to the instruction index
        string marker = instruction->marker;
        // Get the instruction index from the instruction set
        auto it = instruction_set->markers.find(marker);
        if(it != instruction_set->markers.end()){
            // Set the instruction index to the marker index
            instruction_index = it->second;
        }
        else{
            cout<<"Marker " << marker << " not found" << endl;
        }
    }
}
void execute_jmp_not(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<InstructionSet> instruction_set, int& instruction_index){
    // Jump if the condition is false
    // Get the value of the register
    shared_ptr<Bool> condition = dynamic_pointer_cast<Bool>(register_set->registers.at((size_t)instruction->reg1).value);
    if(!condition->get_val()){
        // Jump to the instruction index
        string marker = instruction->marker;
        // Get the instruction index from the instruction set
        auto it = instruction_set->markers.find(marker);
        if(it != instruction_set->markers.end()){
            // Set the instruction index to the marker index
            instruction_index = it->second;
        }
        else{
            cout << "Marker " << marker << " not found" << endl;
        }
    }
}
void execute_jmp(unique_ptr<Instruction>& instruction, shared_ptr<RegisterSet> register_set, shared_ptr<InstructionSet> instruction_set, int& instruction_index){
    // Jump to the instruction index
    string marker = instruction->marker;
    // Get the instruction index from the instruction set
    auto it = instruction_set->markers.find(marker);
    if(it != instruction_set->markers.end()){
        // Set the instruction index to the marker index
        instruction_index = it->second;
    }
    else{
        cout << "Marker not found" << endl;
    }
}

/*
------------------------------------------------
*/


void Processor :: run(shared_ptr<Path> path){
    /*
    We will define the processor here, it will essentially loop through the linear 
    instruction set and compute each line, until a Return, Reject, Graph call is reached.
    */
   // set the register set pointer to the path
    register_set = path->get_registerSet();
    stack_register = path->get_stack_register();
    // If the program counter is -1, set it to the starting index in the instruction set
    if(path->get_program_counter() == -1){
        instruction_index = instruction_set->instruction_start;
    }
    else{
        instruction_index = path->get_program_counter();
    }
    cout<<"Program counter: " << instruction_index << endl;
    cout<<"Instruction set size: " << instruction_set->instructions.size() << endl;
    // Now we will loop through the instruction set and execute each instruction
    while(true){
        // Each instruction can be executed as 
        // execute_instruction(instruction, register_set);
        
        // Get the instruction
        if(instruction_index >= instruction_set->instructions.size()){
            cout << "End of instruction set" << endl;
            break;
        }

        Instruction instruction = instruction_set->instructions.at(instruction_index);
        // Get the current statement, then have a switch case for each enum type 
        // and execute the instruction
        unique_ptr<Instruction> instruction_ptr = make_unique<Instruction>(instruction);
        InstructionType type = instruction_ptr->type;
        
        switch (type){
            case InstructionType::LOAD:
                execute_load(instruction_ptr, register_set, path);
                break;
            case InstructionType::LOAD_CONST:
                execute_load_const(instruction_ptr, register_set);
                break;
            case InstructionType::ADD:
                execute_add(instruction_ptr, register_set);
                break;
            case InstructionType::SUB:
                execute_sub(instruction_ptr, register_set);
                break;
            case InstructionType::MUL:
                execute_mul(instruction_ptr, register_set);
                break;
            case InstructionType::DIV:
                execute_div(instruction_ptr, register_set);
                break;
            case InstructionType::MOD:
                execute_mod(instruction_ptr, register_set);
                break;
            case InstructionType::CMP:
                execute_cmp(instruction_ptr, register_set);
                break;
            case InstructionType::JMP_IF:
                execute_jmp_if(instruction_ptr, register_set, instruction_set, instruction_index);
                break;
            case InstructionType::JMP_NOT:
                execute_jmp_not(instruction_ptr, register_set, instruction_set, instruction_index);
                break;
            case InstructionType::JMP:
                execute_jmp(instruction_ptr, register_set, instruction_set, instruction_index);
                break;
            case InstructionType::NOT:
                execute_not(instruction_ptr, register_set);
                break;
            case InstructionType::AND:
                execute_and(instruction_ptr, register_set);
                break;
            case InstructionType::OR:
                execute_or(instruction_ptr, register_set);
                break;
            case InstructionType::GT:
                execute_gt(instruction_ptr, register_set);
                break;
            case InstructionType::LT:
                execute_lt(instruction_ptr, register_set);
                break;
            case InstructionType::GE:
                execute_ge(instruction_ptr, register_set);
                break;
            case InstructionType::LE:
                execute_le(instruction_ptr, register_set);
                break;
            case InstructionType::EQ:
                execute_eq(instruction_ptr, register_set);
                break;
            case InstructionType::NEQ:
                execute_neq(instruction_ptr, register_set);
                break;
            case InstructionType::INC:
                execute_inc(instruction_ptr, register_set, stack_register);
                break;
            case InstructionType::POP:
                execute_pop(instruction_ptr, register_set, stack_register);
                break;
            case InstructionType::STORE:
                execute_store(instruction_ptr, register_set, stack_register);
                break;
            case InstructionType::STORE_VAR:    
                execute_store_var(instruction_ptr, register_set, path);
                break;
            case InstructionType::STORE_CONST:  
                execute_store_const(instruction_ptr, register_set, stack_register);
                break;
            case InstructionType::MARKER:
                //SKIP
                break;
            case InstructionType::REJECT:
                // TODO : Implement the reject instruction, for now just exit
                cout << "Reject instruction" << endl;
                //Print the value of the variable a 
                cout<< "Value of x: " << path->get_local_variable("x")->repr() << endl;
                // Exit the function 
                return;
            case InstructionType::RETURN:
                // TODO : Implement the return instruction
                cout << "Return instruction" << endl;
                cout<< "Value of x: " << path->get_local_variable("x")->repr() << endl;
                return;
            default:
                cout << "Unknown instruction type" << endl;
                break;
        }
        // Increment the instruction index
        instruction_index++;
    }
    
}

void Processor:: print_instruction(const Instruction instr){
    /*
    print out the value of the instruction
    */
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
                cout << "STORE STACK[SP + " << instr.val << "] R" << int(instr.reg1) + 1 << endl;
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