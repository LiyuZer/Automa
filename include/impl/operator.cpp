// #include <memory>
// #include "../core/operator.h"
// #include "../core/path.h"
// #include "../core/memory.h"
// #include "../core/graph.h"
// #include "../../grammar/ast/ast_node.h"


// shared_ptr<Graph> Operator :: create_graph(shared_ptr<AstNode> graph_defintion){
//     /* We must traverse the ast tree and create the graph object
//      To do this we will first start from graphDef and then explore :-
//         node defintions to create preliminary nodes, and set there types 
//         transition defintions to create transitions between nodes
//      */
//     shared_ptr<graphDef> graphDef_ptr = dynamic_pointer_cast<graphDef>(graph_defintion);
//     shared_ptr<Graph> graph_ptr = shared_ptr<Graph>(new Graph);
//     //Start with memory defintions 

//     // Set the memory template here
//     shared_ptr<AstNode> memory = graphDef_ptr->get_parameterDef();
//     shared_ptr<
//     graph_ptr->set_memory_def(paramater_ptr);

//     //Now we will set the nodes 
//     shared_ptr<AstNode> node = graphDef_ptr->get_nodeDef();
//     shared_ptr<nodeDef> nodeDef_ptr = dynamic_pointer_cast<nodeDef>(node);
//     vector<shared_ptr<AstNode> > node_def_ls = nodeDef_ptr->get_nodeDefStatements();
//     for(auto nodeDefStatement : node_def_ls){
//         shared_ptr<nodeDefStatements> nodeDefStatement_ptr = dynamic_pointer_cast<nodeDefStatements>(nodeDefStatement);
//         string node_name = nodeDefStatement_ptr->get_node();
//         string node_type = nodeDefStatement_ptr->get_nodeType();
//         Node n = Node(node_name);
//         if(node_type == "acceptNode"){
//             n.accept = true;
//         }
//         else if(node_type == "rejectNode"){
//             n.reject = true;
//         }
//         else if(node_type == "startNode"){
//             n.start = true;
//             graph_ptr->set_start_node(node_name);
//         }
//         int success = graph_ptr->insert_node(node_name, n);
//         if(success == -1){
//             cerr << "Error in creating node, node already exists" << endl;
//             exit(1);
//         }
//     }

//     //Now we will set the transitions
//     shared_ptr<AstNode> transition = graphDef_ptr->get_transitionDef();
//     shared_ptr<transitionDef> transitionDef_ptr = dynamic_pointer_cast<transitionDef>(transition);
//     vector<shared_ptr<AstNode> > transition_def_ls = transitionDef_ptr->get_transitionDefStatements();
//     for(auto transitionDefStatement : transition_def_ls){
//         shared_ptr<transitionDefStatements> transitionDefStatement_ptr = dynamic_pointer_cast<transitionDefStatements>(transitionDefStatement);
//         string fromNode = transitionDefStatement_ptr->get_fromNode();
//         string toNode = transitionDefStatement_ptr->get_toNode();
//         vector<shared_ptr<AstNode> > conditions = transitionDefStatement_ptr->get_conditionExpressions();
//         vector<shared_ptr<AstNode> > operations = transitionDefStatement_ptr->get_operationsExpressions();
//         graph_ptr->add_transition(fromNode, toNode, conditions, operations);
//     }
//     //Now we will set the accept node
//     shared_ptr<AstNode> accept = graphDef_ptr->get_accept();
//     graph_ptr->set_accept(accept);


//     graph_ptr->graph_to_dot(*graph_ptr, "graph_sruct.dot");

//     /* We are done that is the initialization of the graph
//         Recap :-
//             We have set the memory defintion
//             We have set the node defintions
//             We have set the transition defintions
//         Note for now the memory definition points to the memory defintion ast node
//         and the transitions conditions and operations are still ast nodes. 
//         They manifest when the path is executed.
//     */

//     return graph_ptr;

// }

// void Operator :: run(){

//     while(!path_queue.empty()){
        
//         current_path = path_queue.front();
//         path_queue.pop();
//         // Now we will run the path
//         shared_ptr<operatorReturn> result = current_path->run();
//         // If the result is not null, then we will add the path to the pending queue
//         if(result->status == 0){
//             path_pending_queue[current_path->get_id()] = current_path;
//             // Now take the result and add the path to the operator
//             shared_ptr<Graph> graph = get_graph(result->graph_name);
//             path_id++;
//             shared_ptr<Path> path = shared_ptr<Path>(new Path(path_id, graph->get_start_node(), 1000000, 0, graph, current_path->get_id()));
//             //Set the arguments for the path 
//             path->addArgument(result->memory_containers, graph);
//             //Push path to the main queue
//             path_queue.push(path);
//         }
//         else{
//             // If the status is 1, then we will take the memory container and return it
//             shared_ptr<Memory> memory = result->memory_containers[0];
//             cout<<current_path->get_id_to_return()<< endl;
//             // Get the path from the pending queue if the path id is not 0(0 case is for the root path)
//             if(current_path->get_id_to_return() != -1){
//                 shared_ptr<Path> path = path_pending_queue[current_path->get_id_to_return()];
//                 path->update_computation_stack(memory);
//                 path_pending_queue.erase(current_path->get_id_to_return());
//                 // Now we will add the path back to the queue
//                 path_queue.push(path);
//             }
//         }
        
//     }


// }