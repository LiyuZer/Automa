#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "include/core/runtime.h"
#include "include/typesdef/num.h"



int main(int argc, char* argv[]) {
    // We will convert the incoming argument to a filename
    string file_name(argv[1]);
    RunTime runtime;
    runtime.run(file_name);              

    // // We will test out the multiply by power of 2 function
    // string num = "5.555";
    // Num n = Num(num);
    // cout<<n.to_string()<<endl;
    return 0;                       
}  
    
       