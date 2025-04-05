/*
This is the file for the compiler, this will be the compiler for the automata, that we will use to compile 

Automa runs on VM processors that take in instructions that look very similar to assembly, but are not quite assembly,
they are more like a high level assembly, we will have a set of registers and instructions that we can use to
compile the automata into a set of instructions that we can run on the VM processor.


Now we will define the registers and instructions 

Registers names -:
    R1, R2, R3, R4, R5, R6, R7, R8, R9, R10
Register will pointers to Automa objects. 

Instruction types 
    LOAD REG1 MEM[A] // Load the value of the memory address A into register REG1
    LOAD_CONST REG1 CONST // Load the constant value CONST into register REG1
    CMP REG3 REG1 REG2 // Compare the values of register REG1 and REG2 and store the result in register REG3
    JMP_IF REG3, X // Jump the X if the value of register REG3 is true
    JMP_NOT REG3, X // Jump to  X if the value of register REG3 is false
    JMP X // Jump to X unconditionally
    ADD REG3 REG1, REG2 // Add the values of register REG1 and REG2 and store the result in register REG3
    SUB REG3 REG1, REG2 // Subtract the values of register REG2 from register REG1 and store the result in register REG3
    MUL REG3 REG1, REG2 // Multiply the values of register REG1 and REG2 and store the result in register REG3
    DIV REG3 REG1, REG2 // Divide the values of register REG1 by register REG2 and store the result in register REG3
    MOD REG3 REG1, REG2 // Modulo the values of register REG1 by register REG2 and store the result in register REG3

    STORE MEM[A], REG1 // Store the value of register REG1 into the memory address A
    STORE_CONST MEM[A], CONST // Store the constant value CONST into the memory address A
Note MEM just means an object that is a pointer to an Automa object, it could be a list or a dict or a string or whatever
Everything here is an object so the registers are just pointers to the Automa objects, the memory is just a pointer to the automa object
These are some of the basic instructions that we will have, we can add more instructions as we go along.


*/
#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "aut_obj.h"
#include <queue>

#pragma once
enum class InstructionType{
    LOAD, // Load from a variable
    LOAD_CONST, // Load a constant
    CMP, // Compare two registers
    JMP_IF,
    JMP_NOT,
    JMP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    STORE,//Store to a variable
    STORE_CONST, 
    MARKER,
    REJECT,
    RETURN
};
enum class RegisterType{
    R1,
    R2,
    R3,// We will make this the output register
    R4,
    R5,
    R6,
    R7,
    R8,
    R9,
    R10, 
    PC, // Program counter
    SP, // Stack location pointer
    STACK, // STACK  
};

struct Instruction{
    InstructionType type;
    RegisterType reg1;
    RegisterType reg2;
    RegisterType reg3;
    string mem_address; // Memory address(usually a variable name)
    string marker; // This is the marker might be empty
};
struct Register{
    RegisterType type;
    shared_ptr<AutomaObject> value; // Pointer to the automa object
    int index = -1; // This will be used if we are using STACK
    Register(RegisterType type, shared_ptr<AutomaObject> value){
        this->type = type;
        this->value = value;
    }
    RegisterType get_type(){
        return type;
    }
};

struct InstructionSet{
    // Will contain a vector of instructions and an unordered map, that maps the markers to the instruction index
    vector<Instruction> instructions;
    unordered_map<string, int> markers; // This will map the markers to the instruction index
};

// A VM compiler will take in a graph ptr and compile it into a set of instructions
// Simple as that
class VMCompiler{
    private:
    shared_ptr<Graph> graph_ptr; // This is the graph ptr
    int current_instruction = 0;
    public:
    shared_ptr<InstructionSet> compile(shared_ptr<Graph> graph_ptr); // This will compile the graph into a set of instructions
    void print_instructions(); // Prints out the instructions 
};