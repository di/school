import random
import math

class world:

    def __init__(self, size=100, density=0.3):
        self.size = size
        self.density = density
        self.termites = []
        self.ticks = 0

        ''' Initialize the empty world '''
        self.world = [[0 for x in range(self.size)] for y in range(self.size)]

        ''' Add wood at the correct density '''
        wood_size = int(self.size**2*self.density)

        woods = set()
        while len(woods) < wood_size:
            woods.add((random.randint(0,self.size-1),random.randint(0,self.size-1)))
        for x, y in woods:
            self.world[y][x] = 1

    def add_termite(self, t):
        self.termites.append(t)

    def tick(self):
        self.ticks += 1
        for t in self.termites :
            t.tick(self)

    def wood_adjacent(self, x, y):
        _adj = 0 - self.world[y][x]
        for _x in range(x-1, x+2):
            for _y in range(y-1, y+2):
                if 0 <= _x < self.size and 0 <= _y < self.size:
                    _adj += self.world[_y][_x]
        return _adj

    def take_wood(self, x, y):
        if self.world[y][x]:
            _adj = self.wood_adjacent(x,y)
            if _adj < 5:
                self.world[y][x] = 0
                return 1
            else:
                return 0
        else:
            return 0

    def drop_wood(self, x, y):
        if self.wood_adjacent(x,y) > 2 and not self.world[y][x]:
            self.world[y][x] = 1
            return 0
        else :
            return 1

    def valid_step(self, x, y):
        return 0 <= x < self.size and 0 <= y < self.size

    def pile_count(self):
        woods = set()
        for y in range(self.size):
            for x in range(self.size):
                if self.world[y][x]:
                    woods.add((x,y))
        to_search = set()
        count = 0
        while len(woods) > 0:
            to_search.add(woods.pop())
            count += 1
            while len(to_search) > 0:
                x,y = to_search.pop()
                '''
                for l in [(x-1,y-1), (x, y-1), (x+1, y-1), (x-1, y), (x+1, y),
                    (x-1, y+1), (x, y+1), (x+1, y+1)]:
                '''
                for l in [(x, y-1), (x-1, y), (x+1, y), (x, y+1)]:
                    if l in woods:
                        woods.remove(l)
                        to_search.add(l)
        return count

    def _print(self):
        for y in range(self.size):
            print ' '.join(str(x) for x in self.world[y])
