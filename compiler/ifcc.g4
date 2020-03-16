grammar ifcc;

axiom : definitionFunction+;

type : INTEGER # integer
;

instr : 'return' CONST ';' # return
;

definitionFunction : type NAME '(' ')' '{' (instr )* '}';

INTEGER : 'int' ;
NAME : [a-zA-Z]+[a-zA-Z0-9] ;
CONST : [0-9]+ ;
VAR : [a-zA-Z]+;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

