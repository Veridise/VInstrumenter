lexer grammar VLexer;

// These are all supported lexer sections:

// Lexer file header. Appears at the top of h + cpp files. Use e.g. for copyrights.
@lexer::header {/* lexer header section */}

// Appears before any #include in h + cpp files.
@lexer::preinclude {/* lexer precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@lexer::postinclude {
/* lexer postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceds the lexer class declaration in the h file (e.g. for additional types etc.).
@lexer::context {/* lexer context section */}

// Appears in the public part of the lexer in the h file.
@lexer::members {/* public lexer declarations section */
bool canTestFoo() { return true; }
bool isItFoo() { return true; }
bool isItBar() { return true; }

void myFooLexerAction() { /* do something*/ };
void myBarLexerAction() { /* do something*/ };
}

// Appears in the private part of the lexer in the h file.
@lexer::declarations {/* private lexer declarations/members section */}

// Appears in line with the other class member definitions in the cpp file.
@lexer::definitions {/* lexer definitions section */}

channels { CommentsChannel, DirectiveChannel }

tokens {
	DUMMY
}

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