#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "aut_obj.h"
#include "vm_compiler.h"
#include <queue>
#pragma once
/*

Here we define a path obj. 
A path at its simplest is equivalent to a process in a computer system.
It will be contain a snapshot of the current process. That is the registers and stack.
It will be run using a processor 

*/

using namespace std;


/*
Here we define the return value from the operator
*/

struct Register{
    RegisterType type;
    shared_ptr<AutomaObject> value; // Pointer to the automa object
    int index = -1; // This will be used if we are using STACK
    Register(RegisterType type, shared_ptr<AutomaObject> value){
        this->type = type;
        this->value = value;
    }
    Register(shared_ptr<AutomaObject> value){
        this->value = value;
    }
    Register(){
        this->value = nullptr;
    }
    RegisterType get_type(){
        return type;
    }
};
// Define the stack register 
struct stackRegister{
    vector<AstNode> stack; // This will be the stack
    int stack_pointer = 0; // This will be the stack pointer
    void push(AstNode node){
        stack.push_back(node);
        stack_pointer++;
    }
};
struct RegisterSet{
    // A full register set as defined in the instruction set
        Register R1;
        Register R2;
        Register R3;
        Register R4;
        Register R5;
        Register R6;
        Register R7;
        Register R8;
        Register R9;
        Register R10; // This is the program counter
        Register SP; // This is the stack pointer
        stackRegister STACK; // This is the stack
        RegisterSet(){
            R1.type = RegisterType::R1;
            R2.type = RegisterType::R2;
            R3.type = RegisterType::R3;
            R4.type = RegisterType::R4;
            R5.type = RegisterType::R5;
            R6.type = RegisterType::R6;
            R7.type = RegisterType::R7;
            R8.type = RegisterType::R8;
            R9.type = RegisterType::R9;
            R10.type = RegisterType::R10;
            SP.type = RegisterType::SP;
            SP.index = -1; // This will signify initial stack pointer
        }
};




class Path{
    private:
    int id;
    int max_time;
    int parent_path_id = -1; // -1 if no parent path
    shared_ptr<RegisterSet> register_set; // This will be the register set
    string graph_name; // This will be the graph name
    int program_counter = -1; // This will be the program counter
    public:
    Path(int id, string graph_name, int max_time=10000, int parent_path_id = -1){
        this->parent_path_id = parent_path_id;
        this->id = id;
        this->max_time = max_time;
        this->graph_name = graph_name;
    }

    int get_id(){
        return id;
    }

    int get_parent_path_id(){
        return parent_path_id;
    }
    void set_registerSet(shared_ptr<RegisterSet> register_set){
        this->register_set = register_set;
    }
    shared_ptr<RegisterSet> get_registerSet(){
        return register_set;
    }
    string get_graph_name(){
        return graph_name;
    }
    void set_graph_name(string graph_name){
        this->graph_name = graph_name;
    }
    int get_program_counter(){
        return program_counter;
    }


};