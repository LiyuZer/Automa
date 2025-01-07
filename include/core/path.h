#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "memory.h"
#include <stack>
#pragma once
/*

Here we define a path obj. 

Path objects have 4 main parts:-
    Current state -> the current node of transaction
    ID -> a unique id generated by the operator and given to the 
    path obj 
    timer(to be implemented) -> a count down timer, when this times is finished 
    the graph yields back to the operator. 
    Memory container -> a ptr to the memory container for executions
    Memory log(to be implemented) -> a memory log of all changed memory parts, 
    to be used during acceptance rejection.



A path is an abstraction for computation it can be accepted, rejected or in a pending 
state. It is called by an operator, set with the memory container, it runs independently and 
yields back to the operator, very similar to limited time context switching 
by the operating system between processes. 

*/

using namespace std;
/*
   This is a typical stack element:-
    {
        memory_container : memory_container
        type : ""  (Binary, Unary, Literal. Graph call)
        Stack_elem_ptr_ls : a vector of shared ptr to stack elements that may nor may not be evaluated 
    }
*/
struct stackElement{
    shared_ptr<Memory> memory_container;
    string type;
    vector<shared_ptr<stackElement> > stack_elem_ptr_ls;
    shared_ptr<AstNode> ast_node;
};
struct operatorReturn{
/*
This will have two values 
*/
int status; 
string graph_name;
shared_ptr<Memory> memory_containers; // The argument to be passed to the graph
};
class Path{
    private:
    int id;
    string current_node;
    shared_ptr<Graph> graph_ptr;
    int max_time;
    int current_time;
    shared_ptr<Memory> memory_ptr;
    unordered_map<int, vector<string> > memory_log;
    stack<shared_ptr<stackElement> > computation_stack;
    int current_condition = 0; // The current condition being evaluated
    int current_operation = 0; // The current operation being evaluated
    int current_transition = 0; // The current transition being evaluated
    operatorReturn operator_return; // The return value from the operator

    shared_ptr<Memory> input; // The input memory container by the operator(if yielded or the path is created as a result of a graph call)
    int path_to_yield = -1; // The path to yield to the operator, in case of a graph call

    public:
        Path(int id, string current_node, int max_time, int current_time, shared_ptr<Graph> graph_ptr)
        : id(id), current_node(current_node), max_time(max_time), current_time(current_time), graph_ptr(graph_ptr) {}

        int run();
        void add_yield();
        shared_ptr<Memory> evaluateExpression();
        shared_ptr<Memory> evaluateBinaryExpressionPrimitive(shared_ptr<Memory> left, shared_ptr<Memory> right, string operations);
        shared_ptr<stackElement> addElementToStack(shared_ptr<AstNode> ast_node);
        void set_memory(shared_ptr<AstNode> memory);
        void set_input(shared_ptr<Memory> input){
            this->input = input;
        }
        void set_path_to_yield(int path_id){
            path_to_yield = path_id;
        }
        int get_path_to_yield(){
            return path_to_yield;
        }
        int get_id(){
            return id;
        }
        shared_ptr<Memory> get_memory(){
            return memory_ptr;
        }
        shared_ptr<Graph> get_graph(){
            return graph_ptr;
        }
        void set_memory(shared_ptr<Memory> memory){
            memory_ptr = memory;
        }
        void add_symbol(string symbol){// Add a memory symbol to the memory container
            memory_ptr->set_memory(symbol, shared_ptr<Memory>(new Memory));
        }
        shared_ptr<Memory> get_memory_symbol(string symbol){// Get a memory symbol from the memory container
            return memory_ptr->get_memory(symbol);
        }
        void change_symbol(string symbol, shared_ptr<Memory> memory){// Change a memory symbol in the memory container
            memory_ptr->set_memory(symbol, memory);
        }

    


};