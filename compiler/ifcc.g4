grammar ifcc;

axiom : definitionFunction+;

type : INTEGER #integer
;

instr : 
  'return' expr ';'           #return
| type NAME (',' NAME)* ';'   #declaration
| NAME '=' expr ';'           #affectation
| type NAME '=' expr ';'      #declareEtAffecte
| NAME '=' NAME '(' ( | NAME  | NAME ',' NAME | NAME  ',' NAME ',' NAME |NAME  ','  NAME  ',' NAME ',' NAME | NAME  ',' NAME  ','  NAME  ',' NAME ',' NAME | NAME ',' NAME  ',' NAME  ','  NAME  ',' NAME ',' NAME  ) ')' ';'	  #calling
| NAME '(' ( | NAME  | NAME ',' NAME | NAME  ',' NAME ',' NAME |NAME  ','  NAME  ',' NAME ',' NAME | NAME  ',' NAME  ','  NAME  ',' NAME ',' NAME | NAME ',' NAME  ',' NAME  ','  NAME  ',' NAME ',' NAME  ) ')' ';'	  #calling2
| 'if' '(' expr ')' '{' (instr )* '}' (elseStatement )? #ifstatement
| 'while' '(' expr ')' '{' (instr )* '}' #whilestatement
;

elseStatement : 'else' '{' (instr )* '}';

expr :
  expr '&' expr  #EtBit
| expr '^' expr  #XorBit
| expr '|' expr  #OuBit
| exprLvl0       #casStandardLvl0
;

exprLvl0 : 
  exprLvl0 '+' exprLvl0   #addition
| exprLvl1                #casStandardLvl1
| exprLvl0 '==' exprLvl0  #egalite
| exprLvl0 '>' exprLvl0   #superiorite
| exprLvl0 '<' exprLvl0   #inferiorite
| exprLvl0 '!=' exprLvl0  #difference
| exprLvl0 '>=' exprLvl0  #supOuEgalite
| exprLvl0 '<=' exprLvl0  #infOuEgalite
;

exprLvl1 :
 exprLvl1'-' exprLvl1 #soustraction
|exprLvl2             #casStandardLvl2
;

exprLvl2 :
  exprLvl2 '*' exprLvl2 #multiplication
| exprLvl2 '/' exprLvl2 #division
| exprLvl3              #casStandardLvl3
;

exprLvl3 :
  '-' exprLvl3         #invert
| '!' exprLvl3         #not
| '(' expr ')'         #parenthese
| CONST                #const
| NAME                 #var
;

definitionFunction : type NAME '('( | type NAME  | type NAME ',' type NAME | type NAME  ',' type NAME ',' type NAME | type NAME  ',' type NAME  ',' type NAME ',' type NAME | type NAME  ',' type NAME  ',' type NAME  ',' type NAME ',' type NAME | type NAME ',' type NAME  ',' type NAME  ','  type NAME  ',' type NAME ',' type NAME  ) ')' '{' (instr )* '}';

INTEGER : 'int' ;
NAME : [a-zA-Z]+[a-zA-Z0-9]* ;
CONST : [0-9]+ ;
COMMENT : '/*' .*? '*/' -> skip ;
DIRECTIVE : '#' .*? '\n' -> skip ;
WS    : [ \t\r\n] -> channel(HIDDEN);

