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
    vector<shared_ptr<AutomaObject> > stack; // This will be the stack
    int stack_pointer = 0; // This will be the stack pointer
};
struct RegisterSet{
    // A full register set as defined in the instruction set
        vector<Register> registers; // This will be the register set
        stackRegister STACK; // This is the stack
        Register SP;
        RegisterSet(){
            // Initialize the register set
            registers.push_back(Register(RegisterType::R1, nullptr));
            registers.push_back(Register(RegisterType::R2, nullptr));
            registers.push_back(Register(RegisterType::R3, nullptr));
            registers.push_back(Register(RegisterType::R4, nullptr));
            registers.push_back(Register(RegisterType::R5, nullptr));
            registers.push_back(Register(RegisterType::R6, nullptr));
            registers.push_back(Register(RegisterType::R7, nullptr));
            registers.push_back(Register(RegisterType::R8, nullptr));
            registers.push_back(Register(RegisterType::R9, nullptr));
            registers.push_back(Register(RegisterType::R10, nullptr));
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
    shared_ptr<stackRegister> stack_register; // This will be the stack register
    string graph_name; // This will be the graph name
    int program_counter = -1; // This will be the program counter
    unordered_map<string, shared_ptr<AutomaObject> > local_variables; // This will be the local variables
    public:
    Path(int id, string graph_name, int max_time=10000, int parent_path_id = -1){
        this->parent_path_id = parent_path_id;
        this->id = id;
        this->max_time = max_time;
        this->graph_name = graph_name;
        this->register_set = shared_ptr<RegisterSet>(new RegisterSet);
        this->stack_register = shared_ptr<stackRegister>(new stackRegister);
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
    void set_program_counter(int program_counter){
        this->program_counter = program_counter;
    }
    void set_local_variable(string name, shared_ptr<AutomaObject> value){
        local_variables[name] = value;
    }
    // Get the local variable from the path
    shared_ptr<AutomaObject> get_local_variable(string name){
        if(local_variables.find(name) != local_variables.end()){
            return local_variables[name];
        }
        return nullptr;
    }
    shared_ptr<stackRegister> get_stack_register(){
        return stack_register;
    }


};