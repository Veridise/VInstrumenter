grammar V;

/*
 * Spec Rules
 */

spec : behavioralSpec EOF | testSpec EOF | tempSpec EOF;

behavioralSpec : varsSection? precondSection? postcondSection
               ;

testSpec       : varsSection? initSection? specSection
               ;

tempSpec       : varsSection? ltlFairnessSection? ltlPropertySection
               ;

/*
 * Section Rules
 */
varsSection : VARS_LABEL declList
            ;

precondSection : PRECOND_LABEL atom
               ;  

postcondSection : POSTCOND_LABEL atom
                ;

initSection : INIT_LABEL seqAtom
            ;

specSection : SPEC_LABEL seqAtom
            ;

ltlFairnessSection : LTLFAIR_LABEL smartltlAtom
                   ;

ltlPropertySection : LTLPROP_LABEL smartltlAtom
                   ;


/*
 * Sequence of atoms
 */

seqAtom : atom
        | atom SEQ seqAtom
        ;

/*
 * Variable Section Rules
 */

declList    : typ ident
            | typ ident COMMA declList
            ;

typ        : IDENTIFIER
           | IDENTIFIER LBRACK RBRACK
           ;


/*
 * SmartLTL Rules
 */

smartltlAtom : atom
             | LPAREN smartltlAtom RPAREN
             | T_UN smartltlAtom
             | L_UN smartltlAtom
             | LBRACK RBRACK smartltlAtom
             | smartltlAtom T_BIN smartltlAtom
             | smartltlAtom SEQ smartltlAtom
             | smartltlAtom L_BIN smartltlAtom
             ;

atom        : ATOM_LOC LPAREN atomFn COMMA constraint RPAREN
            | ATOM_LOC LPAREN atomFn RPAREN
            | LET LPAREN ident ASSN LBRACK params RBRACK RPAREN
            | FOREACH LPAREN ident IN ident COMMA atom RPAREN
            | SENT LPAREN constraint RPAREN
            | LPAREN atom RPAREN
            | L_UN atom
            | atom L_BIN atom
            ;
               
atomFn      : atomFnName
            | WILDCARD
            | atomFnName LPAREN params RPAREN 
            ;
            
atomFnName  : ident DOT ident
            | ident
            ;
               
params      : ident
            | ident COMMA params
            | NUM
            | NUM COMMA params
            | /*epsilon*/
            ; 

constraint  : boolExpr
            | LPAREN constraint RPAREN
            | constraint L_BIN constraint
            ;

boolExpr    : varOrNum
            | L_UN boolExpr
            | LPAREN boolExpr RPAREN
            | arithExpr C_BIN arithExpr
            ;

arithExpr   : varOrNum
            | LPAREN arithExpr RPAREN
            | arithExpr A1_BIN arithExpr
            | arithExpr A2_BIN arithExpr
            ;

fnCall      : FSUM LPAREN atomFn COMMA varOrNum COMMA constraint RPAREN
            | fnName LPAREN argList RPAREN
            ;
            
fnName      : ident DOT ident
            | ident
            ;
            
argList     : constraint
            | constraint COMMA argList
            | /*epsilon*/
            ;

ident       : IDENTIFIER
            | ATOM_LOC
            ;
            
varOrNum    : varAccess
            | num
            ;
            
num         : NUM
            ;
            
varAccess   : ident
            | fnCall
            | varAccess LBRACK arithExpr RBRACK
            | varAccess DOT ident
            ;

/*
 * Lexer Rules
 */

LPAREN : '(' ;
RPAREN : ')' ;
LBRACK : '[' ;
RBRACK : ']' ;
COMMA :   ',' ;
SENT :    'sent' ;
FSUM :    'fsum' ;
WILDCARD : '*' ;
DOT      : '.' ;
SEQ      : ';' ;
ASSN     : ':=' ;
LET      : 'let' ;
FOREACH  : 'foreach' ;
IN       : ':' ;

VARS_LABEL : ('Vars:' | 'vars:' | 'Variables:' | 'variables:') ;       
PRECOND_LABEL : ('Pre:' | 'pre:'| 'Preconditions:' | 'preconditions:') ;       
POSTCOND_LABEL : ('Post:' | 'post:' | 'Postconditions:' | 'postconditions:') ;       
INIT_LABEL : ('Init:' | 'init:' | 'Assume:' | 'assume:') ;       
SPEC_LABEL : ('Spec:' | 'Specification:' | 'spec:' | 'specification:' | 'Assert:' | 'assert:') ;       
LTLFAIR_LABEL : 'LTLFairness:' ;
LTLPROP_LABEL : 'LTLProperty:' ;

ATOM_LOC   : ('executed' | 'finished' | 'started' | 'reverted' | 'willSucceed') ;

T_BIN      : ('U' | 'R' | '==>') ; // also includes ';' but already specified above
T_UN       : ('<>' | 'X') ; // also includes '[]' but necessary in types also so specified above

IDENTIFIER : [a-zA-Z_][a-zA-Z_0-9]* ;

A1_BIN     : ('*' | '/') ;
A2_BIN     : ('+' | '-') ;
A_UN       : '-';
C_BIN      : ('==' | '!=' | '<' | '>' | '<=' | '>=') ;
L_BIN      : ('&&' | '||') ;
L_UN       : '!' ;

NUM        : ([0-9]+ | [0-9]+ 'e' [0-9]+) ;

NEWLINE    : ('\r'? '\n' | '\r')+ -> skip ;

WHITESPACE : ' ' -> skip ;