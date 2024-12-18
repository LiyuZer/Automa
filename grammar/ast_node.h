#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <memory>

#pragma once

using namespace std;

class AstNode{
    private :
    string type;

    public:
    AstNode(string type):type(type){}

    virtual string get_type(){// To enable polymorphism bad approach we wil fix later
        return type;
    }

    void set_type(const string& t){
        type = t;
    }
};

class graphDef: public AstNode{
    private :
    shared_ptr<AstNode> memoryDef;
    shared_ptr<AstNode> afterAccept;
    shared_ptr<AstNode> afterReject;
    shared_ptr<AstNode> nodeDef;
    shared_ptr<AstNode> transitionDef; 

    public: 
    graphDef(): AstNode("graphDef"){}

    shared_ptr<AstNode> get_memoryDef(){ return memoryDef; }
    void set_memoryDef(const shared_ptr<AstNode>& mem){ memoryDef = mem; }

    shared_ptr<AstNode> get_afterAccept(){ return afterAccept; }
    void set_afterAccept(const shared_ptr<AstNode>& accept){ afterAccept = accept; }

    shared_ptr<AstNode> get_afterReject(){ return afterReject; }
    void set_afterReject(const shared_ptr<AstNode>& reject){ afterReject = reject; }

    shared_ptr<AstNode> get_nodeDef(){ return nodeDef; }
    void set_nodeDef(const shared_ptr<AstNode>& node){ nodeDef = node; }

    shared_ptr<AstNode> get_transitionDef(){ return transitionDef; }
    void set_transitionDef(const shared_ptr<AstNode>& trans){ transitionDef = trans; }
};

class memoryDef: public AstNode{
    private :
    vector<shared_ptr<AstNode>> variableDefintions;
    public: 
    memoryDef(): AstNode("memoryDef"){}

    vector<shared_ptr<AstNode>> get_variableDefinitions(){ return variableDefintions; }
    void add_variableDefinition(const shared_ptr<AstNode>& varDef){ variableDefintions.push_back(varDef); }
};

class variableDefintions: public AstNode{
    private :
    string variableName;
    shared_ptr<AstNode> expression;
    public: 
    variableDefintions(): AstNode("variableDefintions"){}

    string get_variableName(){ return variableName; }
    void set_variableName(const string& name){ variableName = name; }

    shared_ptr<AstNode> get_expression(){ return expression; }
    void set_expression(const shared_ptr<AstNode>& expr){ expression = expr; }
};

class nodeDef: public AstNode{
    private :
    vector<shared_ptr<AstNode>> nodeDefStatements;
    public: 
    nodeDef(): AstNode("nodeDef"){}

    vector<shared_ptr<AstNode>> get_nodeDefStatements(){ return nodeDefStatements; }
    void add_nodeDefStatement(const shared_ptr<AstNode>& statement){ nodeDefStatements.push_back(statement); }
};

class nodeDefStatements: public AstNode{
    private :
    string node;
    string nodeType;
    public: 
    nodeDefStatements(): AstNode("nodeDefStatements"){}

    string get_node(){ return node; }
    void set_node(const string& n){ node = n; }

    string get_nodeType(){ return nodeType; }
    void set_nodeType(const string& type){ nodeType = type; }
};

class transitionDef: public AstNode{
    private :
    vector<shared_ptr<AstNode>> transitionDefStatements;
    public: 
    transitionDef(): AstNode("transitionDef"){}

    vector<shared_ptr<AstNode>> get_transitionDefStatements(){ return transitionDefStatements; }
    void add_transitionDefStatement(const shared_ptr<AstNode>& statement){ transitionDefStatements.push_back(statement); }
};

class transitionDefStatements: public AstNode{
    private :
    string fromNode;
    string toNode;
    shared_ptr<AstNode> conditions;
    shared_ptr<AstNode> operations;
    public: 
    transitionDefStatements(): AstNode("transitionDefStatements"){}

    string get_fromNode(){ return fromNode; }
    void set_fromNode(const string& from){ fromNode = from; }

    string get_toNode(){ return toNode; }
    void set_toNode(const string& to){ toNode = to; }

    shared_ptr<AstNode> get_conditions(){ return conditions; }
    void set_conditions(const shared_ptr<AstNode>& cond){ conditions = cond; }

    shared_ptr<AstNode> get_operations(){ return operations; }
    void set_operations(const shared_ptr<AstNode>& ops){ operations = ops; }
};

class conditions: public AstNode{
    private :
    vector<shared_ptr<AstNode>> conditionExpressions;
    public: 
    conditions(): AstNode("conditions"){}

    vector<shared_ptr<AstNode>> get_conditionExpressions(){ return conditionExpressions; }
    void add_conditionExpression(const shared_ptr<AstNode>& expr){ conditionExpressions.push_back(expr); }
};

class operations: public AstNode{
    private :
    vector<shared_ptr<AstNode>> operationsExpressions;
    public: 
    operations(): AstNode("operations"){}

    vector<shared_ptr<AstNode>> get_operationsExpressions(){ return operationsExpressions; }
    void add_operationsExpression(const shared_ptr<AstNode>& expr){ operationsExpressions.push_back(expr); }
};

class expression: public AstNode{
    private:
    string type;
    shared_ptr<AstNode> expressionDef;
    public:
    expression(): AstNode("expression"){}

    string get_expressionType(){ return type; }
    void set_expressionType(const string& t){ type = t; }

    shared_ptr<AstNode> get_expression(){ return expressionDef; }
    void set_expression(const shared_ptr<AstNode>& expr){ expressionDef = expr; }
};

class variable: public AstNode{
    private:
    string variable_name;
    public:
    variable(): AstNode("variable"){}

    string get_variableName(){ return variable_name; }
    void set_variableName(const string& name){ variable_name = name; }
};

class stringLiteral: public AstNode{
    private:
    string string_literal;
    public:
    stringLiteral(): AstNode("stringLiteral"){}

    string get_stringLiteral(){ return string_literal; }
    void set_stringLiteral(const string& value){ string_literal = value; }
};

class integerLiteral: public AstNode{
    private:
    long integer_literal;
    public:
    integerLiteral(): AstNode("integerLiteral"){}

    long get_integerLiteral(){ return integer_literal; }
    void set_integerLiteral(long value){ integer_literal = value; }
};

class charLiteral: public AstNode{
    private:
    char char_literal;
    public:
    charLiteral(): AstNode("charLiteral"){}

    char get_charLiteral(){ return char_literal; }
    void set_charLiteral(char value){ char_literal = value; }
};