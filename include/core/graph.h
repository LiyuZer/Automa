#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "/Users/liyuzerihun/Automa/grammar/ast/ast_node.h"
#pragma once

/*

We will define a base Automa graph obj here. 

A graph can be though of in three main parts:-
    The Nodes
    The Transitions 
    The Memory

Every graph must be initialized with all these before executions 
thus we must create the structure for the graph before executing. 

Graphs are just the structure, thus there might be saved data for 
optimization, but for the most part it is used in tandem with a path object 
This path object is the object that traverses the graph, with a unique ID 
for accessing memory.

Graphs given the base AST node can create a graph object, that can be used
*/

struct Node{
    bool reject;
    bool accept;
    bool start;
    string name;
    Node(string name): name(name){}
};
struct transition{

string toNode;
vector<shared_ptr<AstNode> > conditions;
vector<shared_ptr<AstNode> > operations;

};
using namespace std;
class Graph{
    private:
    unordered_map<string, vector<transition> > node_transitions;
    unordered_map<string, Node> node_map;
    shared_ptr<AstNode> graphDef;
    shared_ptr<AstNode> memoryDef;
    shared_ptr<AstNode> memory_def;
    public:
    void add_transition(string fromNode, string toNode, vector<shared_ptr<AstNode>> conditions, vector<shared_ptr<AstNode>> operations){
        transition t;
        t.toNode = toNode;
        t.conditions = conditions;
        t.operations = operations;
        node_transitions[fromNode].push_back(t);
    }
    vector<transition> get_transitions(string fromNode){
        return node_transitions[fromNode];
    }
    void insert_node(string name, Node n){
        node_map[name] = n;
    }
    void set_memory_def(shared_ptr<AstNode> memoryDef){
        memory_def = memoryDef;
    }
    void set_graph_def(shared_ptr<AstNode> graphDef){
        graphDef = graphDef;
    }
    
};