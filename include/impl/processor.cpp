#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#include "../core/vm_compiler.h"
#include "../core/processor.h"


using namespace std;

void Processor :: run(shared_ptr<Path> path){
    /*
    We will define the processor here, it will essentially loop through the linear 
    instruction set and compute each line, until a Return, Reject, Graph call is reached.
    */
   // set the register set pointer to the path
    register_set = path->get_registerSet();
    // If the program counter is -1, set it to the starting index in the instruction set
    if(path->get_program_counter() == -1){
        instruction_index = instruction_set->instruction_start;
    }
    else{
        instruction_index = path->get_program_counter();
    }
    // Now we will loop through the instruction set and execute each instruction
    for(auto instruction : instruction_set->instructions){
        // Each instruction can be executed as 
        // execute_instruction(instruction, register_set);
        
        
        // Get the current statement, then have a switch case for each enum type 
        // and execute the instruction
        unique_ptr<Instruction> instruction_ptr = make_unique<Instruction>(instruction);
        InstructionType type = instruction_ptr->type;

        switch (type){
            case InstructionType::LOAD:
                execute_load(instruction_ptr, register_set);
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
                execute_jmp_if(instruction_ptr, register_set);
                break;
            case InstructionType::JMP_NOT:
                execute_jmp_not(instruction_ptr, register_set);
                break;
            case InstructionType::JMP:
                execute_jmp(instruction_ptr, register_set);
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
                execute_inc(instruction_ptr, register_set);
                break;
            case InstructionType::POP:
                execute_pop(instruction_ptr, register_set);
                break;
            case InstructionType::STORE:
                execute_store(instruction_ptr, register_set);
                break;
            case InstructionType::STORE_VAR:    
                execute_store_var(instruction_ptr, register_set);
                break;
            case InstructionType::STORE_CONST:  
                execute_store_const(instruction_ptr, register_set);
                break;
            case InstructionType::MARKER:
                execute_marker(instruction_ptr, register_set);
                break;
            case InstructionType::REJECT:
                execute_reject(instruction_ptr, register_set);
                break;
            case InstructionType::RETURN:
                execute_return(instruction_ptr, register_set);
                break;
            default:
                cout << "Unknown instruction type" << endl;
                break;
        }
    }

    
}