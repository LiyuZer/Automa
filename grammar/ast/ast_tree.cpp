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


    vector<shared_ptr<ParseNode> > graph_dec_vec;
    root_node->addChildrenVec("graphDec", graph_dec_vec);


    if( graph_dec_vec.size() == 0){
        cerr << "Error program parse node is not initialized properly, fix grammar" << endl; 
        return nullptr;
    }


    for(auto graph_dec_ptr : graph_dec_vec){

        shared_ptr<graphDec> graph_dec_node = shared_ptr<graphDec>(new graphDec);
        program_node->addGraphDec(graph_dec_node);

        // Get the name of the graph
        vector<shared_ptr<ParseNode>> name_vec;
        graph_dec_ptr->addChildrenVec("IDENTIFIER", name_vec);
        if(name_vec.size() == 0){
            cerr << "Error graph name not defined properly, fix grammar" << endl;
            return nullptr;
        }
        graph_dec_node->setName(name_vec[0]->getValue());

        // Add the graph definition child here(if it doesn't exist skip, ie empty graph)
        vector<shared_ptr<ParseNode>> graph_def_vec;
        graph_dec_ptr->addChildrenVec("graphDef", graph_def_vec);


        if(graph_def_vec.size() > 0){
            shared_ptr<graphDef> graph_def_ptr = shared_ptr<graphDef>(new graphDef);            
            graph_dec_node->setGraphDef(graph_def_ptr);

            vector<shared_ptr<ParseNode> > node_vec;
            graph_def_vec[0]->addChildrenVec("nodeDef", node_vec);
            if(node_vec.size() > 0){
                shared_ptr<nodeDef> node_def_ptr = shared_ptr<nodeDef>(new nodeDef);
                graph_def_ptr->set_nodeDef(node_def_ptr);
                astNodeQueueElem elem = astNodeQueueElem(node_def_ptr,node_vec[0]);
                astNodeQueue.push(elem);
            }

            graph_def_vec[0]->addChildrenVec("afterAccept", node_vec);
            if(node_vec.size() > 0){
                shared_ptr<afterAcceptDef> afterAccept_ptr = shared_ptr<afterAcceptDef>(new afterAcceptDef);
                graph_def_ptr->set_afterAccept(afterAccept_ptr);
                astNodeQueueElem elem = astNodeQueueElem(afterAccept_ptr,node_vec[0]);
                astNodeQueue.push(elem);
            }

            graph_def_vec[0]->addChildrenVec("afterReject", node_vec);
            if(node_vec.size() > 0){
                shared_ptr<afterRejectDef> afterReject_ptr = shared_ptr<afterRejectDef>(new afterRejectDef);
                graph_def_ptr->set_afterReject(afterReject_ptr);
                astNodeQueueElem elem = astNodeQueueElem(afterReject_ptr,node_vec[0]);
                astNodeQueue.push(elem);
                }

            graph_def_vec[0]->addChildrenVec("memoryDef", node_vec);
            if(node_vec.size() > 0){
                shared_ptr<memoryDef> memoryDef_ptr = shared_ptr<memoryDef>(new memoryDef);
                graph_def_ptr->set_memoryDef(memoryDef_ptr);
                astNodeQueueElem elem = astNodeQueueElem(memoryDef_ptr,node_vec[0]);
                astNodeQueue.push(elem);
                }

            graph_def_vec[0]->addChildrenVec("transitionDef", node_vec);
            if(node_vec.size() > 0){
                shared_ptr<transitionDef> transitionDef_ptr = shared_ptr<transitionDef>(new transitionDef);
                graph_def_ptr->set_transitionDef(transitionDef_ptr);
                astNodeQueueElem elem = astNodeQueueElem(transitionDef_ptr,node_vec[0]);
                astNodeQueue.push(elem);
                }

        }
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
       else if(type == "list"){
            explore_list(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "listAccess"){
            explore_list_access(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       }
       else if(type == "listSlice"){
            explore_list_slice(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
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
       else if(type == "decimalLiteral"){
            explore_decimalLiteral(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       } 
       else if(type == "boolLiteral"){
            explore_boolLiteral(astNodeQueue.front().parseNodeptr,astNodeQueue.front().astNodeptr,  astNodeQueue);
       } 
       astNodeQueue.pop();

    }
    
    return program_node;
}




void AbstractTreeGenerator:: explore_memoryDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a memory def parse node
    */
    vector<shared_ptr<ParseNode> > node_vec;
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

    vector<shared_ptr<ParseNode> > transitions;
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
    Here is the rule for the variable definition
    {"varDefenition", {
        CreateRule("variable"),
        CreateToken("COLON"),
        CreateRule("expression"),
    }}
    */

    vector<shared_ptr<ParseNode> > variable_vec;
    root_node->addChildrenVec("variable", variable_vec);

    vector<shared_ptr<ParseNode> > identifier;
    variable_vec[0]->addChildrenVec("IDENTIFIER", identifier); // Just take the identifier for the variable name

    string variable = identifier[0]->getValue();

    shared_ptr<variableDefintions> variableDef_ptr = dynamic_pointer_cast<variableDefintions>(parentAstNode);

    variableDef_ptr->set_variableName(variable);
    // Now we will see if there is an expression and add it to the queue
    vector<shared_ptr<ParseNode> > expression_vec;
    root_node->addChildrenVec("expression", expression_vec);
    if(expression_vec.size() > 0){
        // Create a new expression node
        shared_ptr<expression> expression_node = shared_ptr<expression>(new expression);
        variableDef_ptr->set_elem(expression_node);
        // Push the node to the queue
        astNodeQueueElem elem = astNodeQueueElem(expression_node, expression_vec[0]);
        astNodeQueue.push(elem);
    }

}

void AbstractTreeGenerator:: explore_list(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a list parse node
    Here is the rule 
    { "list" , { 
        CreateToken("LEFT_BRACKET"), 
        CreateParen('('),
        CreateRule("expression"), 
        CreateParen('('),
        CreateToken("COMMA"),
        CreateRule("expression"),
        CreateParen(')'),
        CreateSpecialSymbol('*'),
        CreateParen(')'),
        CreateSpecialSymbol('?'),
        CreateToken("RIGHT_BRACKET")

    }},
    */

    // get a list node
    shared_ptr<list> list_ptr = dynamic_pointer_cast<list>(parentAstNode);
    //Loop through the children of the list node
    vector<shared_ptr<ParseNode> > children;
    root_node->addChildrenVec("expression", children);
    for(auto child : children){
        shared_ptr<expression> expression_ptr = shared_ptr<expression>(new expression);
        list_ptr->add_list_node(expression_ptr);
        astNodeQueueElem elem = astNodeQueueElem(expression_ptr, child);
        astNodeQueue.push(elem);
    }
    // This is all we need to do for the list node

   
}
void AbstractTreeGenerator:: explore_list_access(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a list access parse node
    Here is the rule 
    {"listAccess", {
        CreateRule("variable"), 
        CreateToken("LEFT_BRACKET"), 
        CreateToken("INTEGER_LITERAL"),
        CreateToken("RIGHT_BRACKET"), 
    }},
    */

    shared_ptr<listAccess> listAccess_ptr = dynamic_pointer_cast<listAccess>(parentAstNode);
    vector<shared_ptr<ParseNode> > variable_vec;
    root_node->addChildrenVec("variable", variable_vec);
    shared_ptr<variable> variable_ptr = dynamic_pointer_cast<variable>(parentAstNode);
    if(variable_vec.size() > 0){
        // Set the variable 
        listAccess_ptr->set_variable(variable_ptr);

        //Push the variable to the queue
        astNodeQueueElem elem = astNodeQueueElem(variable_ptr, variable_vec[0]);
    }

    vector<shared_ptr<ParseNode> > integer_vec;
    root_node->addChildrenVec("INTEGER_LITERAL", integer_vec);
    if(integer_vec.size() > 0){
        listAccess_ptr->set_index(stoi(integer_vec[0]->getValue()));
    }

}

void AbstractTreeGenerator:: explore_list_slice(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a list slicing parse node
    Here is the rule 
    {"listSlice", {
        CreateRule("variable"), 
        CreateToken("LEFT_BRACKET"), 
        CreateToken("INTEGER_LITERAL"),
        CreateToken("COLON"),
        CreateToken("INTEGER_LITERAL"),
        CreateToken("RIGHT_BRACKET"), 
    }},
    */

    shared_ptr<listSlice> listSlice_ptr = dynamic_pointer_cast<listSlice>(parentAstNode);
    vector<shared_ptr<ParseNode> > variable_vec;
    root_node->addChildrenVec("variable", variable_vec);
    shared_ptr<variable> variable_ptr = dynamic_pointer_cast<variable>(parentAstNode);
    if(variable_vec.size() > 0){
        // Set the variable 
        listSlice_ptr->set_variable(variable_ptr);

        //Push the variable to the queue
        astNodeQueueElem elem = astNodeQueueElem(variable_ptr, variable_vec[0]);
    }

    vector<shared_ptr<ParseNode> > start_vec;
    root_node->addChildrenVec("INTEGER_LITERAL", start_vec);
    if(start_vec.size() > 0){
        listSlice_ptr->set_start(stoi(start_vec[0]->getValue()));
    }

    vector<shared_ptr<ParseNode> > end_vec;
    root_node->addChildrenVec("INTEGER_LITERAL", end_vec);
    if(end_vec.size() > 0){
        listSlice_ptr->set_end(stoi(end_vec[0]->getValue()));
    }

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
    vector<shared_ptr<ParseNode> > node_vec;
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

    vector<shared_ptr<ParseNode> > type_vec;
    root_node->addChildrenVec("nodeTypes", type_vec);
    string type_identifier = "";

    if(!type_vec.empty()){
        vector<shared_ptr<ParseNode> > type_vec_value;
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

    vector<shared_ptr<ParseNode> > node;
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


    vector<shared_ptr<ParseNode> > conditions_expressions;
    root_node->addChildrenVec("conditions", conditions_expressions);
    shared_ptr<ParseNode> conditions_ptr = conditions_expressions[0];
    conditions_ptr->addChildrenVec("conditionStatement", conditions_expressions);

    vector<shared_ptr<ParseNode> > operations_expressions;
    root_node->addChildrenVec("operations", operations_expressions);
    shared_ptr<ParseNode> operations_ptr = operations_expressions[0];
    operations_ptr->addChildrenVec("operationStatement", operations_expressions);


    vector<shared_ptr<ParseNode> > fromNode;
    root_node->addChildrenVec("fromNode", fromNode);
    fromNode[0]->addChildrenVec("IDENTIFIER", fromNode);


    vector<shared_ptr<ParseNode> > toNode;
    root_node->addChildrenVec("toNode", toNode);
    toNode[0]->addChildrenVec("IDENTIFIER", toNode);


    shared_ptr<transitionDefStatements> transitionStatement = dynamic_pointer_cast<transitionDefStatements>(parentAstNode);

    transitionStatement->set_toNode(toNode[0]->getValue());
    transitionStatement->set_fromNode(fromNode[0]->getValue());

    for(auto operation_expression : operations_expressions){

        vector<shared_ptr<ParseNode> > expressions;
        operation_expression->addChildrenVec("expression", expressions);


        if(!expressions.empty()){
            for(auto expression_ptr : expressions){
                shared_ptr<expression> operationNode = shared_ptr<expression>(new expression);
                transitionStatement->add_operationsExpression(operationNode);
                astNodeQueueElem elem = astNodeQueueElem(operationNode, expression_ptr);
                astNodeQueue.push(elem);

            }
        }

    }

    for(auto condition_expression : conditions_expressions){

        vector<shared_ptr<ParseNode> > expressions;
        condition_expression->addChildrenVec("expression", expressions);


        if(!expressions.empty()){
            for(auto expression_ptr : expressions){
                shared_ptr<expression> conditionNode = shared_ptr<expression>(new expression);
                transitionStatement->add_conditionExpression(conditionNode);
                astNodeQueueElem elem = astNodeQueueElem(conditionNode, expression_ptr);
                astNodeQueue.push(elem);

            }
        }

    }

}

shared_ptr<AstNode> AbstractTreeGenerator::explore_term(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue) {
/*
This does not point to any specific ast nodes but return an ast node, while also pushing up to the queue 
This is the rule for a term currently
{"term", {
        CreateRule("listAccess"), // The reason why list access is here is because list access has a variable,and as the parser is greedy it will always try to match the first rule
        CreateOr(),
        CreateRule("listSlice"), // The reason why list access is here is because list access has a variable,and as the parser is greedy it will always try to match the first rule
        CreateOr(),
        CreateRule("variable"), 
        CreateOr(),
        CreateRule("literal"), 
        CreateOr(),
        CreateRule("list"), 
        CreateOr(),
        CreateToken("LEFT_PAREN"),
        CreateRule("expression"),
        CreateToken("RIGHT_PAREN"),

}},

*/

    vector<shared_ptr<ParseNode> > literal_vec;
    vector<shared_ptr<ParseNode> > variable_vec;
    vector<shared_ptr<ParseNode> > expression_vec;
    vector<shared_ptr<ParseNode> > list_vec;
    vector<shared_ptr<ParseNode> > listAccess_vec;
    vector<shared_ptr<ParseNode> > listSlice_vec;

    root_node->addChildrenVec("literal", literal_vec);
    root_node->addChildrenVec("variable", variable_vec);
    root_node->addChildrenVec("expression", expression_vec);
    root_node->addChildrenVec("list", list_vec);
    root_node->addChildrenVec("listAccess", listAccess_vec);
    root_node->addChildrenVec("listSlice", listSlice_vec);

    if (!literal_vec.empty()) {
        vector<shared_ptr<ParseNode> > string_vec;
        vector<shared_ptr<ParseNode> > integer_vec;
        vector<shared_ptr<ParseNode> > char_vec;
        vector<shared_ptr<ParseNode> > bool_literal_vec;
        vector<shared_ptr<ParseNode> > decimal_vec;

        literal_vec[0]->addChildrenVec("STRING_LITERAL", string_vec);
        literal_vec[0]->addChildrenVec("INTEGER_LITERAL", integer_vec);
        literal_vec[0]->addChildrenVec("CHAR_LITERAL", char_vec);
        literal_vec[0]->addChildrenVec("boolLiteral", bool_literal_vec); // Bool is a rule not a token same with decimal
        literal_vec[0]->addChildrenVec("decimalLiteral", decimal_vec); // Decimal literal is a rule not a token

        if (!string_vec.empty()) {
            shared_ptr<stringLiteral> stringNode = make_shared<stringLiteral>();
            stringNode->set_stringLiteral(string_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(stringNode, string_vec[0]));
            return stringNode;
        } else if (!integer_vec.empty()) {
            shared_ptr<integerLiteral> intNode = make_shared<integerLiteral>();
            intNode->set_integerLiteral(integer_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(intNode, integer_vec[0]));
            return intNode;
        } else if (!char_vec.empty()) {
            shared_ptr<charLiteral> charNode = make_shared<charLiteral>();
            charNode->set_charLiteral(char_vec[0]->getValue()[0]);
            astNodeQueue.push(astNodeQueueElem(charNode, char_vec[0]));
            return charNode;
        }
        else if (!bool_literal_vec.empty()) {
            shared_ptr<boolLiteral> boolNode = make_shared<boolLiteral>();
            boolNode->set_boolLiteral(bool_literal_vec[0]->getValue() == "true");
            astNodeQueue.push(astNodeQueueElem(boolNode, bool_literal_vec[0]));
            return boolNode;
        }
        else if (!decimal_vec.empty()) {
            shared_ptr<decimalLiteral> decimalNode = make_shared<decimalLiteral>();
            decimalNode->set_decimalLiteral(decimal_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(decimalNode, decimal_vec[0]));
            return decimalNode;
        }
    }

    if (!variable_vec.empty()) {
        shared_ptr<variable> variableNode = make_shared<variable>();

        vector<shared_ptr<ParseNode> > identifier_vec;
        variable_vec[0]->addChildrenVec("IDENTIFIER", identifier_vec);

        if (!identifier_vec.empty()) {
            variableNode->set_variableName(identifier_vec[0]->getValue());
        }

        astNodeQueue.push(astNodeQueueElem(variableNode, variable_vec[0]));
        return variableNode;
    }

    if(!expression_vec.empty()){
        shared_ptr<expression> expression_ptr = shared_ptr<expression>(new expression);
        astNodeQueueElem elem = astNodeQueueElem(expression_ptr,expression_vec[0]);
        astNodeQueue.push(elem);

        return expression_ptr;
    }
    if(!list_vec.empty()){
        shared_ptr<list> list_ptr = shared_ptr<list>(new list);
        astNodeQueueElem elem = astNodeQueueElem(list_ptr,list_vec[0]);
        astNodeQueue.push(elem);

        return list_ptr;
    }
    if(!listAccess_vec.empty()){
        shared_ptr<listAccess> listAccess_ptr = shared_ptr<listAccess>(new listAccess);
        astNodeQueueElem elem = astNodeQueueElem(listAccess_ptr,listAccess_vec[0]);
        astNodeQueue.push(elem);

        return listAccess_ptr;
    }
    if(!listSlice_vec.empty()){
        shared_ptr<listSlice> listSlice_ptr = shared_ptr<listSlice>(new listSlice);
        astNodeQueueElem elem = astNodeQueueElem(listSlice_ptr,listSlice_vec[0]);
        astNodeQueue.push(elem);
        return listSlice_ptr;
    }


}
shared_ptr<AstNode> AbstractTreeGenerator::explore_first_class(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue) {// Very similar to term
/*
This does not point to any specific ast nodes but return an ast node, while also pushing up to the queue 
This is the rule for a term currently
    {"firstClass", {
        CreateRule("listAccess"), // The difference between this and the term rule is that there is no expression here, these are all the first class citizens
        CreateOr(),
        CreateRule("listSlice"), 
        CreateOr(),
        CreateRule("variable"), 
        CreateOr(),
        CreateRule("literal"), 
        CreateOr(),
        CreateRule("list"), 
    }},


*/

    vector<shared_ptr<ParseNode> > literal_vec;
    vector<shared_ptr<ParseNode> > variable_vec;
    vector<shared_ptr<ParseNode> > list_vec;
    vector<shared_ptr<ParseNode> > listAccess_vec;
    vector<shared_ptr<ParseNode> > listSlice_vec;

    root_node->addChildrenVec("literal", literal_vec);
    root_node->addChildrenVec("variable", variable_vec);
    root_node->addChildrenVec("list", list_vec);
    root_node->addChildrenVec("listAccess", listAccess_vec);
    root_node->addChildrenVec("listSlice", listSlice_vec);

    if (!literal_vec.empty()) {
        vector<shared_ptr<ParseNode> > string_vec;
        vector<shared_ptr<ParseNode> > integer_vec;
        vector<shared_ptr<ParseNode> > char_vec;
        vector<shared_ptr<ParseNode> > bool_literal_vec;
        vector<shared_ptr<ParseNode> > decimal_vec;

        literal_vec[0]->addChildrenVec("STRING_LITERAL", string_vec);
        literal_vec[0]->addChildrenVec("INTEGER_LITERAL", integer_vec);
        literal_vec[0]->addChildrenVec("CHAR_LITERAL", char_vec);
        literal_vec[0]->addChildrenVec("boolLiteral", bool_literal_vec); // Bool is a rule not a token same with decimal
        literal_vec[0]->addChildrenVec("decimalLiteral", decimal_vec); // Decimal literal is a rule not a token

        if (!string_vec.empty()) {
            shared_ptr<stringLiteral> stringNode = make_shared<stringLiteral>();
            stringNode->set_stringLiteral(string_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(stringNode, string_vec[0]));
            return stringNode;
        } else if (!integer_vec.empty()) {
            shared_ptr<integerLiteral> intNode = make_shared<integerLiteral>();
            intNode->set_integerLiteral(integer_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(intNode, integer_vec[0]));
            return intNode;
        } else if (!char_vec.empty()) {
            shared_ptr<charLiteral> charNode = make_shared<charLiteral>();
            charNode->set_charLiteral(char_vec[0]->getValue()[0]);
            astNodeQueue.push(astNodeQueueElem(charNode, char_vec[0]));
            return charNode;
        }
        else if (!bool_literal_vec.empty()) {
            shared_ptr<boolLiteral> boolNode = make_shared<boolLiteral>();
            boolNode->set_boolLiteral(bool_literal_vec[0]->getValue() == "true");
            astNodeQueue.push(astNodeQueueElem(boolNode, bool_literal_vec[0]));
            return boolNode;
        }
        else if (!decimal_vec.empty()) {
            shared_ptr<decimalLiteral> decimalNode = make_shared<decimalLiteral>();
            decimalNode->set_decimalLiteral(decimal_vec[0]->getValue());
            astNodeQueue.push(astNodeQueueElem(decimalNode, decimal_vec[0]));
            return decimalNode;
        }
    }

    if (!variable_vec.empty()) {
        shared_ptr<variable> variableNode = make_shared<variable>();

        vector<shared_ptr<ParseNode> > identifier_vec;
        variable_vec[0]->addChildrenVec("IDENTIFIER", identifier_vec);

        if (!identifier_vec.empty()) {
            variableNode->set_variableName(identifier_vec[0]->getValue());
        }

        astNodeQueue.push(astNodeQueueElem(variableNode, variable_vec[0]));
        return variableNode;
    }

    if(!list_vec.empty()){
        shared_ptr<list> list_ptr = shared_ptr<list>(new list);
        astNodeQueueElem elem = astNodeQueueElem(list_ptr,list_vec[0]);
        astNodeQueue.push(elem);

        return list_ptr;
    }
    if(!listAccess_vec.empty()){
        shared_ptr<listAccess> listAccess_ptr = shared_ptr<listAccess>(new listAccess);
        astNodeQueueElem elem = astNodeQueueElem(listAccess_ptr,listAccess_vec[0]);
        astNodeQueue.push(elem);

        return listAccess_ptr;
    }
    if(!listSlice_vec.empty()){
        shared_ptr<listSlice> listSlice_ptr = shared_ptr<listSlice>(new listSlice);
        astNodeQueueElem elem = astNodeQueueElem(listSlice_ptr,listSlice_vec[0]);
        astNodeQueue.push(elem);
        return listSlice_ptr;
    }


}

shared_ptr<AstNode> AbstractTreeGenerator::recursive_expression_explorer(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue, string current_level) {

    cout<<"Top level"<<endl;
    if(current_level == "prec0"){
        cout<<"prec0"<<endl;

        if(root_node->findChildren("unary_operators").size()>0){
            // We only have on unary operator for now
            shared_ptr<unaryExpression> unaryNode = shared_ptr<unaryExpression>(new unaryExpression);
            unaryNode->set_operation("!");
            shared_ptr<AstNode> node;
            node = explore_term(root_node->findChildren("term")[0], astNodeQueue);
            unaryNode->set_operand(node);
            return unaryNode;

        }
        else{

        // In this case there is no expresion so must be a term
            shared_ptr<AstNode> node;
            node = explore_term(root_node->findChildren("term")[0], astNodeQueue);
            return node;

        }

    } else if(current_level == "prec1") {
            cout<<"prec1"<<endl;

        if (root_node->findChildren("term").size() == 0  && root_node->findChildren("prec1").size() == 0 ){
            return recursive_expression_explorer(root_node->findChildren("prec0")[0], astNodeQueue, "prec0" );
        }

        vector<shared_ptr<ParseNode> > terms = root_node->findChildren("term");
        vector<shared_ptr<ParseNode> > binary_operations = root_node->findChildren("bin1");

        // We will add the binary operators here
        if(terms.size() == 0){
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            if(root_node->findChildren("prec0").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec0")[0], astNodeQueue, "prec0"));

            }
            if(root_node->findChildren("prec1").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_leftSide(recursive_expression_explorer(root_node->findChildren("prec1")[0], astNodeQueue, "prec1"));

            }
            return binaryNode;
        }
        if(terms.size() == 1){
            // Create an AST binary node and connect it with the recursively generated node 

            shared_ptr<AstNode> term = explore_term(terms[0], astNodeQueue);
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(term);
            if(root_node->findChildren("prec0").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec0")[0], astNodeQueue, "prec0"));

            }
            else{
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec1")[0], astNodeQueue, "prec1"));
            }
            return binaryNode; // return the binary node
        }
        else{
            /* The only difference here is we are iteratively chaining up 
                ast subtrees
            */
           
            shared_ptr<AstNode> firstTerm = explore_term(terms[0], astNodeQueue);
            shared_ptr<AstNode> secondTerm = explore_term(terms[1], astNodeQueue);

            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(firstTerm);
            binaryNode->set_rightSide(secondTerm);
            
            shared_ptr<binaryExpression> chainedBinaryPointer;
                cout<<"term "<<terms.size()<<endl;

            for(int i = 2; i < terms.size(); i++){
                shared_ptr<AstNode> tempTerm = explore_term(terms[i], astNodeQueue);

                chainedBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);
                
                chainedBinaryPointer->set_operation(binary_operations[i - 1]->find_only_child()[0]->getValue());

                chainedBinaryPointer->set_leftSide(binaryNode);
                chainedBinaryPointer->set_rightSide(tempTerm); 
                binaryNode = chainedBinaryPointer;
            }
            if(terms.size() == 2){
                chainedBinaryPointer = binaryNode; //For loop did not loop in this case
            }
            vector<shared_ptr<ParseNode> > prec0 = root_node->findChildren("prec0"); 
            vector<shared_ptr<ParseNode> > prec1 = root_node->findChildren("prec1");
            if(prec0.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[binary_operations.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec0[0], astNodeQueue, "prec0")); 
                return finalBinaryPointer;
            }
            else if(prec1.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[binary_operations.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec1[0], astNodeQueue, "prec1")); 
                return finalBinaryPointer;
            }
            else{
                return chainedBinaryPointer; // Case where no other precedence levels are explored
            }
        }

    } else if(current_level == "prec2") {
            cout<<"prec2"<<endl;

        if (root_node->findChildren("term").size() == 0 && root_node->findChildren("prec2").size() == 0 ){
            // Changed recursion target from higher precedence to lower precedence
            return recursive_expression_explorer(root_node->findChildren("prec1")[0], astNodeQueue, "prec1" );
        }

        vector<shared_ptr<ParseNode> > terms = root_node->findChildren("term");
        vector<shared_ptr<ParseNode> > binary_operations = root_node->findChildren("bin2");

        // We will add the binary operators here
        if(terms.size() == 0){
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            if(root_node->findChildren("prec1").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec1")[0], astNodeQueue, "prec1"));

            }
            if(root_node->findChildren("prec2").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_leftSide(recursive_expression_explorer(root_node->findChildren("prec2")[0], astNodeQueue, "prec2"));

            }
            return binaryNode;
        }
        if(terms.size() == 1){
            // Create an AST binary node and connect it with the recursively generated node 

            shared_ptr<AstNode> term = explore_term(terms[0], astNodeQueue);
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(term);
            if(root_node->findChildren("prec1").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec1")[0], astNodeQueue, "prec1"));

            }
            else{
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec2")[0], astNodeQueue, "prec2")); // Ensure recursion to lower precedence
            }

            return binaryNode; // return the binary node
        }
        else{
            /* The only difference here is we are iteratively chaining up 
                ast subtrees
            */
           
            shared_ptr<AstNode> firstTerm = explore_term(terms[0], astNodeQueue);
            shared_ptr<AstNode> secondTerm = explore_term(terms[1], astNodeQueue);

            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(firstTerm);
            binaryNode->set_rightSide(secondTerm);
            
            shared_ptr<binaryExpression> chainedBinaryPointer;

            for(int i = 2; i < terms.size(); i++){
                shared_ptr<AstNode> tempTerm = explore_term(terms[i], astNodeQueue);

                chainedBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);
                chainedBinaryPointer->set_operation(binary_operations[i - 1]->find_only_child()[0]->getValue());

                chainedBinaryPointer->set_leftSide(binaryNode);
                chainedBinaryPointer->set_rightSide(tempTerm); 
                binaryNode = chainedBinaryPointer;
            }
            if(terms.size() == 2){
                chainedBinaryPointer = binaryNode;
            }
            vector<shared_ptr<ParseNode> > prec2 = root_node->findChildren("prec2"); // Changed to "prec1" to "prec2"
            vector<shared_ptr<ParseNode> > prec1 = root_node->findChildren("prec1"); // Changed to "prec2" to "prec1"
            if(prec1.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[terms.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec1[0], astNodeQueue, "prec1")); // Changed from "prec1" to "prec2"
                return finalBinaryPointer;
            }
            else if(prec2.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[terms.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec2[0], astNodeQueue, "prec2")); // Changed from "prec2" to "prec1"
                return finalBinaryPointer;
            }
            else{
                return chainedBinaryPointer; // Case where no other precedence levels are explored
            }
        }

    } else if(current_level == "prec3") {
            cout<<"prec3"<<endl;

        if (root_node->findChildren("term").size() == 0  && root_node->findChildren("prec3").size() == 0 ){
            // Changed recursion target from higher precedence to lower precedence
            return recursive_expression_explorer(root_node->findChildren("prec2")[0], astNodeQueue, "prec2" );
        }

        vector<shared_ptr<ParseNode> > terms = root_node->findChildren("term");
        vector<shared_ptr<ParseNode> > binary_operations = root_node->findChildren("bin3");

        // We will add the binary operators here
        if(terms.size() == 0){
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            if(root_node->findChildren("prec2").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec2")[0], astNodeQueue, "prec2"));

            }
            if(root_node->findChildren("prec3").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_leftSide(recursive_expression_explorer(root_node->findChildren("prec3")[0], astNodeQueue, "prec3"));

            }
            return binaryNode;
        }
        if(terms.size() == 1){
            // Create an AST binary node and connect it with the recursively generated node 

            shared_ptr<AstNode> term = explore_term(terms[0], astNodeQueue);
            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(term);
            if(root_node->findChildren("prec2").size() > 0){// Changed recursion target from higher to lower precedence
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec2")[0], astNodeQueue, "prec2"));

            }
            else{
                binaryNode->set_rightSide(recursive_expression_explorer(root_node->findChildren("prec3")[0], astNodeQueue, "prec3")); // Ensure recursion to lower precedence
            }

            return binaryNode; // return the binary node
        }
        else{
            /* The only difference here is we are iteratively chaining up 
                ast subtrees
            */
           
            shared_ptr<AstNode> firstTerm = explore_term(terms[0], astNodeQueue);
            shared_ptr<AstNode> secondTerm = explore_term(terms[1], astNodeQueue);

            shared_ptr<binaryExpression> binaryNode = shared_ptr<binaryExpression>(new binaryExpression);
            binaryNode->set_operation(binary_operations[0]->find_only_child()[0]->getValue()); // Getting the value of the binary operation
            binaryNode->set_leftSide(firstTerm);
            binaryNode->set_rightSide(secondTerm);
            
            shared_ptr<binaryExpression> chainedBinaryPointer;

            for(int i = 2; i < terms.size(); i++){
                shared_ptr<AstNode> tempTerm = explore_term(terms[i], astNodeQueue);

                chainedBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);
                chainedBinaryPointer->set_operation(binary_operations[i - 1]->find_only_child()[0]->getValue());

                chainedBinaryPointer->set_leftSide(binaryNode);
                chainedBinaryPointer->set_rightSide(tempTerm); 
                binaryNode = chainedBinaryPointer;
            }
            if(terms.size() == 0){
                chainedBinaryPointer = binaryNode;
            }
            vector<shared_ptr<ParseNode> > prec2 = root_node->findChildren("prec2"); // Changed to "prec2" to "prec3"
            vector<shared_ptr<ParseNode> > prec3 = root_node->findChildren("prec3"); // Changed to "prec3" to "prec2"
            if(prec2.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[terms.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec2[0], astNodeQueue, "prec2")); // Changed from "prec2" to "prec3"
                return finalBinaryPointer;
            }
            else if(prec3.size() > 0){
                shared_ptr<binaryExpression> finalBinaryPointer = shared_ptr<binaryExpression>(new binaryExpression);

                finalBinaryPointer->set_operation(binary_operations[terms.size() - 1]->find_only_child()[0]->getValue());
                finalBinaryPointer->set_leftSide(chainedBinaryPointer);
                finalBinaryPointer->set_rightSide(recursive_expression_explorer(prec3[0], astNodeQueue, "prec3")); // Changed from "prec3" to "prec2"
                return finalBinaryPointer;
            }
            else{
                return chainedBinaryPointer; // Case where no other precedence levels are explored
            }
        }

    }
}


void AbstractTreeGenerator::explore_expression(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an expression parse node

    Parsing an expression is not a good time, 
    We have multiple precedence levels, 
    literals, variables, etc. 
    So essentially an expression might be a term, binary operation, unary operation or assignment 
    that does mean we will have to write code for all those cases however.

    The idea is to start from precedence level 3 and go to zero 


    So we will check if a precedence has a binary operator if not go down, 
    until either a binary operator or a literal, variable after which we push that on the 
    queue and go out. 

    Precedence 3 level :- This is a flow given there is actually a binary operator here, we will 
    get a term(ie either a variable or literal) iteratively create ast binary ast nodes until 
    the last term, the last term, will usually come from a precedence 2 parse sub tree, so we recursively get the ast 
    node from there. 
    Note while creating the ast nodes iteratively we will connect them left associative, so 
    connect the first two terms together using an expression, then the next term will be connected to the first two binary node using a new binary operation 
    node and so on. 

    Precedence 2 level :- We will do the same exact procedure. 

    Precedence 1 level - Same 

    Precedence 0 level- Here we have a few specific options number 1 being that we have a term, which we 
    will expand to later on to either a variable or literal, or we have a parentheses expression to which we will 
    just create an expression node to link and push the expression on the queue. 
    We also have the potential of having possibly unary operations which we will also have to flag


    Some helpful functions:
    explore term (ParseNodePtr, Queue) returns an ast node for the term. 

    recursive_expression_explorer(Current Parse Node, Queue) returns ast node to link up too 

    findChildren(string child) returns a vector of parse nodes that have this key. 

    */

   vector<shared_ptr<ParseNode> > assignmentChildren = root_node->findChildren("assignment");

   shared_ptr<expression> parent_ptr = dynamic_pointer_cast<expression>(parentAstNode);

   if(assignmentChildren.size() > 0){
        string variable_name = assignmentChildren[0]->findChildren("variable")[0]->findChildren("IDENTIFIER")[0]->getValue();

        shared_ptr<expression> expression_ptr = shared_ptr<expression>(new expression);
        shared_ptr <ParseNode> expression_parse_node= assignmentChildren[0]->findChildren("expression")[0];
        astNodeQueue.push(astNodeQueueElem(expression_ptr, expression_parse_node));

        shared_ptr<assignmentExpression> assignment_ptr = shared_ptr<assignmentExpression>(new assignmentExpression);

        assignment_ptr->set_variableName(variable_name);
        assignment_ptr->set_expression(expression_ptr);
        parent_ptr->set_type("assignment");
        parent_ptr->set_expression(assignment_ptr);

   }
   else{
    // We explore precedence here 
    shared_ptr<AstNode> ast_tree_root = recursive_expression_explorer(root_node->findChildren("prec3")[0], astNodeQueue, "prec3");
    parent_ptr->set_type("other_expression");
    parent_ptr->set_expression(ast_tree_root);



   }
}

void AbstractTreeGenerator::explore_variable(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a variable parse node
    */
    vector<shared_ptr<ParseNode> > identifier_vec;
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
    vector<shared_ptr<ParseNode> > literal_vec;
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
    vector<shared_ptr<ParseNode> > literal_vec;
    root_node->addChildrenVec("INTEGER_LITERAL", literal_vec);

    if (!literal_vec.empty()) {
        string value = literal_vec[0]->getValue();
        shared_ptr<integerLiteral> intNode = dynamic_pointer_cast<integerLiteral>(parentAstNode);
        intNode->set_integerLiteral(value);
    }
}

void AbstractTreeGenerator::explore_charLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a char literal parse node
    */
    vector<shared_ptr<ParseNode> > literal_vec;
    root_node->addChildrenVec("CHAR_LITERAL", literal_vec);

    if (!literal_vec.empty()) {
        char value = literal_vec[0]->getValue()[0]; // Assuming the value is a single character
        shared_ptr<charLiteral> charNode = dynamic_pointer_cast<charLiteral>(parentAstNode);
        charNode->set_charLiteral(value);
    }
}

void AbstractTreeGenerator::explore_decimalLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a decimal literal parse node
    A decimal literal as a two parts integerPart and also a decimalPart
    All we have to do is to get the integer part and the decimal part and set them in the ast node

    The rule can be expressed as 
        {"decimalLiteral", {
            CreateRule("integerPart"),
            CreateToken("DOT"),
            CreateRule("decimalPart"),
        }}
    Where we have an integer part and a decimal part, both are actually integer literals
    */
    vector<shared_ptr<ParseNode> > integerPartRule_vec;
    root_node->addChildrenVec("integerPart", integerPartRule_vec);

    vector<shared_ptr<ParseNode> > decimalPartRule_vec;
    root_node->addChildrenVec("decimalPart", decimalPartRule_vec);

    shared_ptr<decimalLiteral> decimalNode = dynamic_pointer_cast<decimalLiteral>(parentAstNode);

    // First extract the integer part and then the decimal part and combine them to one string 
    string integerPart = "";
    string decimalPart = "";
    if (!integerPartRule_vec.empty() && !decimalPartRule_vec.empty()) {
        // Get the integer part, by getting the integer literal value
        vector<shared_ptr<ParseNode> > integerPartLiteral_vec;
        integerPartRule_vec[0]->addChildrenVec("INTEGER_LITERAL", integerPartLiteral_vec);
        if (!integerPartLiteral_vec.empty()) {
            integerPart = integerPartLiteral_vec[0]->getValue();
        }
        // Get the decimal part, by getting the integer literal value
        vector<shared_ptr<ParseNode> > decimalPartLiteral_vec;
        decimalPartRule_vec[0]->addChildrenVec("INTEGER_LITERAL", decimalPartLiteral_vec);
        if (!decimalPartLiteral_vec.empty()) {
            decimalPart = decimalPartLiteral_vec[0]->getValue();
        }
        // Combine the integer part and the decimal part
        decimalNode->set_decimalLiteral(integerPart + "." + decimalPart);
    }
    else{
        cerr<<"Error in decimal literal"<<endl;
        exit(1);
    }

    

}

void AbstractTreeGenerator :: explore_boolLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a bool literal parse node
    {"boolLiteral", {
        CreateParen('('),
        CreateToken("TRUE"),
        CreateOr(),
        CreateToken("FALSE"),
        CreateParen(')'),
    }},
    */
    vector<shared_ptr<ParseNode> > boolLiteral_vec;
    root_node->addChildrenVec("boolLiteral", boolLiteral_vec);
    if(!boolLiteral_vec.empty()){
        shared_ptr<boolLiteral> boolNode = dynamic_pointer_cast<boolLiteral>(parentAstNode);
        boolNode->set_boolLiteral(boolLiteral_vec[0]->getValue() == "true");
    }
    // We are done here


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
        dotFile << "    node" << currentId << " [label=\"" << node->repr() << "\"]\n";

        if (auto programNode = dynamic_pointer_cast<program>(node)) {
            for (const auto& statement : programNode->get_graphDec()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(statement, nodeId);
            }
        } 
         else if(auto graphDecNode = dynamic_pointer_cast<graphDec>(node)){
            if(auto graph = graphDecNode->getGraphDef()){
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(graph, nodeId);
            }
         }
         else if (auto graphNode = dynamic_pointer_cast<graphDef>(node)) {
            if (auto memory = graphNode->get_memoryDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(memory, nodeId);
            }
            if (auto accept = graphNode->get_afterAccept()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(accept, nodeId);
            }
            if (auto reject = graphNode->get_afterReject()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(reject, nodeId);
            }
            if (auto nodes = graphNode->get_nodeDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(nodes, nodeId);
            }
            if (auto transitions = graphNode->get_transitionDef()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(transitions, nodeId);
            }
        } else if (auto memoryNode = dynamic_pointer_cast<memoryDef>(node)) {
            for (const auto& varDef : memoryNode->get_variableDefinitions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(varDef, nodeId);
            }
        } else if (auto varNode = dynamic_pointer_cast<variableDefintions>(node)) {
            if (auto expr = varNode->get_elem()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(expr, nodeId);
            }
        } else if (auto node_def = dynamic_pointer_cast<nodeDef>(node)) {
            for (const auto& nodeDefStatement : node_def->get_nodeDefStatements()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(nodeDefStatement, nodeId);
            }
        } else if (auto node_def = dynamic_pointer_cast<transitionDef>(node)) {
            for (const auto& transitionDefStatement : node_def->get_transitionDefStatements()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(transitionDefStatement, nodeId);
            }
        } else if (auto express = dynamic_pointer_cast<expression>(node)) {
            if (auto expr = express->get_expression()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(expr, nodeId);
            }
        } else if (auto transitionNode = dynamic_pointer_cast<transitionDefStatements>(node)) {
            for (auto conds : transitionNode->get_conditionExpressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(conds, nodeId);
            }
            for (auto ops : transitionNode->get_operationsExpressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(ops, nodeId);
            }
        } else if (auto afterAcceptNode = dynamic_pointer_cast<afterAcceptDef>(node)) {
            if (auto expr = afterAcceptNode->get_Expressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(expr, nodeId);
            }
        } else if (auto afterRejectNode = dynamic_pointer_cast<afterRejectDef>(node)) {
            if (auto expr = afterRejectNode->get_Expressions()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(expr, nodeId);
            }
        } else if (auto binaryNode = dynamic_pointer_cast<binaryExpression>(node)) {
            if (auto left = binaryNode->get_leftSide()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(left, nodeId);
            }
            if (auto right = binaryNode->get_rightSide()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(right, nodeId);
            }
        } else if (auto unaryNode = dynamic_pointer_cast<unaryExpression>(node)) {
            if (auto operand = unaryNode->get_operand()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(operand, nodeId);
            }
        } else if (auto assignmentNode = dynamic_pointer_cast<assignmentExpression>(node)) {
            if (auto expr = assignmentNode->get_expression()) {
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(expr, nodeId);
            }
        }
        // Exploring a list 
        else if(auto listNode = dynamic_pointer_cast<list>(node)){
            for(auto listElem : listNode->get_list_node()){
                dotFile << "    node" << currentId << " -> node" << nodeId << "\n";
                writeNode(listElem, nodeId);
            }
        }
        else if (auto stringNode = dynamic_pointer_cast<stringLiteral>(node)) {
            // String literals do not have children, just represent the node
        } else if (auto intNode = dynamic_pointer_cast<integerLiteral>(node)) {
            // Integer literals do not have children, just represent the node
        } else if (auto charNode = dynamic_pointer_cast<charLiteral>(node)) {
            // Char literals do not have children, just represent the node
        }
        else if(auto decimalNode = dynamic_pointer_cast<decimalLiteral>(node)){
            // Decimal literals do not have children, just represent the node
        }
        else if(auto boolNode = dynamic_pointer_cast<boolLiteral>(node)){
            // Bool literals do not have children, just represent the node
        }
        else if(auto variableNode = dynamic_pointer_cast<variable>(node)){
            // Variable literals do not have children, just represent the node
        }
    };

    int nodeId = 0;
    writeNode(root, nodeId);

    dotFile << "}";
    dotFile.close();
}
