#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
This will be the None obj, it will be used to represent the absence of a value. 
*/

class None : public AutomaObject{
    public:
    None() : AutomaObject("none"){
    }
    string repr() override{
        return "None";
    }
};