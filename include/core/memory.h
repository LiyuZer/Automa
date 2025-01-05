#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "object.h"
#pragma once
/*

We define the memory container class here. 

The memory container class in Automa is the closest thing to a type in Automa. 
Every type, is actually a memory container, where a specific symbol called type 
maps to a string representing the type. 

So for example an int is represented as a memory container, where 
type is just a symbol of the memory container and returns an int. 

A memory container is essentially a map between symbols and other memory containers 

Example :-
    memory {
    a : "hello world", 
    b : 6,
    c : { alpha : 1, beta: 2
            }
    }

In this case we have a memory container with symbols mapping to other memory container,
such as the integers and the memory container that c is mapping to.

To make containers as lightweight as possible, we will use structs as the basic building block. 
*/
using namespace std;

class Memory : public AutomaObj{
      
    private:
    struct SymbolMap{
    unordered_map<string, shared_ptr<Memory> > map;
    };
    unordered_map<int, shared_ptr<SymbolMap> > symbol_map; // The symbol map for the memory container 
    // This can be changed if a non deterministic path is generated and it changes the memory container
    // then a new memory container is created.
    bool immutable; // Memory containers can be immutable thus we can set this flag to true if we want to make the memory container immutable

    public :
    Memory() : immutable(false){}
    void set_immutable(bool immut){
        immutable = immut;
    }
    bool get_immutable(){
        return immutable;
    }
    virtual shared_ptr<Memory> get_memory(string symbol){
        // Get the memory container for a symbol
        return symbol_map[0]->map[symbol];
    }
    virtual void set_memory(string symbol, shared_ptr<Memory> memory){
        // Set the memory container for a symbol
        symbol_map[0]->map[symbol] = memory;
    }
    
};