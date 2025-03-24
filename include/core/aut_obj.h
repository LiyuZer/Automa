/*

Here we will define a base Automa graph obj here.
It will have things like reference counting, and serve as the base class for all objects
*/

#pragma once
#include <iostream>
#include <string>

class AutomaObject {
    private:
    int ref_count;
    string type;
    public:
    AutomaObject() : ref_count(0) {}
    AutomaObject(string type) : ref_count(0), type(type) {}
    void increment_ref_count(){
        ref_count++;
    }
    void decrement_ref_count(){
        ref_count--;
    }
    int get_ref_count(){
        return ref_count;
    }
};