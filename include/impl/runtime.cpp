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
            ptr->toDot("parser.dot");
            AbstractTreeGenerator ast_generator;
            shared_ptr<AstNode> ast_ptr = ast_generator.generateTree(ptr);
            write_ast_to_dot(ast_ptr, "graph.dot");
        }
}
