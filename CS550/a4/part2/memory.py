class Cell :
    def __init__(self, value, nextptr = -1, lst = False) :
        self.value = value
        self.lst = lst
        self.nextptr = nextptr
        self.pos = None
        self.marked = False

    def __str__(self) :
        return '[%s %s %s %s]' % (self.value, self.lst, self.nextptr, self.marked)

class Allocation :
    NUMBER = 1
    LIST = 2
    EMPTY_LIST = 3
    def __init__(self, value, vtype) :
        self.value = value
        self.vtype = vtype

    def string(self, mem) :
        if self.vtype == Allocation.NUMBER :
            return self.value
        elif self.vtype == Allocation.LIST :
            index = self.value
            els = []
            while index != -1 :
                if mem.get(index).lst :
                    els.append(Allocation(mem.get(index).value, Allocation.LIST).string(mem))
                else :
                    els.append(mem.get(index).value)
                index = mem.get(index).nextptr
            return '[' + ', '.join(map(str, els)) + ']'
        elif self.vtype == Allocation.EMPTY_LIST :
            return '[]'
        
class Memory :
    def __init__(self, size) :
        self.mem = [Cell(0, i + 1) for i in range(0, size)]
        self.mem[len(self.mem) - 1].nextptr = -1
        self.next_avail = 0
        self.last_alloc = 0

    def get(self, i) :
        return self.mem[i]

    def sweep(self) :
        last = -1
        
        for i in range(0, len(self.mem)):
            if not self.mem[i].marked :
                self.mem[i] = Cell(0, last)
                last = i
                self.mem[i].marked = False
        self.next_avail = last

    def mark(self, index) :
        while index != -1 :
            self.mem[index].marked = True

            if self.mem[index].lst :
                self.mark(self.mem[index].value)
            index = self.mem[index].nextptr

    def allocate(self, cell) :
        if self.next_avail < 0 :
            return -1

        next_free = self.mem[self.next_avail].nextptr
        self.mem[self.next_avail] = cell
        cell.pos = self.next_avail
        self.last_alloc = self.next_avail

        self.next_avail = next_free
        if self.next_avail >= len(self.mem) :
            self.next_avail = -1

        return cell.pos

    def reallocate(self, index, cell) :
        if index > len(self.mem) :
            return False

        cell.nextptr = self.mem[index].nextptr
        self.mem[index] = cell

    def __str__(self) :
        s = ''
        for i, c in enumerate(self.mem) :
            s += '%s: %s\n' % (i, c.__str__())
        s += 'Next: %d' % self.next_avail
        return s

if __name__ == '__main__' :
    mem = Memory(15)
    def test_alloc(l) :
        last_i = -1
        for i in range(len(l) - 1, -1, -1) :
            if type(l[i]) == type([]) :
                last_i = mem.allocate(Cell(test_alloc(l[i]), last_i, True))
            else :
                last_i = mem.allocate(Cell(l[i], last_i, False))
        return last_i 

    '''pos = test_alloc([10, [1, 2, [3, 4]], 5, [6]])
    print mem
    print 'Array at', pos
    #rebind index 5 which is [3,4] to [99, 98]
    mem.reallocate(5, Cell(test_alloc([99, 98]), None, True))
    print mem
    mem.sweep([pos])
    print mem'''
    print test_alloc([])
    print mem
