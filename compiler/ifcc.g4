grammar ifcc;

axiom : definitionFunction+;

type : INTEGER #integer
;

instr : 
  'return' expr ';'           #return
| type NAME (',' NAME)* ';'   #declaration
| NAME '=' expr ';'           #affectation
| 'if' '(' expr ')' '{' (instr )* '}' (elseStatement )? #ifstatement
;

elseStatement : 'else' '{' (instr )* '}';

expr : 
 expr '+' expr #addition
| exprLvl1     #casStandardLvl1
| expr '==' expr #egalite
| expr '>' expr #superiorite
| expr '<' expr #inferiorite
| expr '!=' expr #difference
;

exprLvl1 :
 exprLvl1'-' exprLvl1 #soustraction
|exprLvl2 #casStandardLvl2
;

exprLvl2 :
  exprLvl2 '*' exprLvl2 #multiplication
| exprLvl2 '/' exprLvl2 #division
| CONST                 #const
| NAME                  #var
| '(' expr ')'          #parenthese
;

definitionFunction : type NAME '(' ')' '{' (instr )* '}';

INTEGER : 'int' ;
NAME : [a-zA-Z]+[a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

