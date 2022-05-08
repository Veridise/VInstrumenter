grammar V;

/*
 * Spec Rules
 */

spec : behavioralSpec EOF | testSpec EOF | tempSpec EOF | invariantSpec EOF ;

behavioralSpec : varsSection? precondSection? postcondSection
               ;

testSpec       : varsSection? initSection? specSection
               ;

tempSpec       : varsSection? ltlFairnessSection? ltlPropertySection
               ;

invariantSpec  : varsSection? invariantSection
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

invariantSection : INV_LABEL invAtom
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
             | smartltlAtom IMP smartltlAtom
             | smartltlAtom SEQ smartltlAtom
             | smartltlAtom L_BIN smartltlAtom
             ;

invAtom     : atom
            | CONTRACT_INV LPAREN varAccess COMMA constraint RPAREN
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
            | atomFnName LPAREN params RPAREN 
            ;
            
atomFnName  : varAccess DOT ident
            | varAccess DOT WILDCARD
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
            | constraint IMP constraint
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
            
fnName      : fnName LPAREN argList RPAREN DOT ident
            | fnName LBRACK arithExpr RBRACK DOT ident
            | fnName DOT ident
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
INV_LABEL : ('Inv:' | 'inv:' | 'Invariant:' | 'invariant:') ;

ATOM_LOC     : ('executed' | 'finished' | 'started' | 'reverted' | 'willSucceed') ;
CONTRACT_INV : 'Cinv' ;

IMP        : '==>' ;
T_BIN      : ('U' | 'R') ; // also includes ';' and '==>' but already specified above
T_UN       : ('<>' | 'X') ; // also includes '[]' but necessary in types also so specified above

IDENTIFIER : [a-zA-Z_][a-zA-Z_0-9]* ;

A1_BIN     : ('*' | '/') ;
A2_BIN     : ('+' | '-') ;
A_UN       : '-';
C_BIN      : ('=' | '!=' | '<' | '>' | '<=' | '>=') ;
L_BIN      : ('&&' | '||') ;
L_UN       : '!' ;

NUM        : ([0-9]+ | [0-9]+ 'e' [0-9]+) ;

NEWLINE    : ('\r'? '\n' | '\r')+ -> skip ;

WHITESPACE : ' ' -> skip ;
