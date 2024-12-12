// Define a grammar called automa


parser grammar AUTOMAParser;
options {
    tokenVocab = AUTOMALexer;
}



r  : graphDef*;

graphDef : Graph IDENTIFIER  LeftBrace graphBody RightBrace;

graphBody: memoryDefinition nodeDefinition transitionDefinition afterAcceptDefinition, afterRejectDefinition; 

memoryDefinition : Memory LeftBrace --- RightBrace;

nodeDefinition: NodeDef LeftBrace (IDENTIFIER DoubleColon NodeDefTypes)* RightBrace;

transitionDefinition : Transition LeftBrace  RightBrace; 

expression : LeftParen expression RightParen | expressionAtom;

expressionAtom: graphCall | arithmeticOperation | var;

graphCall : IDENTIFIER LeftParen  ;


arithmeticOperation : expression arithmeticOperator expression;

arithmeticOperator : Plus | Div | Minus | Star;

var : 
