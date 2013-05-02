#!/usr/bin/python
# -*- coding: utf-8 -*-
import sys
import string
import math
import numpy as np
from itertools import izip
import operator
import random
import bisect

q = 1.0
alpha = 1.0
beta = 10.0
rho = 0.1

def accumulate(iterable, func=operator.add):
    it = iter(iterable)
    total = next(it)
    yield total
    for element in it:
        total = func(total, element)
        yield total

class ant:

    def __init__(self, _id, size, start=0):
        self._id = _id
        self.size = size
        self.start = random.choice(range(size))
        self.reset()

    def reset(self):
        self.at = self.start
        self.tour = [self.start]
        self.tour_length = 0
        self.remaining = range(self.size)
        self.remaining.remove(self.start)

    def do_tour(self, world):
        while self.remaining :
            probs = np.array([world.p(self.at, x) for x in self.remaining])
            probs /= sum(probs)
            cumdist = list(accumulate(probs))
            up_next = self.remaining[bisect.bisect(cumdist, random.random() * cumdist[-1])]

            self.tour_length += world.get_distance(self.at, up_next)
            self.at = up_next
            self.tour.append(self.at)
            self.remaining.remove(self.at)

        self.tour_length += world.get_distance(self.at, self.start)
        self.tour.append(self.start)
        return self.tour_length

    def lay_pher(self, world):
        for x, y in izip(self.tour, self.tour[1:]):
            world.set_pher(x, y, q/self.tour_length)

class world:

    def __init__(self, filename, cpu):
        lines = open(filename, 'r').readlines()
        while lines[0][0] not in string.digits:
           lines.pop(0) 
        self.size = len(lines)

        self.x_coords = []
        self.y_coords = []
        for l in lines:
            try :
                i, x, y = l.strip().split()
            except :
                pass
            self.x_coords.append(float(x))
            self.y_coords.append(float(y))

        self.ants = [ant(i, self.size) for i,_ in enumerate(range(5))]
        self.distance = np.zeros((self.size, self.size))
        for x in range(self.size):
            for y in range(self.size):
                self.distance[x, y] = self.make_distance(x, y)
        self.pher = np.ones((self.size, self.size))
        self.shortest_tour = None
        self.shortest_tour_length = sys.maxint

    def make_distance(self, i, j):
        x_delta = abs(self.x_coords[i] - self.x_coords[j])
        y_delta = abs(self.y_coords[i] - self.y_coords[j])
        dist = math.sqrt(x_delta**2 + y_delta**2)
        if dist == 0.0:
            dist = 1e-20
        return dist

    def get_distance(self, i, j):
        return self.distance[i][j]

    def set_pher(self, x, y, v):
        self.pher[x][y] += v
        self.pher[y][x] += v

    def p(self, x, y):
        return (self.pher[x][y]**alpha)*((1.0/self.distance[x][y])**beta)

    def tick(self):
        for ant in self.ants:
            ant.do_tour(self)
            if ant.tour_length < self.shortest_tour_length:
                self.shortest_tour = ant.tour
                self.shortest_tour_length = ant.tour_length
                print self.shortest_tour_length

        self.pher *= (1 - rho)
        for a in self.ants:
            a.lay_pher(self)
            a.reset()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print("usage: python travellingAnts.py input.tsp maxseconds")
        sys.exit(0)

    w = world(sys.argv[1], sys.argv[2])

    while True:
        w.tick()
