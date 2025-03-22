/*

Here we will define a base Automa graph obj here.
It will have things like reference counting, and serve as the base class for all objects
*/

#pragma once


class AutomaObject {
    private:
    int ref_count;
    public:
    AutomaObject() : ref_count(0) {}
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