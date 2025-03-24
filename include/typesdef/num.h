#include <iostream>
#include <memory>
#include <string>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#include "../typesdef/bool.h"
#include <cmath>
/*
This is the file for defining the num type(one numbers class to control them all), because I am crazy I will make them arbitrary precision in the long run.
For now they are doubles :). 

Let's go! 

*/

class Num : public AutomaObject{
    private:
    double val;
    public:
    Num(double value) : AutomaObject("num"){
        val = value;
    }
    double get_val(){
        return val;
    }
    shared_ptr<Num> add_op(shared_ptr<Num> other){
        return shared_ptr<Num>(new Num(val + other->get_val()));
    }
    shared_ptr<Num> sub_op(shared_ptr<Num> other){
        return shared_ptr<Num>(new Num(val - other->get_val()));
    }
    shared_ptr<Num> mul_op(shared_ptr<Num> other){
        return shared_ptr<Num>(new Num(val * other->get_val()));
    }
    shared_ptr<Num> div_op(shared_ptr<Num> other){
        return shared_ptr<Num>(new Num(val / other->get_val()));
    }
    shared_ptr<Num> mod_op(shared_ptr<Num> other){
        return shared_ptr<Num>(new Num(fmod(val, other->get_val())));
    }
    shared_ptr<Bool> eq_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val == other->get_val()));
    }
    shared_ptr<Bool> neq_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val != other->get_val()));
    }
    shared_ptr<Bool> less_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val < other->get_val()));
    }
    shared_ptr<Bool> greater_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val > other->get_val()));
    }
    shared_ptr<Bool> less_eq_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val <= other->get_val()));
    }
    shared_ptr<Bool> greater_eq_op(shared_ptr<Num> other){
        return shared_ptr<Bool>(new Bool(val >= other->get_val()));
    }
    string to_string(int precision){
        return std::to_string(val);
    }

};

