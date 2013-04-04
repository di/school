#!/usr/bin/python

import sys
from programext import *
from ply import lex

tokens = (
    'PLUS',
    'MINUS',
    'TIMES',
    'LPAREN',
    'RPAREN',
    'LBRACKET',
    'RBRACKET',
    'SEMICOLON',
    'COMMA',
    'NUMBER',
    'ASSIGNOP',
    'WHILE',
    'DO',
    'OD',
    'IF',
    'THEN',
    'ELSE',
    'FI',
    'DEFINE',
    'PROC',
    'END',
    'IDENT',
    'CONS',
    'CAR',
    'CDR',
    'NULLP',
    'INTP',
    'LISTP',
    'CONCAT',
)

    # These are all caught in the IDENT rule, typed there.
reserved = {
        'while' : 'WHILE',
        'do'    : 'DO',
        'od'    : 'OD',
        'if'    : 'IF',
        'then'    : 'THEN',
        'else'    : 'ELSE',
        'fi'    : 'FI',
        'define': 'DEFINE',
        'proc'    : 'PROC',
        'end'   : 'END',
        'cons'  : 'CONS',
        'car'   : 'CAR',
        'cdr'   : 'CDR',
        'nullp' : 'NULLP',
        'intp'  : 'INTP',
        'listp' : 'LISTP',
        }

# Now, this section.  We have a mapping, REs to token types (please note
# the t_ prefix).  They simply return the type.

    # t_ignore is special, and does just what it says.  Spaces and tabs
t_ignore = ' \t'

    # These are the simple maps
t_PLUS        = r'\+'
t_MINUS         = r'-'
t_TIMES        = r'\*'
t_LPAREN    = r'\('
t_RPAREN    = r'\)'
t_LBRACKET    = r'\['
t_RBRACKET    = r'\]'
t_ASSIGNOP      = r':='
t_SEMICOLON     = r';'
t_COMMA        = r','
t_CONCAT        = r'\|\|'

def t_IDENT( t ):
    r'[a-zA-Z_][a-zA-Z_0-9]*'
    #r'[a-z]+'
    t.type = reserved.get( t.value, 'IDENT' )    # Check for reserved words
    return t

def t_NUMBER( t ) :
    r'[0-9]+'

        # t.value holds the string that matched.  Dynamic typing - no unions
    t.value = int( t.value )
    return t

    # These are standard little ditties:
def t_newline( t ):
    r'\n+'
    t.lexer.lineno += len( t.value )

    # Error handling rule
def t_error( t ):
    print "Illegal character '%s' on line %d" % ( t.value[0], t.lexer.lineno )
    return t
    #t.lexer.skip( 1 )

lex.lex()

#-----   LEXER (end)   -------------------------------


######   YACC   #####################################

import ply.yacc as yacc

mem_size = 8192
if len(sys.argv) > 1 :
    mem_size = int(sys.argv[1])
env = Environment({}, {}, Memory(mem_size))
def p_program( p ) :
    'program : stmt_list'

    P = Program( p[1], env )
    print 'Running Program'
    P.eval()
    P.dump()

def p_stmt_list( p ) :
    '''stmt_list : stmt SEMICOLON stmt_list
          | stmt'''
    if len( p ) == 2 :  # single stmt => new list
        p[0] = StmtList()
        p[0].insert( p[1] )
    else :  # we have a stmtList, keep adding to front
        p[3].insert( p[1] )
        p[0] = p[3]

def p_stmt( p ) :
    '''stmt : assign_stmt
                | while_stmt
                | if_stmt
                | define_stmt'''
    p[0] = p[1]

def p_add( p ) :
    'expr : expr PLUS term'
    p[0] = Plus( p[1], p[3] )

def p_sub( p ) :
    'expr : expr MINUS term'
    p[0] = Minus( p[1], p[3] )

def p_expr_list( p ) :
    '''expr_list : expr COMMA expr_list
                | expr'''
    if len( p ) == 2 :  # single expr => new list
        p[0] = [ p[1] ]
    else :  # we have a expr_list, keep adding to front
        p[3].insert( 0, p[1] )
        p[0] = p[3]

def p_expr_term( p ) :
    'expr : term'
    p[0] = p[1]

def p_expr_cons( p ) :
    'expr : cons'
    p[0] = p[1]

def p_expr_car( p ) :
    'expr : car'
    p[0] = p[1]

def p_expr_cdr( p ) :
    'expr : cdr'
    p[0] = p[1]

def p_expr_nullp( p ) :
    'expr : nullp'
    p[0] = p[1]

def p_expr_intp( p ) :
    'expr : intp'
    p[0] = p[1]

def p_expr_listp( p ) :
    'expr : listp'
    p[0] = p[1]

def p_concat( p ) :
    'expr : term CONCAT term'
    p[0] = Concat( p[1], p[3] )

def p_mult( p ) :
    '''term : term TIMES fact'''
    p[0] = Times( p[1], p[3] )

def p_term_fact( p ) :
    'term : fact'
    p[0] = p[1]

def p_fact_expr( p ) :
    'fact : LPAREN expr RPAREN'
    p[0] = p[2]

def p_fact_NUM( p ) :
    'fact : NUMBER'
    p[0] = Number( p[1] )

def p_fact_IDENT( p ) :
    'fact : IDENT'
    p[0] = Ident( p[1] )

def p_fact_funcall( p ) :
    'fact : func_call'
    p[0] = p[1]

def p_fact_list( p ) :
    'fact : list'
    p[0] = p[1]

def p_assn( p ) :
    'assign_stmt : IDENT ASSIGNOP expr'
    p[0] = AssignStmt( p[1], p[3] )

def p_while( p ) :
    'while_stmt : WHILE expr DO stmt_list OD'
    p[0] = WhileStmt( p[2], p[4] )

def p_if( p ) :
    'if_stmt : IF expr THEN stmt_list ELSE stmt_list FI'
    p[0] = IfStmt( p[2], p[4], p[6] )

def p_def( p ) :
    'define_stmt : DEFINE IDENT PROC LPAREN param_list RPAREN stmt_list END'
    p[0] = DefineStmt( p[2], Proc( p[5], p[7] ))

def p_param_list( p ) :
    '''param_list : IDENT COMMA param_list
                | IDENT'''
    if len( p ) == 2 :  # single param => new list
        p[0] = [ p[1] ]
    else :  # we have a param_list, keep adding to front
        p[3].insert( 0, p[1] )
        p[0] = p[3]

def p_func_call( p ) :
    'func_call : IDENT LPAREN expr_list RPAREN'
    p[0] = FunCall( p[1], p[3] )

def p_sequence( p ) :
    '''sequence : listelement COMMA sequence
                | listelement'''
    if len( p ) == 2 :  # single param => new list
        p[0] = [p[1]]
    else :  # we have a param_list, keep adding to front
        p[3].insert( 0, p[1] )
        p[0] = p[3]

def p_list( p ) :
    '''list : LBRACKET sequence RBRACKET
            | LBRACKET RBRACKET'''
    if len( p ) == 3:    # [ ] empty list
        p[0] = List( [] )
    else:
        p[0] = List( p[2] )

def p_elem_IDENT( p ) :
    'listelement : IDENT'
    p[0] = Ident( p[1] )

def p_elem_NUMBER( p ) :
    'listelement : NUMBER'
    p[0] = Number( p[1] )

def p_elem_list( p ) :
    'listelement : list'
    p[0] = p[1]

def p_cons_expr( p ) :
    'cons : CONS LPAREN expr COMMA expr RPAREN'
    p[0] = ConsExpr( p[3], p[5] )

def p_car_expr( p ) :
    'car : CAR LPAREN expr RPAREN'
    p[0] = CarExpr( p[3] )

def p_cdr_expr( p ) :
    'cdr : CDR LPAREN expr RPAREN'
    p[0] = CdrExpr( p[3] )

def p_nullp_expr( p ) :
    'nullp : NULLP LPAREN expr RPAREN'
    p[0] = NullpExpr( p[3] )

def p_intp_expr( p ) :
    'intp : INTP LPAREN fact RPAREN'
    p[0] = IntpExpr( p[3] )

def p_listp_expr( p ) :
    'listp : LISTP LPAREN fact RPAREN'
    p[0] = ListpExpr( p[3] )

def p_error( p ):
    print "Syntax error in input!", str( p )
    sys.exit( 2 )

yacc.yacc()

if __name__ == '__main__' :
    yacc.parse(sys.stdin.read())
