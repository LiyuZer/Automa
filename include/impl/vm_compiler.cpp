#include "../core/runtime.h"
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/graph.h"
#include "../core/vm_compiler.h"   
#include <iostream>

void VMCompiler :: decodeExpression(shared_ptr<AstNode> expression,shared_ptr<InstructionSet>  instruction_set ){
    /*
        Here we will have to decode the expression and create the instruction. 
        Note for binary operators left will be stored in R1 and right in R2 always
        example 
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


        


        
        
    */


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
        for(auto transition : transitions){
            /*
                Now we will convert each condition and operation to an instruction
                Note these are just expressions the key difference is after a conditions 
                if it is true we will jump to the next node, if it is false we will jump to the next transition
                jumping to the next transition is equivalent to just moving the pc(we are just moving forward)
                Additionally at the end of each node section(after all transitions) we will have a reject instruction
                Why? Because if we have not jumped to any node then we are in a reject state, no condition was true
            */
           
        }
    }
    return nullptr;
}