from __future__ import division
import random
import math
from wood import wood

class world:

    def __init__(self, size=100, density=0.3, n_woods=1):
        self.size = size
        self.density = density
        self.termites = []
        self.ticks = 0

        ''' Initialize the empty world '''
        self.world = [[None for x in range(self.size)] for y in range(self.size)]

        ''' Add wood at the correct density '''
        wood_size = int(self.size**2*self.density)

        woods = set()
        while len(woods) < wood_size:
            woods.add((random.randint(0,self.size-1),random.randint(0,self.size-1)))
        wood_types = [wood(i) for i in range(n_woods)]
        for x, y in woods:
            self.world[y][x] = wood_types[random.randint(0,n_woods-1)]

    def add_termite(self, t):
        self.termites.append(t)

    def tick(self):
        self.ticks += 1
        for t in self.termites :
            t.tick(self)

    def has_wood(self, x, y, wood_type=None):
        cell = self.world[y][x]
        return cell is not None and (wood_type is None or cell.wood_type is wood_type)

    def wood_adjacent(self, x, y, wood_type=None):
        _adj = 0 - self.has_wood(x, y)
        if wood_type is None:
            wood_type = self.world[y][x].wood_type
        for _x in range(x-1, x+2):
            for _y in range(y-1, y+2):
                if 0 <= _x < self.size and 0 <= _y < self.size:
                    _adj += self.has_wood(_x, _y, wood_type)
        return _adj

    def take_wood(self, x, y):
        ret = self.world[y][x]
        self.world[y][x] = None
        return ret

    def drop_wood(self, x, y, wood):
        self.world[y][x] = wood
        return None

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
        type_count = 0
        mixed_count = 0
        types = set()
        while len(woods) > 0:
            x,y = woods.pop()
            to_search.add((x,y))
            count += 1
            while len(to_search) > 0:
                x,y = to_search.pop()
                types.add(self.world[y][x].wood_type)
                for l in [(x, y-1), (x-1, y), (x+1, y), (x, y+1)]:
                    if l in woods:
                        woods.remove(l)
                        to_search.add(l)
            type_count += len(types)
            if len(types) > 1:
                mixed_count += 1
            types.clear()
#        print count, type_count, type_count/count, mixed_count, mixed_count/count
        return count, mixed_count

    def _print(self):
        for y in range(self.size):
            print ' '.join(str(x) for x in self.world[y])
