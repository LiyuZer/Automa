#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
Here we define the char type, just your good old char. 
We store is as a char type in c++.

*/

class Char : public Memory{
    private:
    char val;
    public:
    Char(char value) : Memory("char"){
        val = value;
        set_immutable(true);
    }
    char get_val(){
        return val;
    }
    // Define some operations here
    shared_ptr<Char> and_op(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val && other_memory->get_val()));
    }
    shared_ptr<Char> or_op(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val || other_memory->get_val()));
    }
    shared_ptr<Char> not_op(){
        return shared_ptr<Char>(new Char(!val));
    }
    shared_ptr<Char> equal(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val == other_memory->get_val()));
    }
    shared_ptr<Char> not_equal(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val != other_memory->get_val()));
    }
    shared_ptr<Char> less(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val < other_memory->get_val()));
    }
    shared_ptr<Char> greater(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val > other_memory->get_val()));
    }
    shared_ptr<Char> less_equal(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val <= other_memory->get_val()));
    }
    shared_ptr<Char> greater_equal(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val >= other_memory->get_val()));
    }
    shared_ptr<Char> add(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val + other_memory->get_val()));
    }
    shared_ptr<Char> subtract(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val - other_memory->get_val()));
    }
    shared_ptr<Char> multiply(shared_ptr<Char> other_memory){ // I kind of like python's way of doing things so will change soon
        return shared_ptr<Char>(new Char(val * other_memory->get_val()));
    }
    shared_ptr<Char> divide(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val / other_memory->get_val()));
    }
    shared_ptr<Char> modulo(shared_ptr<Char> other_memory){
        return shared_ptr<Char>(new Char(val % other_memory->get_val()));
    }
    shared_ptr<Char> negate(){
        return shared_ptr<Char>(new Char(-val));
    }
};