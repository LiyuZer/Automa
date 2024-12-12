
lexer grammar AUTOMALexer;

/* Here we will define the lexer symbols, the grammer of Automa
is very similar to C++ and C, except of course no while, if statments,
for loops, switches etc. Everything is handled by transitions, which means less
keywords yay! Also bulkier code ;)
 */


/*Keywords here*/
Operator : 'operator' ;

Transitions : 'transitions' ;

Graph : 'graph';

Memory : 'memory';

AfterReject : 'afterReject';

AfterAccept : 'afterAccept';

Symbols : 'symbols';

Array : 'array';

Dict : 'dict';

Tuple : 'tuple';

Conditions : 'conditions';

Operations : 'operations';

None : 'None';

NodeDef : 'nodeDef';


StartNode : 'startNode';

AcceptNode : 'acceptNode';

RejectNode : 'rejectNode';



/* Taken from the C++ Lexer on https://github.com/antlr/grammars-v4/blob/master/cpp/CPP14Lexer.g4  */

Arrow : '->';

ArrowEquals : '=>';


LeftParen: '(';

RightParen: ')';

LeftBracket: '[';

RightBracket: ']';

LeftBrace: '{';

RightBrace: '}';

Plus: '+';

Minus: '-';

Star: '*';

Div: '/';

Mod: '%';

And: '&&' |  'and';

Or: '||' | 'or';


Tilde: '~';

Not: '!' | 'not';

Assign: '=';

Less: '<';

Greater: '>';


Equal: '==';

NotEqual: '!=';

LessEqual: '<=';

GreaterEqual: '>=';

Semicolon : ';';

DoubleColon : '::';

Colon : ':';

Comma : ',';


/* Building Blocks of Literals*/







BooleanLiteral : 'true' | 'false';
StringLiteral : '"'[0-9a-zA-Z]*'"';
CharLiteral :  '\'' [0-9a-zA-Z] '\'';           
IntegerLiteral : Digit+;
Digit : [0-9] ;
IDENTIFIER : [a-zA-Z_]+[0-9a-zA-Z_]*;



/* Skip actions defined here*/


Whitespace: [ \t]+ -> skip;

Newline: ('\r' '\n'? | '\n') -> skip;

BlockComment: '/*' .*? '*/' -> skip;

LineComment: '//' ~ [\r\n]* -> skip;