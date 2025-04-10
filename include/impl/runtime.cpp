#include "../core/runtime.h"
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/graph.h"
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
            // Loop through the graph decelerations and create the graphs
            for(auto graphDef_ptr : graphDecelerations){
                shared_ptr<graphDec> graphDec_ptr = dynamic_pointer_cast<graphDec>(graphDef_ptr);
                shared_ptr<AstNode> graphDef_node_ptr = graphDec_ptr->getGraphDef();
                operator_ptr->add_astTreeDec(graphDef_node_ptr, graphDec_ptr->getName());
                shared_ptr<Graph> graph = operator_ptr->create_graph(graphDef_node_ptr); // Should the operator even do this?
                // Now we compile the graph
                shared_ptr<InstructionSet> set = vm_compiler_ptr.compile(graph);
                operator_ptr->add_instructionSet(graphDec_ptr->getName(), set);
            
            }
            // We will check if the main graph instruction set is present
            shared_ptr<InstructionSet> main_graph_set = operator_ptr->get_instructionSet("main");
            if(main_graph_set == nullptr){
                cout << "Error: Main graph not found" << endl;
                return;
            }

            // // Now we will create a path and add it to the operator
            shared_ptr<Path> path = shared_ptr<Path>(new Path(0, "main"));
            operator_ptr->add_path(path);
            operator_ptr->run();
        } 
        else{
            cout << "Error in parsing, check for syntax errors" << endl;
        }
}
