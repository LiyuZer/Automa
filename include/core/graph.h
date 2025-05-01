#include <string>
#include <vector>
#include <unordered_map>
#include "../../grammar/ast/ast_node.h"
#include <fstream>
#include <iostream>

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
    Node() : reject(false), accept(false), start(false), name("") {}
    Node(string name): name(name), reject(false), accept(false), start(false) {}
};
struct transition{

string toNode;
shared_ptr<AstNode> condition;
vector<shared_ptr<AstNode> > operations;

};

using namespace std;
class Graph{
    private:
    unordered_map<string, vector<transition> > node_transitions;
    unordered_map<string, Node> node_map;
    shared_ptr<AstNode> graphDef;
    shared_ptr<AstNode> parameterDef;
    shared_ptr<AstNode> accept;
    string start_node=""; 
    public:
    void add_transition(string fromNode, string toNode, shared_ptr<AstNode> condition, vector<shared_ptr<AstNode>> operations){
        transition t;
        t.toNode = toNode;
        t.condition = condition;
        t.operations = operations;
        node_transitions[fromNode].push_back(t);
    }
    vector<transition> get_transitions(string fromNode){
        return node_transitions[fromNode];
    }
    int insert_node(string name, Node n){// return 0 if successful, -1 if node already exists
        if(node_map.find(name) != node_map.end()){
            return -1;
        }
        node_map[name] = n;
        return 0;
    }
    void set_paramater_def(shared_ptr<AstNode> memoryDef){
        parameterDef = memoryDef;
    }
    shared_ptr<AstNode> get_parameter_def(){
        return parameterDef;
    }
    void set_accept(shared_ptr<AstNode> a){
        accept = a;
    }
    shared_ptr<AstNode> get_accept(){
        return accept;
    }
    vector<string> return_node_list(){
        vector<string> node_list;
        for(auto it = node_map.begin(); it != node_map.end(); it++){
            node_list.push_back(it->first);
        }
        return node_list;
    } 
    void set_graph_def(shared_ptr<AstNode> gd){
        graphDef = gd;
    }
    void set_start_node(string start){
        start_node = start;
    }
    string get_start_node(){
        return start_node;
    }
    // a function to check if a node is an accept node
    bool is_accept_node(string node){
        return node_map[node].accept;
    }
    void graph_to_dot(const Graph& graph, const string& filename) {
    std::ofstream dotFile(filename);
    if (!dotFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return;
    }

    // Begin the DOT file
    dotFile << "digraph G {\n";

    // Add nodes
    for (const auto& [name, node] : graph.node_map) {
        dotFile << "    \"" << name << "\"";
        if (node.start) {
            dotFile << " [shape=doublecircle, color=green, style=bold];\n";
        } else if (node.accept) {
            dotFile << " [shape=doublecircle, color=blue];\n";
        } else if (node.reject) {
            dotFile << " [shape=doublecircle, color=red];\n";
        } else {
            dotFile << " [shape=circle];\n";
        }
    }

    // Add transitions
    for (const auto& [fromNode, transitions] : graph.node_transitions) {
        for (const auto& transition : transitions) {
            dotFile << "    \"" << fromNode << "\" -> \"" << transition.toNode << "\"";

            // Add label with conditions and operations if present
            if (!(transition.condition == nullptr) || !transition.operations.empty()) {
                dotFile << " [label=\"";
                // if (!(transition.condition == nullptr)) {
                //     dotFile << "Conditions: ";
                //     dotFile << transition.condition->repr() << " ";
                // }
                // if (!transition.operations.empty()) {
                //     if (!(transition.condition == nullptr)) {
                //         dotFile << "\\n";
                //     }
                //     dotFile << "Operations: ";
                //     for (const auto& operation : transition.operations) {
                //         dotFile << operation->repr() << " ";
                //     }
                // }
                dotFile << "\"]";
            }

            dotFile << ";\n";
        }
    }

    // End the DOT file
    dotFile << "}\n";

    dotFile.close();
    std::cout << "DOT file saved to " << filename << std::endl;
}

};