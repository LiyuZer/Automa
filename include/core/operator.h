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
    shared_ptr<AstNode> astTree;

    public:

    void add_path(shared_ptr<Path> path){
        path_queue.push(path);
    }

};