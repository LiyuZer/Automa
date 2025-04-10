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
This is the file for defining the string type
*/
class String : public AutomaObject{
    private:
    std::string val;
    public:
    String(std::string value) : AutomaObject("string"){
        val = value;
    }
    std::string get_val(){
        return val;
    }
    string repr() override{
        return "\"" + val + "\"";
    }
};