#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
// #include "include/core/runtime.h"
#include "include/typesdef/num.h"
// #include "include/typesdef/bool.h"
// Time will be included here 
#include <chrono>

int main(int argc, char* argv[]) {
    // We will convert the incoming argument to a filename
    // string file_name(argv[1]);
    // RunTime runtime;
    // runtime.run(file_name);              
   

    // fibonacci 
    shared_ptr<Num> a = make_shared<Num>("0");
    shared_ptr<Num> b = make_shared<Num>("1");
    shared_ptr<Num> c;
    // add time here  nanoseconds 
    // auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < 100000; i++) {
        c = a->add(b);
        a = b;
        b = c;
    }
    // auto end = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::nanoseconds>(end - start);
    // cout << "Time taken: " << duration.count() << " nanoseconds" << endl;

   
    return 0;                             
}                                      