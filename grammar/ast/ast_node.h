#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <memory>

#pragma once

using namespace std;


class AstNode {
private:
    string type;

public:
    AstNode(string type) : type(type) {}

    virtual string get_type() {
        return type;
    }

    void set_type(const string& t) {
        type = t;
    }

    virtual string repr() {
        return type;
    }
};

class program : public AstNode {
private:
    vector<shared_ptr<AstNode> > graphDec;

public:
    program() : AstNode("program") {}

    void addGraphDec(const shared_ptr<AstNode>& graph) {
        graphDec.push_back(graph);
    }

    vector<shared_ptr<AstNode>> get_graphDec() {// Why are you mixing _ and camelCase? 
        return graphDec;
    }

    string repr() override {
        return "program";
    }
};
class graphDec : public AstNode {
    private:
    shared_ptr<AstNode> graphDef;
    string name;

    public:
    graphDec() : AstNode("graphDec") {}
    void setGraphDef(const shared_ptr<AstNode>& graph) {
        graphDef = graph;
    }
    shared_ptr<AstNode> getGraphDef() {
        return graphDef;
    }
    void setName(const string& n) {
        name = n;
    }
    string getName() {
        return name;
    }
};

class graphDef : public AstNode {
private:
    shared_ptr<AstNode> memoryDef;
    shared_ptr<AstNode> afterAccept;
    shared_ptr<AstNode> afterReject;
    shared_ptr<AstNode> nodeDef;
    shared_ptr<AstNode> transitionDef;

public:
    graphDef() : AstNode("graphDef") {}

    shared_ptr<AstNode> get_memoryDef() { return memoryDef; }
    void set_memoryDef(const shared_ptr<AstNode>& mem) { memoryDef = mem; }

    shared_ptr<AstNode> get_afterAccept() { return afterAccept; }
    void set_afterAccept(const shared_ptr<AstNode>& accept) { afterAccept = accept; }

    shared_ptr<AstNode> get_afterReject() { return afterReject; }
    void set_afterReject(const shared_ptr<AstNode>& reject) { afterReject = reject; }

    shared_ptr<AstNode> get_nodeDef() { return nodeDef; }
    void set_nodeDef(const shared_ptr<AstNode>& node) { nodeDef = node; }

    shared_ptr<AstNode> get_transitionDef() { return transitionDef; }
    void set_transitionDef(const shared_ptr<AstNode>& trans) { transitionDef = trans; }

    string repr() override {
        return "graphDef";
    }
};

class memoryDef : public AstNode {
private:
    vector<shared_ptr<AstNode> > variableDefintions;

public:
    memoryDef() : AstNode("memoryDef") {}

    vector<shared_ptr<AstNode> > get_variableDefinitions() { return variableDefintions; }
    void add_variableDefinition(const shared_ptr<AstNode>& varDef) { variableDefintions.push_back(varDef); }

    string repr() override {
        return "memoryDef";
    }
};

class variableDefintions : public AstNode {
private:
    string variableName;
    shared_ptr<AstNode> elem;// Elem can be a literal or a list

public:
    variableDefintions() : AstNode("variableDefintions") {}

    string get_variableName() { return variableName; }
    void set_variableName(const string& name) { variableName = name; }

    shared_ptr<AstNode> get_elem() { return elem; }
    void set_elem(const shared_ptr<AstNode>& e) { elem = e; }


    string repr() override {
        return "variableDefintions(name=" + variableName + ")";
    }
};

class nodeDef : public AstNode {
private:
    vector<shared_ptr<AstNode> > nodeDefStatements;

public:
    nodeDef() : AstNode("nodeDef") {}

    vector<shared_ptr<AstNode> > get_nodeDefStatements() { return nodeDefStatements; }
    void add_nodeDefStatement(const shared_ptr<AstNode>& statement) { nodeDefStatements.push_back(statement); }

    string repr() override {
        return "nodeDef";
    }
};

class nodeDefStatements : public AstNode {
private:
    string node;
    string nodeType;

public:
    nodeDefStatements() : AstNode("nodeDefStatements") {}

    string get_node() { return node; }
    void set_node(const string& n) { node = n; }

    string get_nodeType() { return nodeType; }
    void set_nodeType(const string& type) { nodeType = type; }

    string repr() override {
        return "nodeDefStatements(node=" + node + ", type=" + nodeType + ")";
    }
};

class transitionDef : public AstNode {
private:
    vector<shared_ptr<AstNode> > transitionDefStatements;

public:
    transitionDef() : AstNode("transitionDef") {}

    vector<shared_ptr<AstNode> > get_transitionDefStatements() { return transitionDefStatements; }
    void add_transitionDefStatement(const shared_ptr<AstNode>& statement) { transitionDefStatements.push_back(statement); }

    string repr() override {
        return "transitionDef";
    }
};

class transitionDefStatements : public AstNode {
private:
    string fromNode;
    string toNode;
    vector<shared_ptr<AstNode> > conditionExpressions;
    vector<shared_ptr<AstNode> > operationsExpressions;

public:
    transitionDefStatements() : AstNode("transitionDefStatements") {}

    string get_fromNode() { return fromNode; }
    void set_fromNode(const string& from) { fromNode = from; }

    string get_toNode() { return toNode; }
    void set_toNode(const string& to) { toNode = to; }

    vector<shared_ptr<AstNode> > get_conditionExpressions() { return conditionExpressions; }
    void add_conditionExpression(const shared_ptr<AstNode>& expr) { conditionExpressions.push_back(expr); }

    vector<shared_ptr<AstNode> > get_operationsExpressions() { return operationsExpressions; }
    void add_operationsExpression(const shared_ptr<AstNode>& expr) { operationsExpressions.push_back(expr); }

    string repr() override {
        return "transitionDefStatements(fromNode=" + fromNode + ", toNode=" + toNode + ")";
    }
};


class afterAcceptDef : public AstNode {
private:
    shared_ptr<AstNode> expression;

public:
    afterAcceptDef() : AstNode("afterAccept") {}

    shared_ptr<AstNode> get_Expressions() { return expression; }
    void add_expression(const shared_ptr<AstNode>& expr) { expression = expr; }

    string repr() override {
        return "afterAccept";
    }
};

class afterRejectDef : public AstNode {
private:
    shared_ptr<AstNode> expression;

public:
    afterRejectDef() : AstNode("afterReject") {}

    shared_ptr<AstNode> get_Expressions() { return expression; }
    void add_expression(const shared_ptr<AstNode>& expr) { expression = expr; }

    string repr() override {
        return "afterReject";
    }
};

class expression : public AstNode {
private:
    string type;
    shared_ptr<AstNode> expressionDef;

public:
    expression() : AstNode("expression") {}

    string get_expressionType() { return type; }
    void set_expressionType(const string& t) { type = t; }

    shared_ptr<AstNode> get_expression() { return expressionDef; }
    void set_expression(const shared_ptr<AstNode>& expr) { expressionDef = expr; }

    string repr() override {
        return "expression(type=" + type + ")";
    }
};

class variable : public AstNode {
private:
    string variable_name;

public:
    variable() : AstNode("variable") {}

    string get_variableName() { return variable_name; }
    void set_variableName(const string& name) { variable_name = name; }

    string repr() override {
        return "variable(name=" + variable_name + ")";
    }
};


class binaryExpression : public AstNode {
private:
    string operation;
    shared_ptr<AstNode> leftSide;
    shared_ptr<AstNode> rightSide;

public:
    binaryExpression() : AstNode("binaryExpression") {}

    string get_operation() { return operation; }
    void set_operation(const string& op) { operation = op; }

    shared_ptr<AstNode> get_leftSide() { return leftSide; }
    void set_leftSide(const shared_ptr<AstNode>& left) { leftSide = left; }

    shared_ptr<AstNode> get_rightSide() { return rightSide; }
    void set_rightSide(const shared_ptr<AstNode>& right) { rightSide = right; }

    string repr() override {
        return "binaryExpression(op=" + operation + ")";
    }
};

class unaryExpression : public AstNode {
private:
    string operation;
    shared_ptr<AstNode> operand;

public:
    unaryExpression() : AstNode("unaryExpression") {}

    string get_operation() { return operation; }
    void set_operation(const string& op) { operation = op; }

    shared_ptr<AstNode> get_operand() { return operand; }
    void set_operand(const shared_ptr<AstNode>& op) { operand = op; }

    string repr() override {
        return "unaryExpression(op=" + operation + ")";
    }
};

class assignmentExpression : public AstNode {
private:
    string variableName;
    shared_ptr<AstNode> expression;

public:
    assignmentExpression() : AstNode("assignmentExpression") {}

    string get_variableName() { return variableName; }
    void set_variableName(const string& name) { variableName = name; }

    shared_ptr<AstNode> get_expression() { return expression; }
    void set_expression(const shared_ptr<AstNode>& expr) { expression = expr; }

    string repr() override {
        return "assignmentExpression(variable=" + variableName + ")";
    }
};

    class list : public AstNode {
    private: 
        vector<shared_ptr<AstNode>> list_node;
        string var_nam;

    public:
        list() : AstNode("list") {}
 
        string repr() override {
            return "list";
        }
        void add_list_node(const shared_ptr<AstNode>& node) { list_node.push_back(node); }
        vector<shared_ptr<AstNode>> get_list_node() { return list_node; }
        void set_var_name(const string& name) { var_nam = name; }
        string get_var_name() { return var_nam; }
    };

class listAccess : public AstNode {
    private:
        int index;
        shared_ptr<AstNode> variable;
    public:
        listAccess() : AstNode("listAccess") {}

        string repr() override {
            return "listAccess + index=" + to_string(index);
        }
        void set_index(const int& idx) { index = idx; }
        int get_index() { return index; }
        void set_variable(const shared_ptr<AstNode>& var) { variable = var; }
        shared_ptr<AstNode> get_variable() { return variable; }
};

class listSlice : public AstNode{
    private:
        int start;
        int end;

    public:
        shared_ptr<AstNode> variable;
        listSlice() : AstNode("listSlice") {}

        string repr() override {
            return "listSlice + start=" + to_string(start) + "end=" + to_string(end);
        }
        void set_start(const int& s) { start = s; }
        int get_start() { return start; }
        void set_end(const int& e) { end = e; }
        int get_end() { return end; }
        void set_variable(const shared_ptr<AstNode>& var) { variable = var; }
        shared_ptr<AstNode> get_variable() { return variable; }
};



class stringLiteral : public AstNode {
private:
    string string_literal;

public:
    stringLiteral() : AstNode("stringLiteral") {}

    string get_stringLiteral() { return string_literal; }
    void set_stringLiteral(const string& value) { string_literal = value; }

    string repr() override {
        return "stringLiteral(value=\"" + string_literal + "\")";
    }
};

class integerLiteral : public AstNode {
private:
    string integer_literal;

public:
    integerLiteral() : AstNode("integerLiteral") {}

    string get_integerLiteral() { return integer_literal; }
    void set_integerLiteral(string value) { integer_literal = value; }

    string repr() override {
        return "integerLiteral(value=" + integer_literal + ")";
    }
};

class decimalLiteral : public AstNode {
    private:
    string decimal_literal;
    public :
    decimalLiteral() : AstNode("decimalLiteral") {}
    string get_decimalLiteral() { return decimal_literal; }
    void set_decimalLiteral(string value) { decimal_literal = value; }
    string repr() override {
        return "decimalLiteral(value=" + decimal_literal + ")";
    }
};
class boolLiteral : public AstNode {
    private:
    bool bool_literal;
    public :
    boolLiteral() : AstNode("boolLiteral") {}
    bool get_boolLiteral() { return bool_literal; }
    void set_boolLiteral(bool value) { bool_literal = value; }
    string repr() override {
        string bool_literal_repr = bool_literal ? "true" : "false";
        return "boolLiteral(value=" + bool_literal_repr + ")";
    }
};
class charLiteral : public AstNode {
private:
    char char_literal;

public:
    charLiteral() : AstNode("charLiteral") {}

    char get_charLiteral() { return char_literal; }
    void set_charLiteral(char value) { char_literal = value; }

    string repr() override {
        return "charLiteral(value='" + string(1, char_literal) + "')";
    }
};

void write_ast_to_dot(const shared_ptr<AstNode>& root, const string& filename);
