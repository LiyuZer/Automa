#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
This will be the boolean primitive type, very similar to Int, except not special lol. 
*/

class Bool : public Memory{
    private:
    bool val;
    public:
    Bool(bool value) : Memory("bool"){
        val = value;
        set_immutable(true);
    }
    shared_ptr<Bool> and_op(shared_ptr<Bool> other_memory){
        return shared_ptr<Bool>(new Bool(val && other_memory->get_val()));
    }
    shared_ptr<Bool> or_op(shared_ptr<Bool> other_memory){
        return shared_ptr<Bool>(new Bool(val || other_memory->get_val()));
    }
    shared_ptr<Bool> not_op(){
        return shared_ptr<Bool>(new Bool(!val));
    }
    bool get_val(){
        return val;
    }
};