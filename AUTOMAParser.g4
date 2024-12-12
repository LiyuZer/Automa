// Define a grammar called automa


grammar automa;
r  : graphDeceleration*;
graphDeceleration : 'graph'   IDENTIFIER  '{' graphBody '}';
graphBody : memory* nodeDefinitions? transitions* afterAccept* afterReject*;
memory : 'memory' ':'  'SYMBOLS';
nodeDefinitions : 'node'  '{' IDENTIFIER '}';

IDENTIFIER : [a-zA-Z_]+;
transitions : 'transition'  '->'  IDENTIFIER IDENTIFIER '=>'  tuple ';' ;
tuple : '(' IDENTIFIER ')';
afterAccept : 'afterAccept'  '{' IDENTIFIER '}';
afterReject : 'afterReject' '{' IDENTIFIER '}';

WS: [ \t\r\n]+ -> skip;




