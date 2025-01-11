#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "include/core/runtime.h"
#include "include/typesdef/num.h"
#include "include/typesdef/bool.h"


int main(int argc, char* argv[]) {
    // We will convert the incoming argument to a filename
    string file_name(argv[1]);
    RunTime runtime;
    runtime.run(file_name);              
   
    // // We will test out the multiply by power of 2 function
    // string num = "5.5";
    // shared_ptr< Num > n = make_shared< Num >(num);
    // string num2 ="5.5";
    // shared_ptr< Num > n2 = make_shared< Num >(num2);
    // // Let us test multiplication
    // shared_ptr< Num > result = n->mul(n2);
    // cout << "Result: " << result->to_string(12) << endl;
   
    return 0;                             
}                                      