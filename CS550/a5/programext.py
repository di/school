#!/usr/bin/python
#
# exp.py - Classes to represent underlying data structures for the grammar
#	 below, for the mini-compiler.
#
# Kurt Schmidt
# 8/07
#
# DESCRIPTION:
#		Just a translation of the C++ implementation by Jeremy Johnson (see
#		programext.cpp)
#
# EDITOR: cols=80, tabstop=2
#
# NOTES
#	environment:
#		a dict
#
#		Procedure calls get their own environment, can not modify enclosing env
#
#	Grammar:
#		program: stmt_list 
#		stmt_list:  stmt ';' stmt_list 
#		    |   stmt  
#		stmt:  assign_stmt 
#		    |  define_stmt 
#		    |  if_stmt 
#		    |  while_stmt 
#		assign_stmt: IDENT ASSIGNOP expr
#		define_stmt: DEFINE IDENT PROC '(' param_list ')' stmt_list END
#		if_stmt: IF expr THEN stmt_list ELSE stmt_list FI
#		while_stmt: WHILE expr DO stmt_list OD
#		param_list: IDENT ',' param_list 
#		    |      IDENT 
#		expr: expr '+' term   
#		    | expr '-' term   
#		    | term            
#		term: term '*' factor   
#		    | factor            
#		factor:     '(' expr ')'  
#		    |       NUMBER 
#		    |       IDENT 
#		    |       funcall 
#		funcall:  IDENT '(' expr_list ')'
#		expr_list: expr ',' expr_list 
#		    |      expr 
#

import sys
from environment import *
from compiler import *


####  CONSTANTS   ################

	# the variable name used to store a proc's return value
returnSymbol = 'return'

tabstop = '  ' # 2 spaces

######   CLASSES   ##################

class Expr :
	'''Virtual base class for expressions in the language'''

	def __init__( self ) :
		raise NotImplementedError(
			'Expr: pure virtual base class.  Do not instantiate' )

	def translate( self, env ) :
		'''Given an environment, translate the expression'''
		raise NotImplementedError(
			'Expr.translate: virtual method.  Must be overridden.' )

	def eval( self, env ) :
		'''Given an environment, evaluates the expression,
		returns the value of the expression (an int in this grammar)'''
		raise NotImplementedError(
			'Expr.eval: virtual method.  Must be overridden.' )

	def display( self, env, depth=0 ) :
		'For debugging.'
		raise NotImplementedError(
			'Expr.display: virtual method.  Must be overridden.' )

class Number( Expr ) :
	'''Just integers'''

	def __init__( self, v=0 ) :
		self.value = v

	def translate( self, env ) :
		c = env.compiler.constant(self.value)
		env.compiler.push_instruction('LDA', c)
		t = env.compiler.temporary()
		env.compiler.push_instruction('STA', t)
		return t

	def eval( self, env ) :
		return self.value

	def display( self, env, depth=0 ) :
		print "%s%i" % (tabstop*depth, self.value)
        
	def write( self, env, fd, depth=0 ) :
		fd.write("%s%i\n" % (tabstop*depth, self.value))
        

class Ident( Expr ) :
	'''Stores the symbol'''

	def __init__( self, name ) :
		self.name = name

	def translate( self, env ) :
		c = env.compiler.variable(self.name)
		env.compiler.push_instruction('LDA', c)
		t = env.compiler.temporary()
		env.compiler.push_instruction('STA', t)
		return t

	def eval( self, env ) :
		return env.st[ self.name ].value

	def display( self, env, depth=0 ) :
		print "%s%s" % (tabstop*depth, self.name)

	def write( self, env, fd, depth=0 ) :
		fd.write("%s%s\n" % (tabstop*depth, self.name))


class Times( Expr ) :
	'''expression for binary multiplication'''

	def __init__( self, lhs, rhs ) :
		'''lhs, rhs are Expr's, the operands'''

		# test type here?
		# if type( lhs ) == type( Expr ) :
		self.lhs = lhs
		self.rhs = rhs
	
	def translate( self, env ) :
		t1 = self.lhs.translate( env )
		t2 = self.rhs.translate( env )
		env.compiler.push_instruction('LDA', t1)
		env.compiler.push_instruction('MUL', t2)
		t3 = env.compiler.temporary()
		env.compiler.push_instruction('STA', t3)
		return t3

	def eval( self, env ) :
		return self.lhs.eval( env ) * self.rhs.eval( env )

	def display( self, env, depth=0 ) :
		print "%sMULT" % (tabstop*depth)
		self.lhs.display( env, depth+1 )
		self.rhs.display( env, depth+1 )
		#print "%s= %i" % (tabstop*depth, self.eval( env ))

	def write( self, env, fd, depth=0 ) :
		fd.write("%sMULT\n" % (tabstop*depth))
		self.lhs.write( env, fd, depth+1 )
		self.rhs.write( env, fd, depth+1 )


class Plus( Expr ) :
	'''expression for binary addition'''

	def __init__( self, lhs, rhs ) :
		self.lhs = lhs
		self.rhs = rhs
	
	def translate( self, env ) :
		t1 = self.lhs.translate( env )
		t2 = self.rhs.translate( env )
		env.compiler.push_instruction('LDA', t1)
		env.compiler.push_instruction('ADD', t2)
		t3 = env.compiler.temporary()
		env.compiler.push_instruction('STA', t3)
		return t3

	def eval( self, env ) :
		return self.lhs.eval( env ) + self.rhs.eval( env )

	def display( self, env, depth=0 ) :
		print "%sADD" % (tabstop*depth)
		self.lhs.display( env, depth+1 )
		self.rhs.display( env, depth+1 )
		#print "%s= %i" % (tabstop*depth, self.eval( env ))

	def write( self, env, fd, depth=0 ) :
		fd.write("%sADD\n" % (tabstop*depth))
		self.lhs.write( env, fd, depth+1 )
		self.rhs.write( env, fd, depth+1 )


class Minus( Expr ) :
	'''expression for binary subtraction'''

	def __init__( self, lhs, rhs ) :
		self.lhs = lhs
		self.rhs = rhs

	def translate( self, env ) :
		t1 = self.lhs.translate( env )
		t2 = self.rhs.translate( env )
		env.compiler.push_instruction('LDA', t1)
		env.compiler.push_instruction('SUB', t2)
		t3 = env.compiler.temporary()
		env.compiler.push_instruction('STA', t3)
		return t3
	
	def eval( self, env ) :
		return self.lhs.eval( env ) - self.rhs.eval( env )

	def display( self, env, depth=0 ) :
		print "%sSUB" % (tabstop*depth)
		self.lhs.display( env, depth+1 )
		self.rhs.display( env, depth+1 )
		#print "%s= %i" % (tabstop*depth, self.eval( env ))

	def write( self, env, fd, depth=0 ) :
		fd.write("%sSUB\n" % (tabstop*depth))
		self.lhs.write( env, fd, depth+1 )
		self.rhs.write( env, fd, depth+1 )


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

	def write( self, env, fd, depth=0 ) :
		fd.write("%sFunction Call: %s, args:\n" % (tabstop*depth, self.name))
		for e in self.argList :
			e.write( env, fd, depth+1 )


#-------------------------------------------------------

class Stmt :
	'''Virtual base class for statements in the language'''

	def __init__( self ) :
		raise NotImplementedError(
			'Stmt: pure virtual base class.  Do not instantiate' )

	def translate( self, env ) :
		raise NotImplementedError(
			'Stmt.translate: virtual method.  Must be overridden.' )

	def eval( self, env ) :
		'''Given an environment, evaluates the expression,
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

	def translate( self, env ) :
		t = self.rhs.translate( env )
		env.compiler.push_instruction('LDA', t)
		v = env.compiler.variable(self.name)
		env.compiler.push_instruction('STA', v)
	
	def eval( self, env ) :
		env.st[ self.name ].value = self.rhs.eval( env )

	def display( self, env, depth=0 ) :
		print "%sAssign: %s :=" % (tabstop*depth, self.name)
		self.rhs.display( env, depth+1 )

	def write( self, env, fd, depth=0 ) :
		fd.write("%sAssign: %s :=\n" % (tabstop*depth, self.name))
		self.rhs.write( env, fd, depth+1 )


class DefineStmt( Stmt ) :
	'''Binds a proc object to a name'''

	def __init__( self, name, proc ) :
		self.name = name
		self.proc = proc

	def translate( self, env ) :
		raise NotImplementedError(
			'DefineStmt.translate: Functions are not yet supported.' )
		

	def eval( self, env ) :
		env.ft[ self.name ] = self.proc

	def display( self, env, depth=0 ) :
		print "%sDEFINE %s :" % (tabstop*depth, self.name)
		self.proc.display( env, depth+1 )

	def write( self, env, fd, depth=0 ) :
		fd.write("%sDEFINE %s :\n" % (tabstop*depth, self.name))
		self.proc.write( env, fd, depth+1 )


class IfStmt( Stmt ) :

	def __init__( self, cond, tBody, fBody ) :
		'''expects:
		cond - expression (integer)
		tBody - StmtList
		fBody - StmtList'''
		
		self.cond = cond
		self.tBody = tBody
		self.fBody = fBody

	def translate( self, env ) :
		L1 = env.compiler.label()
		L2 = env.compiler.label()

		t = self.cond.translate( env )
		env.compiler.push_instruction('LDA', t)
		env.compiler.push_instruction('JMN', L1)
		env.compiler.push_instruction('JMZ', L1)
		self.tBody.translate( env )
		env.compiler.push_instruction('JMP', L2)
		env.compiler.prepare_label(L1)
		self.fBody.translate( env )
		env.compiler.prepare_label(L2)

	def eval( self, env ) :
		if self.cond.eval( env ) > 0 :
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

	def write( self, env, fd, depth=0 ) :
		fd.write("%sIF\n" % (tabstop*depth))
		self.cond.write( env, fd, depth+1 )
		fd.write("%sTHEN\n" % (tabstop*depth))
		self.tBody.write( env, fd, depth+1 )
		fd.write("%sELSE\n" % (tabstop*depth))
		self.fBody.write( env, fd, depth+1 )


class WhileStmt( Stmt ) :

	def __init__( self, cond, body ) :
		self.cond = cond
		self.body = body

	def translate( self, env ) :
		L1 = env.compiler.label()
		L2 = env.compiler.label()

		env.compiler.prepare_label(L1)
		t = self.cond.translate( env )
		env.compiler.push_instruction('LDA', t)
		env.compiler.push_instruction('JMN', L2)
		env.compiler.push_instruction('JMZ', L2)
		self.body.translate( env )
		env.compiler.push_instruction('JMP', L1)
		env.compiler.prepare_label(L2)

	def eval( self, env ) :
		while self.cond.eval( env ) > 0 :
			self.body.eval( env )

	def display( self, env, depth=0 ) :
		print "%sWHILE" % (tabstop*depth)
		self.cond.display( env, depth+1 )
		print "%sDO" % (tabstop*depth)
		self.body.display( env, depth+1 )

	def write( self, env, fd, depth=0 ) :
		fd.write("%sWHILE\n" % (tabstop*depth))
		self.cond.write( env, fd, depth+1 )
		fd.write("%sDO\n" % (tabstop*depth))
		self.body.write( env, fd, depth+1 )

#-------------------------------------------------------

class StmtList :
	'''builds/stores a list of Stmts'''

	def __init__( self ) :
		self.sl = []
	
	def insert( self, stmt ) :
		self.sl.insert( 0, stmt )

	def translate( self, env ) :
		for s in self.sl :
			s.translate( env )
	
	def eval( self, env ) :
		for s in self.sl :
			s.eval( env )
	
	def display( self, env, depth=0 ) :
		print "%sSTMT LIST" % (tabstop*depth)
		for s in self.sl :
			s.display( env, depth+1 )

	def write( self, env, fd, depth=0 ) :
		fd.write("%sSTMT LIST\n" % (tabstop*depth))
		for s in self.sl :
			s.write( env, fd, depth+1 )


class Proc :
	'''stores a procedure (formal params, and the body)

	Note that, while each function gets its own environment, we decided not to
	allow side-effects, so, no access to any outer contexts.  Thus, nesting
	functions is legal, but no different than defining them all in the global
	environment.  Further, all calls are handled the same way, regardless of
	the calling environment (after the actual args are evaluated); the proc
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

		new_st = {}
		# bind parameters in new name table (the only things there right now)
			# use zip, bastard
		for i in range( len( args )) :
			new_st[ self.parList[i] ] = args[i].eval( env )

		# evaluate the function body using the new name table and the old (only)
		# function table.  Note that the proc's return value is stored as
		# 'return in its nametable

		self.body.eval( Environment(new_st, env.ft, env.ral_fd) )
		if new_st.has_key( returnSymbol ) :
			return new_st[ returnSymbol ]
		else :
			print "Error:  no return value"
			sys.exit( 2 )
	
	def display( self, env, depth=0 ) :
		print "%sPROC %s :" % (tabstop*depth, str(self.parList))
		self.body.display( env, depth+1 )

	def write( self, env, fd, depth=0 ) :
		fd.write("%sPROC %s :\n" % (tabstop*depth, str(self.parList)))
		self.body.write( env, fd, depth+1 )


class Program :
	
	def __init__( self, stmtList, env ) :
		self.stmtList = stmtList
		self.env = env

	def translate( self ) :
		self.stmtList.translate( self.env )
		self.env.compiler.push_instruction('HLT')
	
	def eval( self ) :
		self.stmtList.eval( self.env )
	
	def dump( self ) :
		print "Dump of Symbol Table"
		print "Name Table"
		for k in self.env.st :
			print "  %s -> %s " % ( str(k), str(self.env.st[k].value) )
#		print "Function Table"
#		for k in self.env.ft :
#			print "  %s" % str(k)

	def display( self, depth=0 ) :
		print "%sPROGRAM :" % (tabstop*depth)
		self.stmtList.display( self.env )

	def write(self, filename) :
	    fd = open(filename, 'w')
	    self.stmtList.write(self.env, fd)

