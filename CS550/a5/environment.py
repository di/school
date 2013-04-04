from compiler import *

class Environment: 
    def __init__(self, st, ft, ral_filename, mem_filename) :
        self.st = st
#        self.ft = ft
        self.compiler = Compiler(ral_filename, mem_filename)


