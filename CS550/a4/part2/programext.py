#!/usr/bin/python
import sys
from memory import *
from environment import *

####  CONSTANTS   ################

    # the variable name used to store a proc's return value
returnSymbol = 'return'

tabstop = '  ' # 2 spaces
######   CLASSES   ##################
def safe_eval(e, env) :
    if isinstance(e, Allocation) :
        return e
    return e.eval(env)
def error(msg) :
    print 'ERROR:', msg
    sys.exit(1)

class Expr :
    '''Virtual base class for expressions in the language'''

    def __init__( self ) :
        raise NotImplementedError(
            'Expr: pure virtual base class.  Do not instantiate' )

    def eval( self, env ) :
        '''Given an environment and a function table, evaluates the expression,
        returns the value of the expression (an int in this grammar)'''

        raise NotImplementedError(
            'Expr.eval: virtual method.  Must be overridden.' )

    def display( self, env, depth=0 ) :
        'For debugging.'
        raise NotImplementedError(
            'Expr.display: virtual method.  Must be overridden.' )

class ListElement :
    '''Virtual base class for list elements in the language'''

    def __init__( self ) :
        raise NotImplementedError(
            'Expr: pure virtual base class.  Do not instantiate' )

    def eval( self, env ) :
        '''Given an environment and a function table, evaluates the expression,
        returns the value of the expression (an int in this grammar)'''

        raise NotImplementedError(
            'Expr.eval: virtual method.  Must be overridden.' )

    def display( self, env, depth=0 ) :
        'For debugging.'
        raise NotImplementedError(
            'Expr.display: virtual method.  Must be overridden.' )

class Number( Expr, ListElement ) :
    '''Just integers'''

    def __init__( self, v=0 ) :
        self.value = v
    
    def eval( self, env ) :
        return Allocation(self.value, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%s%i" % (tabstop*depth, self.value)

class Ident( Expr, ListElement ) :
    '''Stores the symbol'''

    def __init__( self, name ) :
        self.name = name
    
    def eval( self, env ) :
        return env.nt[ self.name ]

    def display( self, env, depth=0 ) :
        print "%s%s" % (tabstop*depth, self.name)

class Times( Expr ) :
    '''expression for binary multiplication'''

    def __init__( self, lhs, rhs ) :
        '''lhs, rhs are Expr's, the operands'''

        # test type here?
        # if type( lhs ) == type( Expr ) :
        self.lhs = lhs
        self.rhs = rhs
    
    def eval( self, env ) :
        return Allocation(self.lhs.eval( env ).value * self.rhs.eval( env ).value, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sMULT" % (tabstop*depth)
        self.lhs.display( env, depth+1 )
        self.rhs.display( env, depth+1 )


class Plus( Expr ) :
    '''expression for binary addition'''

    def __init__( self, lhs, rhs ) :
        self.lhs = lhs
        self.rhs = rhs
    
    def eval( self, env ) :
        return Allocation(self.lhs.eval( env ).value + self.rhs.eval( env ).value, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sADD" % (tabstop*depth)
        self.lhs.display( env, depth+1 )
        self.rhs.display( env, depth+1 )


class Minus( Expr ) :
    '''expression for binary subtraction'''

    def __init__( self, lhs, rhs ) :
        self.lhs = lhs
        self.rhs = rhs
    
    def eval( self, env ) :
        return Allocation(self.lhs.eval( env ).value - self.rhs.eval(env).value, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sSUB" % (tabstop*depth)
        self.lhs.display( env, depth+1 )
        self.rhs.display( env, depth+1 )


class FunCall( Expr ) :
    '''stores a function call:
      - its name, and arguments'''
    
    def __init__( self, name, argList ) :
        self.name = name
        self.argList = argList
    
    def eval( self, env ) :
        return env.ft[ self.name ].apply( env, self.argList )

    def display( self, env, depth=0 ) :
        print "%sFunction Call: %s, args:" % (tabstop*depth, self.name)
        for e in self.argList :
            e.display( env, depth+1 )


class List( ListElement ) :
    '''Lists'''

    def __init__( self,  value ) :
        self.value = value
        self.pos = -1

    def eval( self, env ) :
        lst = Allocation(None, Allocation.EMPTY_LIST)
        for e in reversed(self.value) :
            lst = ConsExpr(e, lst).eval(env)
        return lst

    def display( self, env, depth=0 ) :
        print "%sLIST: [" % (tabstop*depth)
        for e in self.value :
            e.display( env, depth+1 )
        print "%s      ] " % (tabstop*depth)


class ConsExpr( Expr ) :

    def __init__( self, car, cdr ) :
        self.car = car
        self.cdr = cdr

    def eval( self, env ) :
        attempt = self.attempt_alloc(env)
        if attempt >= 0 :
            return Allocation(attempt, Allocation.LIST)

        for alloc in env.nt.values() :
            if alloc.vtype == Allocation.LIST :
                env.mem.mark(alloc.value)

        env.mem.mark(env.mem.last_alloc)
        env.mem.sweep()

        if env.mem.next_avail >= 0 :
            attempt = self.attempt_alloc(env)
            if attempt >= 0 :
                return Allocation(attempt, Allocation.LIST)
        print 'Could not allocate enough memory for cons'
        sys.exit(1)
        
    def attempt_alloc(self, env) :
        front = self.car
        front = safe_eval(self.car, env)
        rest = safe_eval(self.cdr, env)

        front_is_list = (front.vtype == Allocation.LIST)
        if rest.vtype == Allocation.EMPTY_LIST :
            return env.mem.allocate(Cell(front.value, -1, front_is_list))
        else :
            if rest.vtype != Allocation.LIST :
                error('The second parameter of \'cons\' must me a list')
            return env.mem.allocate(Cell(front.value, rest.value, front_is_list))

    def display( self, env, depth=0 ) :
        print "%sCONS" % (tabstop*depth)
        self.car.display( env, depth+1 )
        self.cdr.display( env, depth+1 )

class CarExpr( Expr ) :

    def __init__( self, L ) :
        self.L = L

    def eval( self, env ) :
        e = safe_eval(self.L, env)
        if e.vtype != Allocation.LIST :
            error('The \'car\' function takes a list')
        car = env.mem.get(e.value)
        return Allocation(car.value, Allocation.LIST if car.lst else Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sCDR" % (tabstop*depth)
        self.L.display( env, depth+1 )

class CdrExpr( Expr ) :

    def __init__( self, L ) :
        self.L = L

    def eval( self, env ) :
        v = safe_eval(self.L, env)
        if v.vtype != Allocation.LIST :
            error('The \'cdr\' function takes a list')
        return Allocation(env.mem.get(v.value).nextptr, Allocation.LIST)

    def display( self, env, depth=0 ) :
        print "%sCDR" % (tabstop*depth)
        self.L.display( env, depth+1 )

class NullpExpr( Expr ) :

    def __init__( self, L ) :
        self.L = L

    def eval( self, env ) :
        if self.L.eval(env).vtype == Allocation.EMPTY_LIST :
            return Allocation(1, Allocation.NUMBER)
        return Allocation(0, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sNULLP" % (tabstop*depth)
        self.L.display( env, depth+1 )


class IntpExpr( Expr ) :

    def __init__( self, L ) :
        self.L = L

    def eval( self, env ) :
        if self.L.eval(env).vtype == Allocation.NUMBER :
            return Allocation(1, Allocation.NUMBER)
        return Allocation(0, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sINTP" % (tabstop*depth)
        self.L.display( env, depth+1 )


class ListpExpr( Expr ) :

    def __init__( self, L ) :
        self.L = L

    def eval( self, env ) :
        if self.L.eval(env).vtype == Allocation.LIST :
            return Allocation(1, Allocation.NUMBER)
        return Allocation(0, Allocation.NUMBER)

    def display( self, env, depth=0 ) :
        print "%sLISTP" % (tabstop*depth)
        self.L.display( env, depth+1 )


class Concat( Expr ) :
    '''expression for binary list concatenation'''

    def __init__( self, lhs, rhs ) :
        self.lhs = lhs
        self.rhs = rhs
    
    def eval( self, env ) :
        l = safe_eval(self.lhs, env)
        r = safe_eval(self.rhs, env)
        if l.vtype != Allocation.LIST or r.vtype != Allocation.LIST :
            error('The \'concat\' function takes two lists')

        car = CarExpr(l).eval(env)
        if env.mem.get(l.value).nextptr == -1 :
            return ConsExpr(car, r).eval(env) 
        cdr = CdrExpr(l)
        return ConsExpr(car, Concat(cdr, r).eval(env)).eval(env)

    def display( self, env, depth=0 ) :
        print "%sCONCAT" % (tabstop*depth)
        self.lhs.display( env, depth+1 )
        self.rhs.display( env, depth+1 )


#-------------------------------------------------------

class Stmt :
    '''Virtual base class for statements in the language'''

    def __init__( self ) :
        raise NotImplementedError(
            'Stmt: pure virtual base class.  Do not instantiate' )

    def eval( self, env ) :
        '''Given an environment and a function table, evaluates the expression,
        returns the value of the expression (an int in this grammar)'''

        raise NotImplementedError(
            'Stmt.eval: virtual method.  Must be overridden.' )

    def display( self, env, depth=0 ) :
        'For debugging.'
        raise NotImplementedError(
            'Stmt.display: virtual method.  Must be overridden.' )


class AssignStmt( Stmt ) :
    '''adds/modifies symbol in the current context'''

    def __init__( self, name, rhs ) :
        '''stores the symbol for the l-val, and the expressions which is the
        rhs'''
        self.name = name
        self.rhs = rhs
    
    def eval( self, env ) :
        v = self.rhs.eval(env)
        env.nt[ self.name ] = v

    def display( self, env, depth=0 ) :
        print "%sAssign: %s :=" % (tabstop*depth, self.name)
        self.rhs.display( env, depth+1 )


class DefineStmt( Stmt ) :
    '''Binds a proc object to a name'''

    def __init__( self, name, proc ) :
        self.name = name
        self.proc = proc

    def eval( self, env ) :
        env.ft[ self.name ] = self.proc

    def display( self, env, depth=0 ) :
        print "%sDEFINE %s :" % (tabstop*depth, self.name)
        self.proc.display( env, depth+1 )


class IfStmt( Stmt ) :

    def __init__( self, cond, tBody, fBody ) :
        '''expects:
        cond - expression (integer)
        tBody - StmtList
        fBody - StmtList'''
        
        self.cond = cond
        self.tBody = tBody
        self.fBody = fBody

    def eval( self, env ) :
        if self.cond.eval( env ).value > 0 :
            self.tBody.eval( env )
        else :
            self.fBody.eval( env )

    def display( self, env, depth=0 ) :
        print "%sIF" % (tabstop*depth)
        self.cond.display( env, depth+1 )
        print "%sTHEN" % (tabstop*depth)
        self.tBody.display( env, depth+1 )
        print "%sELSE" % (tabstop*depth)
        self.fBody.display( env, depth+1 )


class WhileStmt( Stmt ) :

    def __init__( self, cond, body ) :
        self.cond = cond
        self.body = body

    def eval( self, env ) :
        while self.cond.eval( env ).value > 0 :
            self.body.eval( env )

    def display( self, env, depth=0 ) :
        print "%sWHILE" % (tabstop*depth)
        self.cond.display( env, depth+1 )
        print "%sDO" % (tabstop*depth)
        self.body.display( env, depth+1 )

#-------------------------------------------------------

class StmtList :
    '''builds/stores a list of Stmts'''

    def __init__( self ) :
        self.sl = []
    
    def insert( self, stmt ) :
        self.sl.insert( 0, stmt )
    
    def eval( self, env ) :
        for s in self.sl :
            s.eval( env )
    
    def display( self, env, depth=0 ) :
        print "%sSTMT LIST" % (tabstop*depth)
        for s in self.sl :
            s.display( env, depth+1 )


class Proc :
    '''stores a procedure (formal params, and the body)

    Note that, while each function gets its own environment, we decided not to
    allow side-effects, so, no access to any outer contexts.  Thus, nesting
    functions is legal, but no different than defining them all in the global
    environment.  Further, all calls are handled the same way, regardless of
    the calling environment (aenv.fter the actual args are evaluated); the proc
    doesn't need/want/get an outside environment.'''

    def __init__( self, paramList, body ) :
        '''expects a list of formal parameters (variables, as strings), and a
        StmtList'''

        self.parList = paramList
        self.body = body

    def apply( self, env, args ) :
        # sanity check, # of args
        if len( args ) is not len( self.parList ) :
            print "Param count does not match:"
            sys.exit( 1 )

        new_nt = {}
        # bind parameters in new name table (the only things there right now)
            # use zip, bastard
        for i in range( len( args )) :
            new_nt[ self.parList[i] ] = args[i].eval( env )

        # evaluate the function body using the new name table and the old (only)
        # function table.  Note that the proc's return value is stored as
        # 'return in its nametable

        self.body.eval(Environment(new_nt, env.ft, env.mem))
        if new_nt.has_key( returnSymbol ) :
            return new_nt[ returnSymbol ]
        else :
            print "Error:  no return value"
            sys.exit( 2 )
    
    def display( self, env, depth=0 ) :
        print "%sPROC %s :" % (tabstop*depth, str(self.parList))
        self.body.display( env, depth+1 )


class Program :
    
    def __init__( self, stmtList, env ) :
        self.stmtList = stmtList
        self.env = env
    
    def eval( self ) :
        self.stmtList.eval( self.env )
    
    def dump( self ) :
#        print "Dump of Memory"
#        print self.env.mem
        print "Dump of Symbol Table"
        print "Name Table"
        for k in self.env.nt :
            print "  %s -> %s " % ( str(k), self.env.nt[k].string(self.env.mem) )
        print "Function Table"
        for k in self.env.ft :
            print "  %s" % str(k)

    def display( self, depth=0 ) :
        print "%sPROGRAM :" % (tabstop*depth)
        self.stmtList.display( env.nt, env.ft )

