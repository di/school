#!/usr/bin/python

import json, math
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist
from scipy.cluster.hierarchy import linkage, fcluster
from numpy import unique
from pylab import *

def parse_file(f):
    x = []
    y = []
    avg = [[] for i in range(101)]
    for line in f.readlines():
        l = json.loads(line)
        x.append(l['evap'])
        y.append(l['foods'])
        avg[int(l['evap']*100)].append(l['foods'])
    avg = [sum(a)/len(a) if len(a) > 0 else 0 for a in avg[1:]]
    return x, y, avg

x, y, avg = parse_file(open("ants.out", 'r'))
plt.plot(x, y, 'b.')

plt.ylim(6000, 13000)
fit = polyfit(x, y, 1)
print fit
fit_fn = poly1d(fit)

plt.plot(x, fit_fn(x), '--r')
plt.show()
plt.xlabel("Evaporation Rate")
plt.ylabel("Number of Foods Collected")
plt.title("Ants Forage: Foods Collected vs. Pheremone Evaporation Rate")
plt.savefig('a3.png')
plt.savefig('a3.eps')
plt.savefig('a3.ps')
plt.savefig('a3.pgf')
