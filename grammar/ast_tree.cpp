#include <memory>
#include <queue>
#include "ast_tree.h"
#include "parser.h"
#include "ast_node.h"


shared_ptr<AstNode> AbstractTreeGenerator :: generateTree(shared_ptr<ParseNode> root_node){

    queue<astNodeQueueElem> astNodeQueue;
    string type = root_node->getType(); 

    if(type != "program"){
        cerr << "Error program parse node is not declared, fix grammar" << endl;
        return nullptr;
    }

    vector<shared_ptr<ParseNode>> children;
    bool found = root_node->addChildrenVec("program", children);

    root_node = children[0];// For now we will assume there are no other graph definitions

    if(!found){
       cerr << "Error program parse node is not initialized properly, fix grammar" << endl; 
       return nullptr;
    }

    shared_ptr<graphDef> graph_def_ptr = shared_ptr<graphDef>(new graphDef);


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
        shared_ptr<nodeDef> afterAccept_ptr = shared_ptr<nodeDef>(new nodeDef);
        graph_def_ptr->set_afterAccept(afterAccept_ptr);
        astNodeQueueElem elem = astNodeQueueElem(afterAccept_ptr,node_vec[0]);
        astNodeQueue.push(elem);
    }

    root_node->addChildrenVec("afterReject", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<nodeDef> afterReject_ptr = shared_ptr<nodeDef>(new nodeDef);
        graph_def_ptr->set_afterReject(afterReject_ptr);
        astNodeQueueElem elem = astNodeQueueElem(afterReject_ptr,node_vec[0]);
        astNodeQueue.push(elem);
        }

    root_node->addChildrenVec("memoryDef", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<nodeDef> memoryDef_ptr = shared_ptr<nodeDef>(new nodeDef);
        graph_def_ptr->set_afterReject(memoryDef_ptr);
        astNodeQueueElem elem = astNodeQueueElem(memoryDef_ptr,node_vec[0]);
        astNodeQueue.push(elem);
        }

    root_node->addChildrenVec("transitionDef", node_vec);
    if(node_vec.size() > 0){
        shared_ptr<nodeDef> transitionDef_ptr = shared_ptr<nodeDef>(new nodeDef);
        graph_def_ptr->set_afterReject(transitionDef_ptr);
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
       else if(type == "transitionDef"){
        
       }
       else if(type == "transitionDef"){
        
       }
       else if(type == "transitionDef"){
        
       }
       else if(type == "transitionDef"){
        
       }
       astNodeQueue.pop();

    }
    
    return nullptr;
}



void AbstractTreeGenerator:: explore_memoryDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue){
    /*
    Here we are exploring a memory def parse node
    */
    vector<shared_ptr<ParseNode>> node_vec;
    root_node->addChildrenVec("tupleItems", node_vec);
    shared_ptr<memoryDef> special_symbol = dynamic_pointer_cast<memoryDef>(parentAstNode);
    if(node_vec.size() > 0){
        for(auto node : node_vec){
            shared_ptr<variableDefintions> variable_definiton_ptr = shared_ptr<variableDefintions>(new variableDefintions);
            special_symbol->add_variableDefinition(variable_definiton_ptr); 
            astNodeQueueElem elem = astNodeQueueElem(variable_definiton_ptr, node);
            astNodeQueue.push(elem);
        }
    }

}
void AbstractTreeGenerator::explore_transitionDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a transition definition parse node
    */
}

void AbstractTreeGenerator::explore_variableDefinitions(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a variable definitions parse node
    */
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
}

void AbstractTreeGenerator::explore_nodeDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring node definition statements parse node
    */
}

void AbstractTreeGenerator::explore_transitionDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring transition definition statements parse node
    */
}

void AbstractTreeGenerator::explore_conditions(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a conditions parse node
    */
}

void AbstractTreeGenerator::explore_operations(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an operations parse node
    */
}

void AbstractTreeGenerator::explore_expression(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an expression parse node
    */
}

void AbstractTreeGenerator::explore_variable(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a variable parse node
    */
}

void AbstractTreeGenerator::explore_stringLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a string literal parse node
    */
}

void AbstractTreeGenerator::explore_integerLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring an integer literal parse node
    */
}

void AbstractTreeGenerator::explore_charLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue) {
    /*
    Here we are exploring a char literal parse node
    */
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
