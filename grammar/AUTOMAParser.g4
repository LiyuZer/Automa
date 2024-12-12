// Define a grammar called AUTOMAParser

parser grammar AUTOMAParser;
options {
    tokenVocab = AUTOMALexer;
}

r: graphDef*;

graphDef: Graph IDENTIFIER LeftBrace graphBody RightBrace;

graphBody: memoryDefinition nodeDefinition transitionDefinition afterAcceptDefinition* afterRejectDefinition*;

memoryDefinition: Memory LeftBrace (IDENTIFIER Colon expression (Comma IDENTIFIER Colon expression)*)? RightBrace;

nodeDefinition: NodeDef LeftBrace (IDENTIFIER DoubleColon nodeDefTypes Semicolon (IDENTIFIER DoubleColon nodeDefTypes Semicolon)*)? RightBrace;


transitionDefinition: Transitions LeftBrace transition+ RightBrace;

transition: firstNode secondNode ArrowEquals  Conditions Colon tupleType Comma Operations Colon tupleType Semicolon;

firstNode: IDENTIFIER;

secondNode: IDENTIFIER;

expression
    : (Not)* booleanExpression
    ;

booleanExpression
    : arithmeticExpression (boolOperator arithmeticExpression)*
    ;

arithmeticExpression
    : term ((Plus | Minus) term)*
    ;

term
    : factor ((Star | Div) factor)*
    ;

factor
    : LeftParen expression RightParen
    | expressionAtom
    ;

expressionAtom
    : graphCall
    | var
    | literals
    | dataTypes
    ;


dataTypes : memoryType | tupleType | listType; 

memoryType: LeftBrace (IDENTIFIER Colon expression (Comma IDENTIFIER Colon expression)*)? RightBrace;

tupleType: LeftParen (expression (Comma expression)*)* RightParen;

listType: LeftBracket (expression (Comma expression)*)* RightBracket;


nodeDefTypes : StartNode | AcceptNode| RejectNode; 


graphCall: IDENTIFIER tupleType ;

afterAcceptDefinition: AfterAccept LeftBrace (expression Semicolon)* RightBrace;

afterRejectDefinition: AfterReject LeftBrace (expression Semicolon)* RightBrace;

arithmeticOperator: Plus | Div | Minus | Star;




boolOperator: And | Or | Equal;

literals: booleanLiteral | charLiteral | stringLiteral | integerLiteral;

var: IDENTIFIER;


booleanLiteral : BooleanLiteral;
stringLiteral : StringLiteral;
charLiteral :  CharLiteral;
integerLiteral : IntegerLiteral;
digit : Digit;

