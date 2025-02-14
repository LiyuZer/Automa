#include <iostream>
#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#pragma once

/*
This will be the None memory container, it will be used to represent the absence of a value. 
*/

class None : public Memory{
    public:
    None() : Memory("none"){
        set_immutable(true);
    }
};