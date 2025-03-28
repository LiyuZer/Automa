#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "graph.h"
#include "aut_obj.h"
#include <queue>
#pragma once
/*

Here we define a path obj. 

Path objects have 4 main parts:-
    Current state -> the current node of transaction
    ID -> a unique id generated by the operator and given to the 
    path obj 
    timer(to be implemented) -> a count down timer, when this times is finished 
    the graph yields back to the operator. 


A path is an abstraction for computation it can be accepted, rejected or in a pending 
state. 

During transition evaluation we first put the condition expression and 
then the operations expressions in an array. They will be in array for the current transition. 
However we will store the array later in a cache, so that if we revisit the transition we can
use the cached version. This will help with optimization.

When we get a to a new transition we do the following 
    1. Check if the transition is in the cache, if so use it 
    2. If not then evaluate the condition expression and then the operations expressions 
    3. Store the results in the cache for future use. 


Not if it is in the cache we will still evaluate the expression, it is just that we will not remake some constants 
the stack elements and other things will still be evaluated.


*/

using namespace std;
/*
   This is a typical stack element:-
    {
        AuromaObject : a shared pointer to the object in the graph
        type : ""  (Binary, Unary, Literal. Graph call)
        Stack_elem_ptr_ls : a vector of shared ptr to stack elements that may nor may not be evaluated 
    }
*/
enum class EvalState {
    NotStarted,
    WaitingDependencies,
    Completed
};
struct queueElement{
    char status=0;// In special cases we will have a status
    shared_ptr<AutomaObject> object;
    string type;
    vector<shared_ptr<queueElement>> queue_elem_ptr_ls;
    shared_ptr<AstNode> ast_node;
    EvalState state;
    int parent_index=-1; // This is the index of the parent element in the queue, only needed if this is the last element needed to evaluate the parent


};
/*
Here we define the return value from the operator
*/
struct operatorReturn{
    /*
    This will have two values 
    */
    int status; 
    string graph_name;
    vector<shared_ptr<AutomaObject>> arguments; // The argument to be passed to the graph
};

class Path{
    private:
    int id;
    string current_node;
    shared_ptr<Graph> graph_ptr;
    int max_time;
    int current_time;
    int parent_path_id = -1; // -1 if no parent path
    int current_transition_index = 0; // The index of the current transition
    int current_queue_index = 0; // The index of the current stack element
    int conditions_queue_end = 0; // The end of the conditions queue
    bool started_transition = false; // Flag to check if we started the transition
    shared_ptr<vector<shared_ptr<queueElement>>> queue; // This will store the queue elements
    unordered_map<string, shared_ptr<vector<shared_ptr<queueElement>>>> queue_cache; // This will store the cached queue elements

    public:
    Path(int id, shared_ptr<Graph> graph_ptr, int max_time=10000, int parent_path_id = -1){
        this->parent_path_id = parent_path_id;
        this->id = id;
        this->graph_ptr = graph_ptr;
        this->max_time = max_time;
        this->current_time = 0;
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
    shared_ptr<operatorReturn> run();
    void initialize_queue();
    shared_ptr<AutomaObject> evaluate_primitve_expression(shared_ptr<AstNode> ast_node);
    void add_elem_to_queue(shared_ptr<AstNode> elem);
    void set_current_transition_index(int index){
        current_transition_index = index;
    }
    int get_current_transition_index(){
        return current_transition_index;
    }
    shared_ptr<operatorReturn> forward_evaluation();


};