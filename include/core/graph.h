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

struct transition{

string toNode;
vector<shared_ptr<AstNode> > conditions;
vector<shared_ptr<AstNode> > operations;

};
using namespace std;
class Graph{
    private:
    unordered_map<string, vector<transition> > node_map;
    public:
    void add_transition(string fromNode, string toNode, vector<AstNode> conditions, vector<AstNode> operations);// Adding transitions here
    vector<AstNode> get_conditions(string fromNode, string toNode);
    vector<AstNode> get_operations(string fromNode, string toNode);
    void create_graph(shared_ptr<AstNode> graphDef);
    
};