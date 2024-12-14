#include <iostream>
#include <string>
#include <vector>
#include <memory> // For smart pointers
using namespace std;

class ASTNode{
    private:
    string type;

    public:
    ASTNode(const string& type)
     : type(type){}

     string getType(){
        return type;
     }

};

class GraphDefNode : public ASTNode{
    
    public : 
    shared_ptr<ASTNode> nodeDefinition;
    shared_ptr<ASTNode> transitionDefintion;
    shared_ptr<ASTNode> afterAcceptDefintion;
    shared_ptr<ASTNode> afterRejectDefintion;
    GraphDefNode(const string& type)
     : ASTNode(type){}


};