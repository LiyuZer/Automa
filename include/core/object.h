/*
The base Automa Object, defined as AutObj, this class 
has a reference counter, and a type pointer that points to the 
type of the object(a memory container), these two point to each other.

The object base class only has to deal with the the reference count of the obj 
for clean up(for now). 

*/
#pragma once

class AutomaObj{
    private:
        int ref_count; 
    
    public: 
        AutomaObj(): ref_count(0){}
        void increment_count(){
            ref_count++;
        }
        void decrement_count(){
            ref_count++;
        }
        
};