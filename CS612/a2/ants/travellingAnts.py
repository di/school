#!/usr/bin/python
import sys
import string
import math

class ant:

    def __init__(self, _id):
        self._id = _id
        self.i = 0
        self.tour = []

    def tick(self, world):
        print("ant-%d at %d" % (self._id, self.i))


class world:

    def __init__(self, filename, cpu):
        lines = open(filename, 'r').readlines()
        while lines[0][0] not in string.digits:
           lines.pop(0) 
        self.size = len(lines)

        self.g = [[None for _ in range(self.size)] for _ in range(self.size)]
        x_coords = []
        y_coords = []
        for l in lines:
            i, x, y = l.strip().split()
            x_coords.append(float(x))
            y_coords.append(float(y))
        for i in range(self.size):
            for j in range(self.size):
                x_delta = abs(x_coords[i] - x_coords[j])
                y_delta = abs(y_coords[i] - y_coords[j])
                self.g[i][j] = math.sqrt(x_delta**2 + y_delta**2)

        self.ants = [ant(i) for i,_ in enumerate(range(5))]
        self.pher = [[0.0 for _ in range(self.size)] for _ in range(self.size)]

    def distance(self, i, j):
        return self.g[i][j]

    def tick(self):
        for ant in self.ants:
            ant.tick(self)


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("usage: python travellingAnts.py input.tsp maxseconds")
        sys.exit(0)

    w = world(sys.argv[1], sys.argv[2])

    while True:
        w.tick()
        break
