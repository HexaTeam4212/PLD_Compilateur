grammar ifcc;

axiom : definitionFunction+;

type : INTEGER # integer
;

instr : RETURN CONST ';' # return
;

definitionFunction : type NAME '(' ')' '{' (instr )* '}';

INTEGER : 'int' ;
NAME : [a-zA-Z][a-zA-Z0-9] ;
RETURN : 'return' ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);
