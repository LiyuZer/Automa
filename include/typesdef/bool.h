#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
This will be the boolean primitive type, very similar to Int, except not special lol. 
*/

class Bool : public AutomaObject{
    private:
    bool val;
    public:
    Bool(bool value) : AutomaObject("bool"){
        val = value;
    }
    bool get_val(){
        return val;
    }
    shared_ptr<Bool> and_op(shared_ptr<Bool> other){
        return shared_ptr<Bool>(new Bool(val && other->get_val()));
    }
    shared_ptr<Bool> or_op(shared_ptr<Bool> other){
        return shared_ptr<Bool>(new Bool(val || other->get_val()));
    }
    shared_ptr<Bool> not_op(){
        return shared_ptr<Bool>(new Bool(!val));
    }
    string repr(){
        return val ? "true" : "false";
    }
};