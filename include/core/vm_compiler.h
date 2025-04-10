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
#include <variant>

#pragma once
enum class InstructionType{
    LOAD, // Load from a variable to a register
    LOAD_CONST, // Load a constant
    CMP, // Compare two registers
    GT, // Greater than
    LT, // Less than
    GE, // Greater than or equal to
    LE, // Less than or equal to
    EQ, // Equal to
    NEQ, // Not equal to
    JMP_IF,
    JMP_NOT,
    JMP,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NOT, // Not operation
    AND, // And operation
    OR, // Or operation
    INC, // Increment
    POP, // Pop from the stack
    STORE,//Store to STACK
    STORE_VAR, // Store to a variable
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
    NULL_REG,//Denotes empty
};
enum class ConstantType {
    Integer,
    String,
    Char,
    Bool,
    Float
};

struct Constant {
    ConstantType type;
    std::variant<int, std::string, char, bool, double> value;
    Constant() : type(ConstantType::Integer), value(0) {} // Default constructor
    Constant(int v) : type(ConstantType::Integer), value(v) {}
    Constant(const std::string& v) : type(ConstantType::String), value(v) {}
    Constant(char v) : type(ConstantType::Char), value(v) {}
    Constant(bool v) : type(ConstantType::Bool), value(v) {}
    Constant(double v) : type(ConstantType::Float), value(v) {}
};
struct Instruction{
    InstructionType type;
    RegisterType reg1;
    RegisterType reg2;
    RegisterType reg3;
    string marker; // This is the marker might be empty
    string variable_name; // This is the variable name
    Constant constant; // This is the constant value
    int val ; // A miscellaneous value that we will use for the instruction
};
struct stackElem{
    shared_ptr<AstNode> value; // Pointer to the automa object
    Instruction instruction; // The instruction that we will use to pop the value
    bool is_instruction = false; // This will be used to check if the value is an instruction or not
};

struct InstructionSet{
    // Will contain a vector of instructions and an unordered map, that maps the markers to the instruction index
    vector<Instruction> instructions;
    unordered_map<string, int> markers; // This will map the markers to the instruction index
    int instruction_start = 0; // This will be the start of the instruction set(for now it might not be 0, it is where the start node is)
};

// A VM compiler will take in a graph ptr and compile it into a set of instructions
// Simple as that
class VMCompiler{
    private:
    shared_ptr<Graph> graph_ptr; // This is the graph ptr
    int current_instruction = 0;
    public:
    shared_ptr<InstructionSet> compile(shared_ptr<Graph> graph_ptr); // This will compile the graph into a set of instructions
    void decode_expression(shared_ptr<AstNode> node, shared_ptr<InstructionSet> instruction_set); // This will decode the expression into a set of instructions
    void print_instructions(const shared_ptr<InstructionSet>& instructionSet); // This will print the instructions
};