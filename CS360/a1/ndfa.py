#!/usr/bin/python
import sys
epsilon = "EPSILON"

class entry:
   def __init__(self):
      self.state = None
      self.symbol = None
      self.stateSet = []

   def printOut(self):
      printString = ""
      printString += "(" + self.state + "," + self.symbol + ",("
      for i in range(0, len(self.stateSet)):
         if (i != 0):
            printString += ","
         printString += self.stateSet[i]
      printString += "))"
      print(printString)

class ndfa:

   def __init__(self):
      self.numStates = None
      self.numEntries = None
      self.entries = []
      self.acceptingState = None

      self.testStrings = []

   if len(sys.argv) < 3:
      sys.exit("Must provide a input file and action (USAGE: ndfa.py ACTION FILENAME)")

   def read(self):
      fin = open(sys.argv[2], "r")
      self.numStates = int(fin.readline())
      self.acceptingState = str(int(self.numStates)-1)
      self.numEntries = int(fin.readline())

      for l in fin.readlines():
         self.process(l)
   
   def exportToGraph(self):
      fout = open(sys.argv[2][:sys.argv[2].find(".")] + ".out", "w")
      fout.write("digraph fsm {\n" +
                 "rankdir=\"LR\"\n" +
                 "start [shape=\"plaintext\",label=\"start\"]\n")
      fout.write("1 [shape=\"doublecircle\",label=\"S0\"]\n")
      for i in range(1, self.numStates):
         fout.write(str(i+1) + " [shape=\"circle\",label=\"S" + str(i) + "\"]\n")
      fout.write("start->1\n")
      for i in range(0, len(self.entries)):
         for j in range(0,len(self.entries[i].stateSet)):
            fout.write(self.entries[i].state + "->" + self.entries[i].stateSet[j] + 
                  " [label=\"" + self.entries[i].symbol + "\"]\n")
      fout.write("}\n")

   def process(self, l):
      l = l.strip("\n")

      currentEntry = entry()

      stateAccepted = False
      symbolAccepted = False
      epsilonAccepted = False
      
      if (l[0] == "("):
         for i in range(0, len(l)):
            if (epsilonAccepted and l[i] == ","):
               epsilonAccepted = False
            if (l[i] != "(" and l[i] != ")" and l[i] != "," and not epsilonAccepted):
               if (not stateAccepted):
                  currentEntry.state = l[i]
                  stateAccepted = True
               elif (not symbolAccepted):
                  currentEntry.symbol = l[i]
                  symbolAccepted = True
                  if (l[i] == epsilon[0]):
                     epsilonAccepted = True
               elif (l[i] != " "):
                  currentEntry.stateSet.append(l[i])

         currentEntry.printOut()
         self.entries.append(currentEntry)
      else:
         self.testStrings.append(l)

   def isAccepted(self, string, state):
      for i in range(0, len(self.entries)):
         e = self.entries[i]
         if (e.state == state and (e.symbol == string[0] or e.symbol == epsilon[0])):
            if (len(string) == 1):
               if (self.acceptingState in e.stateSet):
                  return True
            else:
               for j in range(0, len(e.stateSet)):
                  start = 1
                  if(e.symbol == epsilon[0]):
                     start = 0
                  if(self.isAccepted(string[start:len(string)],e.stateSet[j])):
                     return True
      return False

   def simulate(self):
      for i in range(0, len(self.testStrings)):
         if(self.isAccepted(self.testStrings[i],"0")):
            print "\"" + self.testStrings[i] + "\" is accepted"
         else:
            print "\"" + self.testStrings[i] + "\" is not accepted"

myNDFA = ndfa()
myNDFA.read()

if (sys.argv[1] == "graph"):
   myNDFA.exportToGraph()
elif (sys.argv[1] == "sim"):
   myNDFA.simulate()
else:
   print "Unknown action provided"
