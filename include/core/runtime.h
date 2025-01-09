#include <unordered_map>
#include <memory>
#include <string>
#include <vector>
#include "operator.h"
#include "../../grammar/ast/ast_node.h"
#include "../../grammar/parser/parser.h"
#include "../../grammar/ast/ast_tree.h"

using namespace std;

/*
This is for the basic runtime of Automa. We will create an operator object that will control the execution of the paths.
The operator will have a queue of paths that are ready to be executed

The runtime will have access to the input file, the parser and ast tree creator. 

It will run time in sequence after wards, it will create the ast tree and then create 
the operator, afterwards it will invoke the graph to start executing.
*/

class RunTime{
    public:
    shared_ptr<Operator> operator_ptr;
    shared_ptr<AstNode> astTreeRoot;
    shared_ptr<Parser> parser_ptr;
 
    void run(string input_file);
};


