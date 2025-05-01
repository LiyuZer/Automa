#include <memory>
#include "../parser/parser.h"
#include "ast_node.h"
#include <queue>

#pragma once

struct astNodeQueueElem { // This will have both the AST Node and the Parse Node
    shared_ptr<AstNode> astNodeptr;
    shared_ptr<ParseNode> parseNodeptr;

    astNodeQueueElem(shared_ptr<AstNode> astNodeptr, shared_ptr<ParseNode> parseNodeptr)
        : astNodeptr(astNodeptr), parseNodeptr(parseNodeptr) {}
};

class AbstractTreeGenerator {
public:

    // Main method to generate the Abstract Syntax Tree
    shared_ptr<AstNode> generateTree(shared_ptr<ParseNode> root_node);

    // Exploration methods for different types of nodes
    void explore_parameterDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_transitionDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_variableDefinitions(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_graphDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_nodeDef(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_nodeDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_transitionDefStatements(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_conditions(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_operations(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_expression(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_variable(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_stringLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_integerLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_charLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_decimalLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_boolLiteral(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_afterAccept(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_afterReject(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_list(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_list_slice(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_list_access(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_accept(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    void explore_graphCall(shared_ptr<ParseNode> root_node, shared_ptr<AstNode> parentAstNode, queue<astNodeQueueElem>& astNodeQueue);
    shared_ptr<AstNode> explore_first_class(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue);
    shared_ptr<AstNode> recursive_expression_explorer(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue, string current_level);
    shared_ptr<AstNode> explore_term(shared_ptr<ParseNode> root_node, queue<astNodeQueueElem>& astNodeQueue);
};

