#include <memory>
#include <queue>
#include "ast_tree.h"
#include "../parser/parser.h"
#include "ast_node.h"


shared_ptr<AstNode> AbstractTreeGenerator :: generateTree(shared_ptr<ParseNode> root_node){

    queue<astNodeQueueElem> astNodeQueue;
    string type = root_node->getType(); 

    if(type != "program"){
        cerr << "Error program parse node is not declared, fix grammar" << endl;
        return nullptr;
    }
    shared_ptr<program> program_node = shared_ptr<program>(new program);


    vector<shared_ptr<ParseNode>> children;
    bool found = root_node->addChildrenVec("mainGraph", children);
    

    if(!found){
       cerr << "Error program parse node is not initialized properly, fix grammar" << endl; 
       return nullptr;
    }
    root_node = children[0];// For now we will assume there are no other graph definitions


    // Repeat the same patter for main graphs
    found = root_node->addChildrenVec("graphDef", children);

    if(!found){
        // TODO this should not be a nullptr in this case there is no graphDefinition so just end the program
       return nullptr;
    }

    root_node = children[0];// For now we will assume there are no other graph definitions

    shared_ptr<graphDef> graph_def_ptr = shared_ptr<graphDef>(new graphDef);

    program_node->setGraphDef(graph_def_ptr);// Pointing the program node to the graph def ptr


    vector<shared_ptr<ParseNode>> node_vec;
    root_node->addChildrenVec("nodeDef", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<nodeDef> node_def_ptr = shared_ptr<nodeDef>(new nodeDef);
        graph_def_ptr->set_nodeDef(node_def_ptr);
        astNodeQueueElem elem = astNodeQueueElem(node_def_ptr,node_vec[0]);
        astNodeQueue.push(elem);
    }

    root_node->addChildrenVec("afterAccept", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<afterAcceptDef> afterAccept_ptr = shared_ptr<afterAcceptDef>(new afterAcceptDef);
        graph_def_ptr->set_afterAccept(afterAccept_ptr);
        astNodeQueueElem elem = astNodeQueueElem(afterAccept_ptr,node_vec[0]);
        astNodeQueue.push(elem);
    }

    root_node->addChildrenVec("afterReject", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<afterRejectDef> afterReject_ptr = shared_ptr<afterRejectDef>(new afterRejectDef);
        graph_def_ptr->set_afterReject(afterReject_ptr);
        astNodeQueueElem elem = astNodeQueueElem(afterReject_ptr,node_vec[0]);
        astNodeQueue.push(elem);
        }

    root_node->addChildrenVec("memoryDef", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<memoryDef> memoryDef_ptr = shared_ptr<memoryDef>(new memoryDef);
        graph_def_ptr->set_memoryDef(memoryDef_ptr);
        astNodeQueueElem elem = astNodeQueueElem(memoryDef_ptr,node_vec[0]);
        astNodeQueue.push(elem);
        }

    root_node->addChildrenVec("transitionDef", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<transitionDef> transitionDef_ptr = shared_ptr<transitionDef>(new transitionDef);
        graph_def_ptr->set_transitionDef(transitionDef_ptr);
        astNodeQueueElem elem = astNodeQueueElem(transitionDef_ptr,node_vec[0]);
        astNodeQueue.push(elem);
        }


    while(!astNodeQueue.empty()){
        /*
        Here we will have an iterative method for creating out Abstract syntax tree! Fun! 
        The idea is to perform essentially a breadth first search of our parse tree 
        then add the children of these nodes to the queue. The  queue element will have both the 
        ast node and the parse node, thus we pop the top element explore its parse node, connect 
        the ast node to its children and then push that node to the end of the new queue.

        Each AST node type will have it's associated function for exploration that will return  
        a vector of AST nodes we will then push 
        */

       astNodeQueueElem top = astNodeQueue.front();
       string type = top.astNodeptr->get_type();
       if(type == "memoryDef"){
            explore_memoryDef(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "nodeDef"){
            explore_nodeDef(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "transitionDef"){
            explore_transitionDef(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);

       }
       else if(type == "transitionDefStatements"){
            explore_transitionDefStatements(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "variableDefintions"){
            explore_variableDefinitions(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "nodeDefStatements"){
            explore_nodeDefStatements(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "expression"){
            explore_expression(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "variable"){
            explore_variable(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       } 
       else if(type == "stringLiteral"){
            explore_stringLiteral(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "integerLiteral"){
            explore_integerLiteral(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       } 
       else if(type == "charLiteral"){
            explore_charLiteral(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       } 

       astNodeQueue.pop();

    }
    
    return program_node;
}



void AbstractTreeGenerator:: explore_memoryDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a memory def parse node
    */
    vector<shared_ptr<ParseNode>> node_vec;
    root_node->addChildrenVec("tupleItems", node_vec);
    root_node = node_vec[0];
    root_node->addChildrenVec("varDefenition", node_vec); 
    shared_ptr<memoryDef> memory_ptr = dynamic_pointer_cast<memoryDef>(parentAstNode);
    if(node_vec.size() > 0){
        for(auto node : node_vec){
            shared_ptr<variableDefintions> variable_definiton_ptr = shared_ptr<variableDefintions>(new variableDefintions);
            memory_ptr->add_variableDefinition(variable_definiton_ptr); 
            astNodeQueueElem elem = astNodeQueueElem(variable_definiton_ptr, node);
            astNodeQueue.push(elem);
        }
    }

}
void AbstractTreeGenerator::explore_transitionDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a transition definition parse node
    */

    vector<shared_ptr<ParseNode>> transitions;
    root_node->addChildrenVec("transitionStatement", transitions);
    shared_ptr<transitionDef> transitionNode = dynamic_pointer_cast<transitionDef>(parentAstNode);

    for(auto transition : transitions){
        shared_ptr<transitionDefStatements> transitionDef = shared_ptr<transitionDefStatements>(new transitionDefStatements);
        transitionNode->add_transitionDefStatement(transitionDef);
        astNodeQueueElem elem = astNodeQueueElem(transitionDef, transition);
        astNodeQueue.push(elem);

    }


}

void AbstractTreeGenerator::explore_variableDefinitions(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a variable definitions parse node
    */

    vector<shared_ptr<ParseNode>> expression_vec;
    root_node->addChildrenVec("expression", expression_vec);

    vector<shared_ptr<ParseNode>> variable_vec;
    root_node->addChildrenVec("variable", variable_vec);

    vector<shared_ptr<ParseNode>> identifier;
    variable_vec[0]->addChildrenVec("IDENTIFIER", identifier); // Just take the identifier for the variable name

    string variable = identifier[0]->getValue();

    shared_ptr<variableDefintions> variableDef_ptr = dynamic_pointer_cast<variableDefintions>(parentAstNode);

    shared_ptr<expression> expr_ptr = shared_ptr<expression>(new expression());

    variableDef_ptr->set_variableName(variable);
    variableDef_ptr->set_expression(expr_ptr);


    astNodeQueueElem elem = astNodeQueueElem(expr_ptr, expression_vec[0]);
    astNodeQueue.push(elem);

}

void AbstractTreeGenerator::explore_graphDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a graph definition parse node
    */
}

void AbstractTreeGenerator::explore_nodeDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a node definition parse node
    */
    vector<shared_ptr<ParseNode>> node_vec;
    root_node->addChildrenVec("nodeDefStatement", node_vec);

    shared_ptr<nodeDef> nodeDef_ptr = dynamic_pointer_cast<nodeDef>(parentAstNode);
    if(node_vec.size() > 0){
        for(auto node : node_vec){
            shared_ptr<nodeDefStatements> nodeDefStatement_ptr = shared_ptr<nodeDefStatements>(new nodeDefStatements);
            nodeDef_ptr->add_nodeDefStatement(nodeDefStatement_ptr); 
            astNodeQueueElem elem = astNodeQueueElem(nodeDefStatement_ptr, node);
            astNodeQueue.push(elem);
        }
    }
}

void AbstractTreeGenerator::explore_nodeDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring node definition statements parse node
    */

    vector<shared_ptr<ParseNode>> type_vec;
    root_node->addChildrenVec("nodeTypes", type_vec);
    string type_identifier = "";

    if(!type_vec.empty()){
        vector<shared_ptr<ParseNode>> type_vec_value;
        type_vec[0]->addChildrenVec("START_NODE", type_vec_value);

        if(type_vec_value.empty()){
        type_vec[0]->addChildrenVec("ACCEPT_NODE", type_vec_value);
        }

        if(type_vec_value.empty()){
        type_vec[0]->addChildrenVec("REJECT_NODE", type_vec_value);
        }


        if(!type_vec_value.empty()){
            type_identifier = type_vec_value[0]->getValue();
        }


    }

    vector<shared_ptr<ParseNode>> node;
    root_node->addChildrenVec("IDENTIFIER", node);


    string node_identifier = node[0]->getValue();
    
    shared_ptr<nodeDefStatements> nodeDefStatement_ptr = dynamic_pointer_cast<nodeDefStatements>(parentAstNode);
    nodeDefStatement_ptr->set_nodeType(type_identifier);
    nodeDefStatement_ptr->set_node(node_identifier);

}
void AbstractTreeGenerator::explore_transitionDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring transition definition statements parse node
    */


    vector<shared_ptr<ParseNode>> conditions_expressions;
    root_node->addChildrenVec("conditions", conditions_expressions);
    shared_ptr<ParseNode> conditions_ptr = conditions_expressions[0];
    conditions_ptr->addChildrenVec("conditionStatement", conditions_expressions);

    vector<shared_ptr<ParseNode>> operations_expressions;
    root_node->addChildrenVec("operations", operations_expressions);
    shared_ptr<ParseNode> operations_ptr = operations_expressions[0];
    operations_ptr->addChildrenVec("operationStatement", operations_expressions);


    vector<shared_ptr<ParseNode>> fromNode;
    root_node->addChildrenVec("fromNode", fromNode);
    fromNode[0]->addChildrenVec("IDENTIFIER", fromNode);


    vector<shared_ptr<ParseNode>> toNode;
    root_node->addChildrenVec("toNode", toNode);
    toNode[0]->addChildrenVec("IDENTIFIER", toNode);


    shared_ptr<transitionDefStatements> transitionStatement = dynamic_pointer_cast<transitionDefStatements>(parentAstNode);

    transitionStatement->set_toNode(toNode[0]->getValue());
    transitionStatement->set_fromNode(fromNode[0]->getValue());

    for(auto operation_expression : operations_expressions){
        shared_ptr<expression> operationNode = shared_ptr<expression>(new expression);

        vector<shared_ptr<ParseNode>> expression;
        operation_expression->addChildrenVec("expression", expression);

        if(!expression.empty()){
            transitionStatement->add_operationsExpression(operationNode);
            astNodeQueueElem elem = astNodeQueueElem(operationNode, expression[0]);
            astNodeQueue.push(elem);
        }

    }

    for(auto condition_expression : conditions_expressions){
        shared_ptr<expression> conditionNode = shared_ptr<expression>(new expression);

        vector<shared_ptr<ParseNode>> expression;
        condition_expression->addChildrenVec("expression", expression);

        if(!expression.empty()){
            transitionStatement->add_conditionExpression(conditionNode);
            astNodeQueueElem elem = astNodeQueueElem(conditionNode, expression[0]);
            astNodeQueue.push(elem);
        }

    }

}

void AbstractTreeGenerator::explore_expression(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an expression parse node
    */
    vector<shared_ptr<ParseNode>> literal_vec;
    vector<shared_ptr<ParseNode>> variable_vec;

    root_node->addChildrenVec("literal", literal_vec);
    root_node->addChildrenVec("variable", variable_vec);

    if (!literal_vec.empty()) {
        dynamic_pointer_cast<expression>(parentAstNode)->set_expressionType("literal");

        vector<shared_ptr<ParseNode>> string_vec;
        vector<shared_ptr<ParseNode>> integer_vec;
        vector<shared_ptr<ParseNode>> char_vec;

        literal_vec[0]->addChildrenVec("STRING_LITERAL", string_vec);
        literal_vec[0]->addChildrenVec("INTEGER_LITERAL", integer_vec);
        literal_vec[0]->addChildrenVec("CHAR_LITERAL", char_vec);

        if (!string_vec.empty()) {
            shared_ptr<stringLiteral> stringNode = make_shared<stringLiteral>();
            stringNode->set_stringLiteral(string_vec[0]->getValue());
            dynamic_pointer_cast<expression>(parentAstNode)->set_expression(stringNode);
            astNodeQueue.push(astNodeQueueElem(stringNode, string_vec[0]));
        } else if (!integer_vec.empty()) {
            shared_ptr<integerLiteral> intNode = make_shared<integerLiteral>();
            intNode->set_integerLiteral(stol(integer_vec[0]->getValue()));
            dynamic_pointer_cast<expression>(parentAstNode)->set_expression(intNode);
            astNodeQueue.push(astNodeQueueElem(intNode, integer_vec[0]));
        } else if (!char_vec.empty()) {
            shared_ptr<charLiteral> charNode = make_shared<charLiteral>();
            charNode->set_charLiteral(char_vec[0]->getValue()[0]);
            dynamic_pointer_cast<expression>(parentAstNode)->set_expression(charNode);
            astNodeQueue.push(astNodeQueueElem(charNode, char_vec[0]));
        }
    }

    if (!variable_vec.empty()) {
        dynamic_pointer_cast<expression>(parentAstNode)->set_expressionType("variable");
        shared_ptr<variable> variableNode = make_shared<variable>();

        vector<shared_ptr<ParseNode>> identifier_vec;
        variable_vec[0]->addChildrenVec("IDENTIFIER", identifier_vec);

        if (!identifier_vec.empty()) {
            variableNode->set_variableName(identifier_vec[0]->getValue());
        }

        dynamic_pointer_cast<expression>(parentAstNode)->set_expression(variableNode);
        astNodeQueue.push(astNodeQueueElem(variableNode, variable_vec[0]));
    }
}

void AbstractTreeGenerator::explore_variable(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a variable parse node
    */
    vector<shared_ptr<ParseNode>> identifier_vec;
    root_node->addChildrenVec("IDENTIFIER", identifier_vec);

    if (!identifier_vec.empty()) {
        string variableName = identifier_vec[0]->getValue();
        shared_ptr<variable> variableNode = dynamic_pointer_cast<variable>(parentAstNode);
        variableNode->set_variableName(variableName);
    }
}

void AbstractTreeGenerator::explore_stringLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a string literal parse node
    */
    vector<shared_ptr<ParseNode>> literal_vec;
    root_node->addChildrenVec("STRING_LITERAL", literal_vec);

    if (!literal_vec.empty()) {
        string value = literal_vec[0]->getValue();
        shared_ptr<stringLiteral> stringNode = dynamic_pointer_cast<stringLiteral>(parentAstNode);
        stringNode->set_stringLiteral(value);
    }
}

void AbstractTreeGenerator::explore_integerLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an integer literal parse node
    */
    vector<shared_ptr<ParseNode>> literal_vec;
    root_node->addChildrenVec("INTEGER_LITERAL", literal_vec);

    if (!literal_vec.empty()) {
        long value = stol(literal_vec[0]->getValue());
        shared_ptr<integerLiteral> intNode = dynamic_pointer_cast<integerLiteral>(parentAstNode);
        intNode->set_integerLiteral(value);
    }
}

void AbstractTreeGenerator::explore_charLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a char literal parse node
    */
    vector<shared_ptr<ParseNode>> literal_vec;
    root_node->addChildrenVec("CHAR_LITERAL", literal_vec);

    if (!literal_vec.empty()) {
        char value = literal_vec[0]->getValue()[0]; // Assuming the value is a single character
        shared_ptr<charLiteral> charNode = dynamic_pointer_cast<charLiteral>(parentAstNode);
        charNode->set_charLiteral(value);
    }
}

void AbstractTreeGenerator::explore_afterAccept(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an after accept parse node
    */
}

void AbstractTreeGenerator::explore_afterReject(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an after reject parse node
    */
}



/*
Thanks to GPT we can actually see the DOT file for the AST tree!

*/


// Function to write the AST to a DOT file
void write_ast_to_dot(const shared_ptr<AstNode>& root, const string& filename) {
    ofstream dotFile(filename);

    if (!dotFile.is_open()) {
        throw runtime_error("Could not open file for writing: " + filename);
    }

    dotFile << "digraph AST {\n";

    // Helper function to recursively write nodes and edges
    function<void(const shared_ptr<AstNode>&, int&)> writeNode = [&](const shared_ptr<AstNode>& node, int& nodeId) {
        if (!node) return;

        int currentId = nodeId++;
        dotFile << "    node" << currentId << " [label=\"" << node->repr() << "\"];\n";

        if (auto programNode = dynamic_pointer_cast<program>(node)) {
            if (auto graph = programNode->getGraphDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(graph, nodeId);
            }
        } else if (auto graphNode = dynamic_pointer_cast<graphDef>(node)) {
            if (auto memory = graphNode->get_memoryDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(memory, nodeId);
            }
            if (auto accept = graphNode->get_afterAccept()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(accept, nodeId);
            }
            if (auto reject = graphNode->get_afterReject()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(reject, nodeId);
            }
            if (auto nodes = graphNode->get_nodeDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(nodes, nodeId);
            }
            if (auto transitions = graphNode->get_transitionDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(transitions, nodeId);
            }
        } else if (auto memoryNode = dynamic_pointer_cast<memoryDef>(node)) {
            for (const auto& varDef : memoryNode->get_variableDefinitions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(varDef, nodeId);
            }
        } else if (auto varNode = dynamic_pointer_cast<variableDefintions>(node)) {
            if (auto expr = varNode->get_expression()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(expr, nodeId);
            }
        } 
        else if (auto node_def = dynamic_pointer_cast<nodeDef>(node)) {
                for (const auto& nodeDefStatement : node_def->get_nodeDefStatements()) {
                    dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                    writeNode(nodeDefStatement, nodeId);
                }
            }
        else if (auto node_def = dynamic_pointer_cast<transitionDef>(node)) {
                for (const auto& transitionDefStatement : node_def->get_transitionDefStatements()) {
                    dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                    writeNode(transitionDefStatement, nodeId);
                }
            }           
        else if (auto express = dynamic_pointer_cast<expression>(node)) {
            if (auto expr = express->get_expression()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(expr, nodeId);
            }
        } 
        else if (auto transitionNode = dynamic_pointer_cast<transitionDefStatements>(node)) {
            for (auto conds : transitionNode->get_conditionExpressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(conds, nodeId);
            }
            for (auto ops : transitionNode->get_operationsExpressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << ";\n";
                writeNode(ops, nodeId);
            }
        }
    };

    int nodeId = 0;
    writeNode(root, nodeId);

    dotFile << "}";
    dotFile.close();
}

