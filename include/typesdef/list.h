#include <iostream>
#include <memory>
#include <string>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
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

class List : public Memory{
    private:
    vector<shared_ptr<Memory>> list_nodes;
    
    public:
    List() : Memory("list"){}
    List(vector<shared_ptr<Memory>> list_nodes) : Memory("list"), list_nodes(list_nodes){}
    void add_list_node(const shared_ptr<Memory>& node){
        list_nodes.push_back(node);
    }
    vector<shared_ptr<Memory>> get_list_node(){
        return list_nodes;
    }
    shared_ptr<Memory> get_list_node(int index){
        return list_nodes[index];
    }
    void set_list_node(int index, shared_ptr<Memory> node){
        list_nodes[index] = node;
    }
    void remove_list_node(int index){
        list_nodes.erase(list_nodes.begin() + index);
    }
    void insert_list_node(int index, shared_ptr<Memory> node){
        list_nodes.insert(list_nodes.begin() + index, node);
    }
    shared_ptr<List> slice(int start, int end){
        shared_ptr<List> new_list = shared_ptr<List>(new List);
        for(int i = start; i < end; i++){
            new_list->add_list_node(list_nodes[i]);
        }
        return new_list;
    }
    void append(shared_ptr<Memory> node){
        list_nodes.push_back(node);
    }
    void remove(int index){
        list_nodes.erase(list_nodes.begin() + index);
    }
    // We will define the add operation for the list
    List add(shared_ptr<List> list_memory){
        List new_list;
        for(int i = 0; i < list_nodes.size(); i++){
            new_list.add_list_node(list_nodes[i]);
        }
        for(int i = 0; i < list_memory->get_list_node().size(); i++){
            new_list.add_list_node(list_memory->get_list_node()[i]);
        }
        return new_list;
    }



};