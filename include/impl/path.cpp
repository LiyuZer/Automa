#include "../core/graph.h"
#include "../core/path.h"
#include <iostream>


using namespace std;
void Path :: add_elem_to_queue(shared_ptr<AstNode> elem){
    // Add the element to the queue, for example if it is a binary expression expand to left and right side
    shared_ptr<queueElement> queue_elem(new queueElement);
    queue_elem->ast_node = elem;
    queue_elem->type = "expression";
    auto nodes = vector<shared_ptr<queueElement>>();
    nodes.push_back(queue_elem);
    // while the current node is not null
    while(!nodes.empty()){
        shared_ptr<queueElement> queue_elem = nodes.back();
        queue_elem->state = EvalState::NotStarted;
        nodes.pop_back();
        // Push the queue element to the queue
        queue->push_back(queue_elem);

        // If the current node is a binary expression, add the left and right side to the queue
        if(dynamic_pointer_cast<binaryExpression>(queue_elem->ast_node)){
            // Set the type 
            queue_elem->type = "binary_expression";
            shared_ptr<binaryExpression> bin_exp = dynamic_pointer_cast<binaryExpression>(queue_elem->ast_node);
            //Create the queue elements for left and right side
            shared_ptr<queueElement> left_elem(new queueElement);
            left_elem->ast_node = bin_exp->get_leftSide();
            // We set the type in the next iteration 
            nodes.push_back(left_elem);
            queue_elem->queue_elem_ptr_ls.push_back(left_elem);

            shared_ptr<queueElement> right_elem(new queueElement);
            right_elem->ast_node = bin_exp->get_rightSide();
            right_elem->parent_index = nodes.size(); // This is the index of binary expression in the queue, note only he right 
            // child has this because when the right child is evaluated, the parent will be evaluated
            // We set the type in the next iteration
            nodes.push_back(right_elem);
            queue_elem->queue_elem_ptr_ls.push_back(right_elem);

        }
        else if (dynamic_pointer_cast<unaryExpression>(queue_elem->ast_node)){
            // Set the type 
            queue_elem->type = "unary_expression";
            shared_ptr<unaryExpression> un_exp = dynamic_pointer_cast<unaryExpression>(queue_elem->ast_node);
            //Create the queue element for the operand
            shared_ptr<queueElement> operand_elem(new queueElement);
            operand_elem->ast_node = un_exp->get_operand();
            operand_elem->parent_index = nodes.size(); // This is the index of unary expression in the queue
            // We set the type in the next iteration
            nodes.push_back(operand_elem);
            queue_elem->queue_elem_ptr_ls.push_back(operand_elem);

        }
        else if (dynamic_pointer_cast<assignmentExpression>(queue_elem->ast_node)){
            // Set the type 
            queue_elem->type = "assignment_expression";
            shared_ptr<assignmentExpression> assign_exp = dynamic_pointer_cast<assignmentExpression>(queue_elem->ast_node);
            //Create the queue element for the expression
            shared_ptr<queueElement> expression_elem(new queueElement);
            expression_elem->ast_node = assign_exp->get_expression();
            expression_elem->parent_index = nodes.size(); // This is the index of assignment expression in the queue
            // We set the type in the next iteration
            nodes.push_back(expression_elem);
            queue_elem->queue_elem_ptr_ls.push_back(expression_elem);
        }
        // Literals
        else if (dynamic_pointer_cast<integerLiteral>(queue_elem->ast_node)){
            queue_elem->type = "integer_literal";
        }
        else if (dynamic_pointer_cast<boolLiteral>(queue_elem->ast_node)){
            queue_elem->type = "bool_literal";
        }
        else if (dynamic_pointer_cast<charLiteral>(queue_elem->ast_node)){
            queue_elem->type = "char_literal";
        }
        else if (dynamic_pointer_cast<stringLiteral>(queue_elem->ast_node)){
            queue_elem->type = "string_literal";
        }
        else if (dynamic_pointer_cast<variable>(queue_elem->ast_node)){
            queue_elem->type = "variable";
        }
        else if (dynamic_pointer_cast<list>(queue_elem->ast_node)){
            queue_elem->type = "list";
        }
        else if (dynamic_pointer_cast<listAccess>(queue_elem->ast_node)){
            queue_elem->type = "list_access";
        }
        else if (dynamic_pointer_cast<listSlice>(queue_elem->ast_node)){
            queue_elem->type = "list_slice";
        }

        else if (dynamic_pointer_cast<expression>(queue_elem->ast_node)){
            queue_elem->type = "expression";
            // In this case we will add the children of the expression to the queue
            shared_ptr<expression> expr = dynamic_pointer_cast<expression>(queue_elem->ast_node);
            shared_ptr<AstNode> child = expr->get_expression();
            // Create a new queue element for the children
            shared_ptr<queueElement> children_elem(new queueElement);
            children_elem->ast_node = child;
            children_elem->parent_index = nodes.size(); // This is the index of expression in the queue
            // We set the type in the next iteration
            nodes.push_back(children_elem);
            queue_elem->queue_elem_ptr_ls.push_back(children_elem);
        }
    }
}
void Path :: initialize_queue(){
    // Initialize the path here 
    vector<transition> transitions = graph_ptr->get_transitions(current_node);
    // Check to see if we have any transitions in the cache 
    // Note key of the cache is current_node + current_transition_index
    string cache_key = current_node + to_string(current_transition_index);
    if(queue_cache.find(cache_key) != queue_cache.end()){
        // We have a cached value
        queue = queue_cache[cache_key];
    }
    else{
        // If we don't have a cached value, we will create a new queueElement
        auto queue = shared_ptr<vector<shared_ptr<queueElement>>>(new vector<shared_ptr<queueElement>>());
        this->queue = queue;

        // Get the conditions and operations for the current transition
        transition t = transitions[current_transition_index];
        queueElement elem;
        elem.type = "transition";
        elem.ast_node = t.condition;
        add_elem_to_queue(t.condition);
        conditions_queue_end = queue->size();
        
        // Add the operations to the queue
        for(auto operation : t.operations){
            queueElement op_elem;
            op_elem.object = make_shared<AutomaObject>("operation");
            op_elem.type = "operation";
            op_elem.ast_node = operation;
            add_elem_to_queue(operation);
        }
    
        // Add the queue to the cache
        queue_cache[cache_key] = queue;
    }
}

shared_ptr<AutomaObject> Path :: evaluate_primitve_expression(shared_ptr<AstNode> ast_node){
    // We will evaluate the pure expression here that are between primitives, ints, chars, bools, etc
    return nullptr;
}
shared_ptr<operatorReturn> Path :: forward_evaluation(){
    // Go from current que index onwards and evaluate the queue elements
    while(current_queue_index < queue->size()){
        // We have three possible states 
        // 1. Not started
        // 2. In progress
        // 3. Done

        // Get the current queue element
        shared_ptr<queueElement> current_elem = (*queue)[current_queue_index];
        if(current_elem->state == EvalState::NotStarted){
        }
        else if(current_elem->state == EvalState::WaitingDependencies){
        }
        else if(current_elem->state == EvalState::Completed){
            // We skip this element
            current_queue_index++;
        }

        // If we have finished the conditions section then check the first first element
        // which is an expression to see if it is pointign to a boolean and that boolean is
        if(current_queue_index == conditions_queue_end){
            shared_ptr<queueElement> condition_elem = queue->at(0);
            // This will always be an expression pointing to something go it its child, check if it is a boolean object 
            // and then if it is true or false
            shared_ptr<AutomaObject> result = condition_elem->queue_elem_ptr_ls[0]->object;
            if(result != nullptr && dynamic_pointer_cast<Bool>(result)){
                shared_ptr<Bool> bool_result = dynamic_pointer_cast<Bool>(result);
                if(bool_result->get_val()){
                    // We can proceed to the next transition
                    current_transition_index++;
                    current_queue_index = 0;
                    return nullptr;
                }
                else{
                    // We cannot proceed to the next transition
                    return nullptr;
                }
            }
            else{
                // We cannot proceed to the next transition
                return nullptr;
            }


            return nullptr;
        }
    }
}
// We will have the run function here 
shared_ptr<operatorReturn> Path :: run(){
    // We will run the path here 

    if (started_transition == false) {
        initialize_queue();
        started_transition = true;
    } 
    cout<< "Running Path" << "path size " << queue->size() << endl;
    // Evaluation time baby!!
    shared_ptr<operatorReturn> result = forward_evaluation();
    
    return nullptr;
}