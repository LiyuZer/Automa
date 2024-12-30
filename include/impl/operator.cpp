#include <memory>
#include "../core/operator.h"
#include "../core/path.h"
#include "../core/memory.h"
#include "../core/graph.h"
#include "../../grammar/ast/ast_node.h"

void Operator :: run(){
/*


*/
}

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
    shared_ptr<AstNode> memory = graphDef_ptr->get_memoryDef();
    shared_ptr<memoryDef> memoryDef_ptr = dynamic_pointer_cast<memoryDef>(memory);
    graph_ptr->set_memory_def(memoryDef_ptr);

    //Now we will set the nodes 
    shared_ptr<AstNode> node = graphDef_ptr->get_nodeDef();
    shared_ptr<nodeDef> nodeDef_ptr = dynamic_pointer_cast<nodeDef>(node);
    vector<shared_ptr<AstNode> > nodeDefStatements = nodeDef_ptr->get_nodeDefStatements();
    for(auto nodeDefStatement : nodeDefStatements){
        shared_ptr<nodeDefStatements> nodeDefStatement_ptr = dynamic_pointer_cast<nodeDefStatements>(nodeDefStatement);
        string node_name = nodeDefStatement_ptr->get_node();
        string node_type = nodeDefStatement_ptr->get_nodeType();
        Node n = Node(node_name);
        if(node_type == "accept"){
            n.accept = true;
        }
        else if(node_type == "reject"){
            n.reject = true;
        }
        else if(node_type == "start"){
            n.start = true;
        }
        graph_ptr->insert_node(node_name, n);
    }

    //Now we will set the transitions
    shared_ptr<AstNode> transition = graphDef_ptr->get_transitionDef();
    shared_ptr<transitionDef> transitionDef_ptr = dynamic_pointer_cast<transitionDef>(transition);
    vector<shared_ptr<AstNode> > transitionDefStatements = transitionDef_ptr->get_transitionDefStatements();
    for(auto transitionDefStatement : transitionDefStatements){
        shared_ptr<transitionDefStatements> transitionDefStatement_ptr = dynamic_pointer_cast<transitionDefStatements>(transitionDefStatement);
        string fromNode = transitionDefStatement_ptr->get_fromNode();
        string toNode = transitionDefStatement_ptr->get_toNode();
        vector<shared_ptr<AstNode> > conditions = transitionDefStatement_ptr->get_conditions();
        vector<shared_ptr<AstNode> > operations = transitionDefStatement_ptr->get_operations();
        graph_ptr->add_transition(fromNode, toNode, conditions, operations);
    }

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