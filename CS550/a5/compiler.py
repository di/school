
import string
from symbols import *

#####################################################################

class Compiler :
    def __init__(self, ral_filename, mem_filename) :
        self.ops = {}
        self.ral = []
        self.mem = SymbolTable()

        self.opt_enabled = False
        self.prepared_label = None

        self.register_op_type('LDA', "ac <- memory[ %s ]")
        self.register_op_type('LDI', "ac <- memory[memory[ %s ]]")
        self.register_op_type('STA', "memory[ %s ] <- ac")
        self.register_op_type('STI', "memory[memory[ %s ]] <- ac")
        self.register_op_type('ADD', "ac += memory[ %s ]")
        self.register_op_type('SUB', "ac -= memory[ %s ]")
        self.register_op_type('MUL', "ac *= memory[ %s ]")
        self.register_op_type('JMP', "goto %s")
        self.register_op_type('JMZ', "if ac == 0, goto %s")
        self.register_op_type('JMN', "if ac < 0, goto %s")
        self.register_op_type('HLT', "Halt execution")

    # enable optimization
    def enable_optimization(self) :
        self.opt_enabled = True

    # store a label to be associated with the
    # next instruction that is pushed
    def prepare_label(self, label) :
        self.prepared_label = label

    # register an optype with the compiler
    def register_op_type(self, op_string, comment) :
        self.ops[op_string] = OpType(op_string, comment)

    # push an instruction onto the ral instruction list
    def push_instruction(self, op_string, sym = None) :
        self.ral.append(Instruction(self.ops[op_string], 
                                    sym, 
                                    self.prepared_label))
        self.prepared_label = None
        return self.ral[-1]

    # return a constant if it exists, else create a new one
    def constant(self, value) :
        if not self.mem.constants.has_key(value) :
            self.mem.constants[value] = Constant(value)
        return self.mem.constants[value]

    # return a variable if it exists, else create a new one
    def variable(self, name) :
        if not self.mem.variables.has_key(name) :
            self.mem.variables[name] = Variable(name)
        return self.mem.variables[name]

    # create a new temporary
    def temporary(self) :
        sym = Temporary(len(self.mem.temporaries))
        self.mem.temporaries[sym.name] = sym
        return sym

    # create a new label
    def label(self) :
        sym = Label(len(self.mem.labels))
        self.mem.labels[sym.name] = sym
        return sym

    # optimize the ral instruction list
    def optimize(self) :
        if self.opt_enabled :
            # peephole optimization
            i = 0
            while i < len(self.ral)-1 :
                if (
                    # if direct store followed by direct load 
                    (((self.ral[i].op_type.op_string == 'STA') and
                      (self.ral[i+1].op_type.op_string == 'LDA')) or
                    # or indirect store followed by indirect load
                     ((self.ral[i].op_type.op_string == 'STI') and
                      (self.ral[i+1].op_type.op_string == 'LDI'))) and
                    # and the arguments refer to the same symbol
                    (self.ral[i].sym == self.ral[i+1].sym)) :
                    # then delete the load operation
                    del self.ral[i+1]
                i += 1


    # link symbols with memory locations and 
    # labels with instruction locations
    def link(self) :
        l = Linker()
        self.mem.link(l)

        for inst in self.ral :
            inst.link(l)

    # write memory file
    def write_mem(self, mem_filename) :
        mem_fd = open(mem_filename, 'w')
        self.mem.write(mem_fd)

    # write instructions to file
    def write_ins(self, ral_filename) :
        ral_fd = open(ral_filename, 'w')

        # write input code into comments at the
        # top of the ral instruction file
        for line in self.code :
            ral_fd.write("; " + line)
        for inst in self.ral :
            inst.write(ral_fd)

#####################################################################

class Linker :
    def __init__(self) :
        self.ral_index = 0
        self.mem_index = 0

    def add_symbol(self, sym) :
        self.mem_index += 1
        sym.addr = self.mem_index

    def add_instruction(self, inst) :
        self.ral_index += 1
        if inst.lbl != None :
            inst.lbl.addr = self.ral_index


#####################################################################

class OpType :
    def __init__(self, op_string, comment) :
        self.op_string = op_string
        self.comment = comment

    def arg_expected(self) :
        return string.find(self.comment, '%s') != -1

    def write(self, fd, sym) :
        if self.arg_expected() :
            address = str(sym.addr)
            comment = self.comment % sym.name
        else :
            address = ' '
            comment = self.comment

        fd.write(self.op_string + 
                 '\t' + address + ';' +
                 '\t# ' + comment + '\n')

#####################################################################

class Instruction :
    def __init__(self, op_type, sym, lbl = None) :
        if op_type.arg_expected() and sym == None :
            print "Error: arg expected for op_type " + \
                op_type.op_string + " but none provided"
            exit(1)
        self.op_type = op_type
        self.sym = sym
        self.lbl = lbl

    def link(self, linker) :
        linker.add_instruction(self)

    def write(self, fd) :
        self.op_type.write(fd, self.sym)

#####################################################################

class SymbolTable :
    def __init__(self) :
        self.constants = {}
        self.variables = {}
        self.temporaries = {}
        self.labels = {}

    def link(self, linker) :
        for key, sym in self.constants.items() :
            linker.add_symbol(sym)

        for key, sym in self.variables.items() :
            linker.add_symbol(sym)

        for key, sym in self.temporaries.items() :
            linker.add_symbol(sym)


    def write(self, fd) :
        for key, sym in self.constants.items():
            fd.write(str(sym.addr) + 
                     "\t" + str(sym.value) + 
                     "; constant " + sym.name + "\n")

        for key, sym in self.variables.items():
            fd.write(str(sym.addr) + 
                     "\t" + str(sym.value) +  
                     "; variable " + sym.name + "\n")

        for key, sym in self.temporaries.items():
            fd.write(str(sym.addr) + 
                     "\t" + str(sym.value) +  
                     "; temporary " + sym.name + "\n")


#####################################################################





if __name__ == '__main__' :
    c = Compiler('ral.txt', 'mem.txt')

    c.enable_optimization()

    v1 = c.variable("a")
    c.push_instruction('LDA', v1)

    v2 = c.variable("b")
    c.push_instruction('SUB', v2)

    L1 = c.label()
    c.push_instruction('JMZ', L1)

    c0 = c.constant(0)
    c.push_instruction('LDA', c0)

    v3 = c.variable("return")
    c.push_instruction('STA', v3)

    c.push_instruction('HLT')

    c1 = c.constant(1)
    c.prepare_label(L1)
    c.push_instruction('LDA', c1)

    c.push_instruction('STA', v3)
    c.push_instruction('LDA', v3) # this should get optimized out
    c.push_instruction('HLT')

    v1.value = 1
    v2.value = 1

    t = c.temporary()
    t = c.temporary()
    t = c.temporary()
    t = c.temporary()

    c.optimize()
    c.link()
    c.write()


