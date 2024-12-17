#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <memory>

using namespace std;
class ParseNode {
    private:
    string type;
    string value;
    std::unordered_map<std::string, std::vector<shared_ptr<ParseNode>>> children;
    public:
        ParseNode(string type, string value) : type(type), value(value){}
        void addChildren(string next_node_type, shared_ptr<ParseNode> next_node){
            if(children.find(next_node_type) != children.end()){
                children[next_node_type].push_back(next_node);
            }
            else{
                children[next_node_type] = {next_node};
            }
            
        }
};