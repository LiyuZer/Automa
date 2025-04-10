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
        
    }

    
}