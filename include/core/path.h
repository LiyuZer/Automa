#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "memory.h"
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
class Path{
    private:
    int id;
    string current_node;
    shared_ptr<Graph> graph_ptr;
    int max_time;
    int current_time;
    shared_ptr<Memory> memory_ptr;
    unordered_map<int, vector<string> > memory_log;

    public:
        Path(int id, string current_node, int max_time, int current_time, shared_ptr<Graph> graph_ptr)
        : id(id), current_node(current_node), max_time(max_time), current_time(current_time), graph_ptr(graph_ptr) {}

};