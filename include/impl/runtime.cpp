#include "../core/runtime.h"
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"

void RunTime :: run(string input_file){
        Lexer myLexer;

        string input_text;
        readFile(input_file, input_text);

        Parser myParser;
        shared_ptr<ParseNode> ptr;
        cout << myParser.parse(myLexer,input_text, rules, ptr) << endl;

        if(ptr){
            ptr->collapseDynamicNodes();
            AbstractTreeGenerator ast_generator;
            shared_ptr<AstNode> ast_ptr = ast_generator.generateTree(ptr);
            write_ast_to_dot(ast_ptr, "graph.dot"); //Writing to a graph file
            // Create the operator
            operator_ptr = shared_ptr<Operator>(new Operator);
            // The ast ptr should be a program node 
            shared_ptr<program> program_ptr = dynamic_pointer_cast<program>(ast_ptr);
            //Now we will cast the graphDef ast to a graphDef node
            shared_ptr<graphDef> graphDef_ptr = dynamic_pointer_cast<graphDef>(program_ptr->getGraphDef());
            operator_ptr->set_astTree(ast_ptr);
            shared_ptr<Graph> graph = operator_ptr->create_graph(graphDef_ptr);
            
            operator_ptr->run();
        }
        else{
            cout << "Error in parsing, check for syntax errors" << endl;
        }
}
