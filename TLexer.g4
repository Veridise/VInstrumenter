lexer grammar TLexer;

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

VARS_LABEL : ('Vars:' | 'vars:') ;       

PRECOND_LABEL : ('Pre:' | 'pre:') ;       

POSTCOND_LABEL : ('Post:' | 'post:') ;       

ATOM_LOC   : ('executed' | 'finished' | 'started' | 'reverted' | 'willSucceed') ;

CON_BIN    : (';' | '&&' | '||') ;

T_BIN      : (';' | 'U' | 'R' | '==>') ;

T_UN       : ('[]' | '<>' | 'X') ;

IDENTIFIER : [a-zA-Z_][a-zA-Z_0-9]* ;

A1_BIN     : ('*' | '/') ;

A2_BIN     : ('+' | '-') ;

A_UN       : '-';

C_BIN      : ('==' | '!=' | '<' | '>' | '<=' | '>=') ;

L_BIN      : ('&&' | '||') ;

L_UN       : '!' ;

NUM        : [0-9]+ ;

NEWLINE    : ('\r'? '\n' | '\r')+ -> skip ;

WHITESPACE : ' ' -> skip ;