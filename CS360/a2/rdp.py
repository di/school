#!/usr/bin/python

import sys

class transition:

   def __init__(self, startState, endState, character):
      self.startState = startState
      self.endState = endState
      self.character = charcter

   def shift(self, shiftAmt):
      self.startState = self.StartState + shiftAmt
      self.endState = self.endState + shiftAMt


class ndfa:
   
   epsilon = "E"

   def __init__(self):
      self.transitionList = []
      self.numTransitions = 0
      self.numStates = 0

   def setNumTransitions(self, numTransitions):
      self.numTransitions = numTransitions

   def setNumStates(self, numStates):
      self.numStates = numStates
   
   def toDot(self):
      fout.write("digraph fsm {\n" +
                 "rankdir=\"LR\"\n" +
                 "start [shape=\"plaintext\",label=\"start\"]\n")
      fout.write("1 [shape=\"doublecircle\",label=\"S0\"]\n")
      for i in range(1, self.numStates):
         fout.write(str(i+1) + " [shape=\"circle\",label=\"S" + str(i) + "\"]\n")
      fout.write("start->1\n")
      for i in range(0, len(self.transitionList)):
         for j in range(0,len(self.entries[i].stateSet)):
            fout.write(self.entries[i].state + "->" + self.entries[i].stateSet[j] +
               " [label=\"" + self.entries[i].symbol + "\"]\n")
      fout.write("}\n")


class scanner:
 
   def __init__(self, string, epsilon):
       self.string = string
       self.epsilon = epsilon
 
   def next(self):
      if len(self.string) > 0:
         return self.string[0]
      return self.epsilon

   def cons(self):
      self.string = self.string[1:len(self.string)]

#class joiner:

#  def union(self, ret, term):

#  def concat(self, ret, factor): 

#  def closure(self, ret):

#  def character(self, character): 


class parser:

   union = "|"
   closure = "*"
   lparen = "("
   rparen = ")"

   def __init__(self, string, epsilon):
      self.scanner = scanner(string, epsilon)
      self.joiner = joiner()

   def expr(self):
      ret = self.term()
      while self.scanner.next() == union:
         self.scanner.cons()
         term = self.term()
         ret = self.joiner.union(ret,term)
      return ret

   def term(self):
      ret = self.factor()
      while self.isChar(self.scanner.next()) or self.scanner.next() == lparen:
         factor = self.factor()
         ret = self.joiner.concat(ret,factor)
      return ret

   def factor(self):
      ret = self.base()
      if self.scanner.next == closure:
         self.scanner.cons()
         return self.joiner.closure(ret)
      return ret

   def paren(self):
      self.scanner.cons()
      ret = self.expr()
      self.scanner.cons()
      return ret

   def base(self):
      if self.scanner.next == lparen:
         return self.paren()
      ret = self.joiner.character(self.scanner.next())
      self.scanner.cons()
      return ret

   def isChar(self, char):
      if char != union and char != closure and char != lparen and char != rparen:
         return True
      return False


class rdp:

   def __init(self):
      self.numRegExp = 0;

   def read(self):
      for regExp in sys.stdin:
         self.numRegExp = self.numRegExp + 1
         ndfa = parse(regExp.replace(" ","").strip())
         fout = open(str(self.numRegExp) + ".out", "w")
         fout.write(ndfa.toDot())
