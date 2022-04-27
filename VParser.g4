parser grammar VParser;

options {
	tokenVocab = VLexer;
}

// These are all supported parser sections:

// Parser file header. Appears at the top in all parser related files. Use e.g. for copyrights.
@parser::header {/* parser/listener/visitor header section */}

// Appears before any #include in h + cpp files.
@parser::preinclude {/* parser precinclude section */}

// Follows directly after the standard #includes in h + cpp files.
@parser::postinclude {
/* parser postinclude section */
#ifndef _WIN32
#pragma GCC diagnostic ignored "-Wunused-parameter"
#endif
}

// Directly preceeds the parser class declaration in the h file (e.g. for additional types etc.).
@parser::context {/* parser context section */}

// Appears in the private part of the parser in the h file.
// The function bodies could also appear in the definitions section, but I want to maximize
// Java compatibility, so we can also create a Java parser from this grammar.
// Still, some tweaking is necessary after the Java file generation (e.g. bool -> boolean).
@parser::members {
/* public parser declarations/members section */
bool myAction() { return true; }
bool doesItBlend() { return true; }
void cleanUp() {}
void doInit() {}
void doAfter() {}
}

// Appears in the public part of the parser in the h file.
@parser::declarations {/* private parser declarations section */}

// Appears in line with the other class member definitions in the cpp file.
@parser::definitions {/* parser definitions section */}

// Additionally there are similar sections for (base)listener and (base)visitor files.
@parser::listenerpreinclude {/* listener preinclude section */}
@parser::listenerpostinclude {/* listener postinclude section */}
@parser::listenerdeclarations {/* listener public declarations/members section */}
@parser::listenermembers {/* listener private declarations/members section */}
@parser::listenerdefinitions {/* listener definitions section */}

@parser::baselistenerpreinclude {/* base listener preinclude section */}
@parser::baselistenerpostinclude {/* base listener postinclude section */}
@parser::baselistenerdeclarations {/* base listener public declarations/members section */}
@parser::baselistenermembers {/* base listener private declarations/members section */}
@parser::baselistenerdefinitions {/* base listener definitions section */}

@parser::visitorpreinclude {/* visitor preinclude section */}
@parser::visitorpostinclude {/* visitor postinclude section */}
@parser::visitordeclarations {/* visitor public declarations/members section */}
@parser::visitormembers {/* visitor private declarations/members section */}
@parser::visitordefinitions {/* visitor definitions section */}

@parser::basevisitorpreinclude {/* base visitor preinclude section */}
@parser::basevisitorpostinclude {/* base visitor postinclude section */}
@parser::basevisitordeclarations {/* base visitor public declarations/members section */}
@parser::basevisitormembers {/* base visitor private declarations/members section */}
@parser::basevisitordefinitions {/* base visitor definitions section */}

/*
 * Spec Rules
 */

spec : behavioralSpec | testSpec | tempSpec ;

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