#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/aut_obj.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"


shared_ptr<Graph> Operator :: create_graph(shared_ptr<AstNode> graph_defintion){
    /* We must traverse the ast tree and create the graph object
     To do this we will first start from graphDef and then explore :-
        node defintions to create preliminary nodes, and set there types 
        transition defintions to create transitions between nodes
     */
    shared_ptr<graphDef> graphDef_ptr = dynamic_pointer_cast<graphDef>(graph_defintion);
    shared_ptr<Graph> graph_ptr = shared_ptr<Graph>(new Graph);
    //Start with memory defintions 

    // Set the memory template here
    shared_ptr<AstNode> memory = graphDef_ptr->get_parameterDef();
    shared_ptr<memoryDef> paramater_ptr = dynamic_pointer_cast<memoryDef>(memory);
    graph_ptr->set_paramater_def(paramater_ptr);

    //Now we will set the nodes 
    shared_ptr<AstNode> node = graphDef_ptr->get_nodeDef();
    shared_ptr<nodeDef> nodeDef_ptr = dynamic_pointer_cast<nodeDef>(node);
    vector<shared_ptr<AstNode> > node_def_ls = nodeDef_ptr->get_nodeDefStatements();
    for(auto nodeDefStatement : node_def_ls){
        shared_ptr<nodeDefStatements> nodeDefStatement_ptr = dynamic_pointer_cast<nodeDefStatements>(nodeDefStatement);
        string node_name = nodeDefStatement_ptr->get_node();
        string node_type = nodeDefStatement_ptr->get_nodeType();
        Node n = Node(node_name);
        if(node_type == "AC"){
            n.accept = true;
        }
        else if(node_type == "RJ"){
            n.reject = true;
        }
        else if(node_type == "ST"){
            n.start = true;
            graph_ptr->set_start_node(node_name);
        }
        int success = graph_ptr->insert_node(node_name, n);
        if(success == -1){
            cerr << "Error in creating node, node already exists" << endl;
            exit(1);
        }
    }

    //Now we will set the transitions
    shared_ptr<AstNode> transition = graphDef_ptr->get_transitionDef();
    shared_ptr<transitionDef> transitionDef_ptr = dynamic_pointer_cast<transitionDef>(transition);
    vector<shared_ptr<AstNode> > transition_def_ls = transitionDef_ptr->get_transitionDefStatements();
    for(auto transitionDefStatement : transition_def_ls){
        shared_ptr<transitionDefStatements> transitionDefStatement_ptr = dynamic_pointer_cast<transitionDefStatements>(transitionDefStatement);
        string fromNode = transitionDefStatement_ptr->get_fromNode();
        string toNode = transitionDefStatement_ptr->get_toNode();
        shared_ptr<AstNode> conditions = transitionDefStatement_ptr->get_conditionExpression();
        vector<shared_ptr<AstNode> > operations = transitionDefStatement_ptr->get_operationsExpressions();
        graph_ptr->add_transition(fromNode, toNode, conditions, operations);
    }
    //Now we will set the accept node
    shared_ptr<AstNode> accept = graphDef_ptr->get_accept();
    graph_ptr->set_accept(accept);


    graph_ptr->graph_to_dot(*graph_ptr, "graph_sruct.dot");

    /* We are done that is the initialization of the graph
        Recap :-
            We have set the memory defintion
            We have set the node defintions
            We have set the transition defintions
        Note for now the memory definition points to the memory defintion ast node
        and the transitions conditions and operations are still ast nodes. 
        They manifest when the path is executed.
    */

    return graph_ptr;

}

void Operator :: run(){

    while(!path_queue.empty()){
        // Take the first path from the queue
        shared_ptr<Path> path = path_queue.front();
        path_queue.pop();
        // Run the path
    }
}