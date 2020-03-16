grammar ifcc;

axiom : prog
      ;

prog : 'int' 'main' '(' ')' '{' bloc RETURN expr ';' '}' ;

bloc : instructions
	|
     ;

instructions : instruction
             | instruction instructions
             ;	

instruction : declaration
            | affectation 
            ;


declaration : 'int' VAR ';'
	    ;


affectation : expr '=' expr ';'
	    ;

expr : CONST  #const
     | VAR #var
     ;


TYPE : 'int'
     | 'double'
     ; 
RETURN : 'return' ;
CONST : [0-9]+ ;
VAR : [a-zA-Z]+;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

