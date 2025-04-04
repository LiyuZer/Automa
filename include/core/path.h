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

A path is a sequence of transitions that are executed in order. Thus a path is a sequence of transitions.
and states. 

While designing this system it became apparent early that it would benefit from a IR rep. The reason being 
that the IR rep would allow for a more efficient implementation of the automata. An example being executing a transitions 

A transition is defined as 
    if condition is true:
        operations
        jmp to next node
    else:
        move on to next transition
To manually implement this in a language like C++ would be a pain.
The IR rep allows for a more efficient implementation of the automata. An example being executing a transitions
rather than checking the conditions and then going to check the operation we could represent some IR 
for example suppose the condition is a < b and the operation is a = a + 1
Node 1
Transition 1
    LOAD R1 a 
    LOAD_CONST R2 b
    CMP R3 R1 R2
    JMP_IF R3, Node 2
    JMP_NOT R3, Transition 2
Transition 2
...
This way we can represent the automata in a more efficient way, all we have to do is have one linear sequence 
that we can execute, and execute the instructions, the conditions and operations are all sort of stripped
this makes it much easier. 

In the long run we will have a processor that will execute this IR rep, not a run function within the path 
class, a path is simply a snapshot of the register state of the automata.

*/

using namespace std;


/*
Here we define the return value from the operator
*/


class Path{
    private:
    int id;
    string current_node;
    shared_ptr<Graph> graph_ptr;
    int max_time;
    int current_time;
    int parent_path_id = -1; // -1 if no parent path
    vector<Register> registers; // Registers to store the values of the automa objects
    vector<Instruction> instructions; // Instructions to execute

    public:
    Path(int id, shared_ptr<Graph> graph_ptr, int max_time=10000, int parent_path_id = -1){
        this->parent_path_id = parent_path_id;
        this->id = id;
        this->graph_ptr = graph_ptr;
        this->max_time = max_time;
        this->current_time = 0;
        //Initialize the registers
        for(int i=0; i<10; i++){
            registers.push_back(Register((RegisterType)i, nullptr));
        }
    }

    int get_id(){
        return id;
    }

    shared_ptr<Graph> get_graph(){
        return graph_ptr;
    }
    int get_parent_path_id(){
        return parent_path_id;
    }
    void set_current_node(string node_name){
        current_node = node_name;
    }  
    void run();
    void initialize_queue();
    shared_ptr<AutomaObject> evaluate_primitve_expression(shared_ptr<AstNode> ast_node);
    void add_elem_to_queue(shared_ptr<AstNode> elem);


};