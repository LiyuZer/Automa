#include <iostream>
#include <memory>
#include <string>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"
#include "../typesdef/bool.h"


/*
Here we will define the list memory container, a fundamental data structure that will be used in the language.
It will have an internal list of memory containers, int the form of a vector of shared pointers to memory containers.

Additionally it will have a specific set of functionalities that will be used in the language, such as append, remove, insert, and get.

Also slicing will be used as a function, and will be implemented as a function that will return a new list memory container.

This ls[2:3] will be very mich possible in the language, and will be implemented as a function that will return a new list memory container.

The list memory container will be an immutable type, and will have a type of "list".

{
    val : vector of shared pointers to memory containers
    type : "list"
    append : graph, 
    remove : graph,
    insert : graph,
    get : graph,
    slice : graph
}

*/

class List : public AutomaObject{
    private:
    vector<shared_ptr<AutomaObject>> val;
    public:
    List(vector<shared_ptr<AutomaObject>> value) : AutomaObject("list"){
        val = value;
    }
    vector<shared_ptr<AutomaObject>> get_val(){
        return val;
    }
    void append(shared_ptr<AutomaObject> element){
        val.push_back(element);
    }
    void remove(int index){
        if(index >= 0 && index < val.size()){
            val.erase(val.begin() + index);
        }
    }
    void insert(int index, shared_ptr<AutomaObject> element){
        if(index >= 0 && index <= val.size()){
            val.insert(val.begin() + index, element);
        }
    }
    shared_ptr<AutomaObject> get(int index){
        if(index >= 0 && index < val.size()){
            return val[index];
        }
        return nullptr;
    }
    shared_ptr<List> slice(int start, int end){
        if(start < 0 || end > val.size() || start > end){
            return nullptr;
        }
        vector<shared_ptr<AutomaObject>> new_val(val.begin() + start, val.begin() + end);
        return shared_ptr<List>(new List(new_val));
    }
    string repr() override{
        string result = "[";
        for(int i = 0; i < val.size(); i++){
            result += val[i]->repr();
            if(i < val.size() - 1){
                result += ", ";
            }
        }
        result += "]";
        return result;
    }
};