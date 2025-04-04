#include "../core/runtime.h"
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/graph.h"
#include "../core/vm_compiler.h"   
#include <iostream>

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
    for (auto node : nodes){
        cout<<"Node: " << node << endl;
    }
    return nullptr;
}