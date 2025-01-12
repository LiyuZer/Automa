#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include "path.h"
#include "../../grammar/ast/ast_node.h"


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
    queue<shared_ptr<Path> > path_pending_queue;
    shared_ptr<Path> current_path;
    unordered_map<string, shared_ptr<AstNode>> graphDecMap;// This will store the root ast node declarations for the graphs
    unordered_map<string, shared_ptr<Graph> > graph_map;// This will store the graph objects

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
    
    void add_graph(shared_ptr<Graph> graph, string graph_name){
        graph_map[graph_name] = graph;
    }
    shared_ptr<Graph> get_graph(string graph_name){
        if(graph_map.find(graph_name) != graph_map.end()){
            return graph_map[graph_name];
        }
        return nullptr;
    }

    void run();

};