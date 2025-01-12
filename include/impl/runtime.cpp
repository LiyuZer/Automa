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
            ptr->toDot("parse_tree.dot");
            AbstractTreeGenerator ast_generator;
            shared_ptr<AstNode> ast_ptr = ast_generator.generateTree(ptr);
            write_ast_to_dot(ast_ptr, "graph.dot"); //Writing to a graph file
            // Create the operator
            operator_ptr = shared_ptr<Operator>(new Operator);
            // The ast ptr should be a program node 
            shared_ptr<program> program_ptr = dynamic_pointer_cast<program>(ast_ptr);
            //Now we will cast the graphDef ast to a graphDef node
            vector<shared_ptr<AstNode>> graphDecelerations = program_ptr->get_graphDec();
            for(auto graphDef_ptr : graphDecelerations){
                shared_ptr<graphDec> graphDec_ptr = dynamic_pointer_cast<graphDec>(graphDef_ptr);
                shared_ptr<AstNode> graphDef_node_ptr = graphDec_ptr->getGraphDef();
                operator_ptr->add_astTreeDec(graphDef_node_ptr, graphDec_ptr->getName());
                shared_ptr<Graph> graph = operator_ptr->create_graph(graphDef_node_ptr);
                operator_ptr->add_graph(graph, graphDec_ptr->getName());
            }
            // We will check if the main graph is present
            shared_ptr<Graph> graph = operator_ptr->get_graph("main");
            if(!graph){
                cerr << "Error, main graph not found" << endl;
                exit(1);
            }
            // Now we will create a path and add it to the operator
            shared_ptr<Path> path = shared_ptr<Path>(new Path(0, graph->get_start_node(), 1000000, 0, graph));
            operator_ptr->add_path(path);
            operator_ptr->run();// Now it is up to the operator to run the paths
        } 
        else{
            cout << "Error in parsing, check for syntax errors" << endl;
        }
}
