#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "path.h"
#include "../../grammar/ast/ast_node.h"
#include "vm_compiler.h"


#pragma once
/*
This is effectively the operating system for Automa. 
The operator effectively controls which path runs 
and for how long the path runs for. This way a path can yield 
back to the operator during execution. 


*/
using namespace std;
class Operator{
    private:
    queue<shared_ptr<Path> > path_queue;
    unordered_map<int, shared_ptr<Path>> path_pending_queue; // T
    shared_ptr<Path> current_path;
    unordered_map<string, shared_ptr<AstNode>> graphDecMap;// This will store the root ast node declarations for the graphs
    unordered_map<string, shared_ptr<InstructionSet>> instructionSetMap; // This will store the instruction set for each graph
    int path_id = 0;
    public:

    void add_path(shared_ptr<Path> path){
        path_queue.push(path);
    }
    shared_ptr<Graph> create_graph(shared_ptr<AstNode> graphDef);
    void add_astTreeDec(shared_ptr<AstNode> ast_tree, string graph_name){// Add the ast tree to the graphDecMap
        graphDecMap[graph_name] = ast_tree;
    }

    shared_ptr<AstNode> get_astTreeDec(string graph_name){
        if(graphDecMap.find(graph_name) != graphDecMap.end()){
            return graphDecMap[graph_name];
        }
        return nullptr;
    }
    
    //Add the instruction set to the map
    void add_instructionSet(string graph_name, shared_ptr<InstructionSet> instructionSet){
        instructionSetMap[graph_name] = instructionSet;
    }
    shared_ptr<InstructionSet> get_instructionSet(string graph_name){
        if(instructionSetMap.find(graph_name) != instructionSetMap.end()){
            return instructionSetMap[graph_name];
        }
        return nullptr;
    }

    void run();

};