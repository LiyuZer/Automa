/*
This is the processor file, we will be using this to process the paths
It will contain the processor and the stack
The processor will be used to process the paths and the stack will be used to store the values

Note the processor class contains a ptr to the path object, that is it.
*/

#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
// Now the internal header files 
#include "graph.h"
#include "aut_obj.h"
#include "vm_compiler.h"
#include "operator.h"
#include "path.h"
#include <queue>
#include <iostream>

#pragma once
class Processor{
    private:
        shared_ptr<AutomaObject> current_node;
        shared_ptr<AutomaObject> current_value;
        shared_ptr<InstructionSet> instruction_set;
        shared_ptr<RegisterSet> register_set;
        shared_ptr<stackRegister> stack_register;
        stack<stackElem> stack; // This is the stack that we will use to store the values
        int instruction_index = 0; // This is the index of the instruction that we are currently executing
        bool running = false; // This will be used to check if the processor is running or not
    public:
        Processor() :instruction_set(nullptr){};
        void run(shared_ptr<Path> path); // This will run the processor
        void set_instructionSet(shared_ptr<InstructionSet> instruction_set){
            this->instruction_set = instruction_set;
        }
        void get_instructionSet(shared_ptr<InstructionSet> instruction_set){
            this->instruction_set = instruction_set;
        }
        void get_registerSet(shared_ptr<RegisterSet> register_set){
            this->register_set = register_set;
        }
        void print_instruction(const Instruction instr); // This will print the instruction



};
