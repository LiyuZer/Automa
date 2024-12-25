#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include "include/core/runtime.h"

int main(int argc, char* argv[]) {
    // We will convert the incoming argument to a filename
    string file_name(argv[1]);
    RunTime runtime;
    runtime.run(file_name);

    return 0;
}