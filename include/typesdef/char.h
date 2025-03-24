#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
Here we define the char type, just your good old char. 
We store is as a char type in c++.

*/

class Char : public AutomaObject{
    private:
    char val;
    public:
    Char(char value) : AutomaObject("char"){
        val = value;
    }
    char get_val(){
        return val;
    }
    string repr() override{
        return "'" + string(1, val) + "'";
    }
};