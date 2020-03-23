grammar ifcc;

axiom : definitionFunction+;

type : INTEGER #integer
;

instr : 'return' expr ';'           #return
      | type VAR (',' VAR)* ';'     #declaration
      | VAR '=' expr ';'            #affectation
      ;

expr : CONST         #const
     | VAR           #var
	 | expr '+' expr #addition
     ;



definitionFunction : type NAME '(' ')' '{' (instr )* '}';

INTEGER : 'int' ;
NAME : [a-zA-Z]+[a-zA-Z0-9] ;
CONST : [0-9]+ ;
VAR : [a-zA-Z]+;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

