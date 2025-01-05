#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"


void Path :: set_memory(shared_ptr<AstNode> memory){
    // Loop through the memory defintions and set the memory container
    shared_ptr<memoryDef> memoryDef_ptr = dynamic_pointer_cast<memoryDef>(memory);
    vector<shared_ptr<AstNode> > variableDefinitions = memoryDef_ptr->get_variableDefinitions();
    for(auto var_def : variableDefinitions){
        shared_ptr var_def_ptr = dynamic_pointer_cast<variableDefintions>(var_def);
        string var_name = var_def_ptr->get_variableName();
        shared_ptr<AstNode> literal = var_def_ptr->get_literal();

        // Now we will go to the literal and set the memory container, first check the literal type
        if(dynamic_pointer_cast<stringLiteral>(literal)){
            shared_ptr<stringLiteral> stringLiteral_ptr = dynamic_pointer_cast<stringLiteral>(literal);
            
        }
        else if(dynamic_pointer_cast<integerLiteral>(literal)){
            shared_ptr<integerLiteral> integerLiteral_ptr = dynamic_pointer_cast<integerLiteral>(literal);
            // memory_ptr->set_integer(var_name, integerLiteral_ptr->get_integerLiteral());
        }
        else if(dynamic_pointer_cast<charLiteral>(literal)){
            shared_ptr<charLiteral> charLiteral_ptr = dynamic_pointer_cast<charLiteral>(literal);
            // memory_ptr->set_char(var_name, charLiteral_ptr->get_charLiteral());
        }




    }
}


void Path :: run(){

    // Here we will define the path logic, the path logic is the main logic for running graph objects
    if(current_time == 0){
        // Set the memory container
        memory_ptr = shared_ptr<Memory>(new Memory);
        // traverse the memory ast and set the memory container
        shared_ptr<AstNode> memory = graph_ptr->get_memory_def();
        set_memory(memory);

        // Set the memory log
        memory_log[0] = vector<string>();


        return;
    }
}