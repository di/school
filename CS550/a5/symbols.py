
class Symbol (object) :
    def __init__(self, name, value) :
        self.name = name
        self.value = value
        self.addr = None # unknown til link

class Constant (Symbol) :
    def __init__(self, value) :
        super(Constant, self).__init__("c" + str(value), value)

class Variable (Symbol) :
    def __init__(self, name) :
        super(Variable, self).__init__(name, 0)

class Temporary (Symbol) :
    def __init__(self, count) :
        super(Temporary, self).__init__("t" + str(count), 0)

class Label (Symbol) :
    def __init__(self, count) :
        super(Label, self).__init__("L" + str(count), None)

SymbolRank = {1:Constant, 2:Variable, 3:Temporary, 4:Label}

# L.sort(key=lambda sym: SymbolRank[type(sym)])
# sorted(L, key=lambda sym: SymbolRank[type(sym)])

