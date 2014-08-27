#!/usr/bin/python

import json, math
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from scipy.spatial.distance import pdist
from scipy.cluster.hierarchy import linkage, fcluster
from numpy import unique

def distance(a, b):
    x_a, y_a = a
    x_b, y_b = b
    return math.sqrt(abs(x_a-x_b)**2 + abs(y_a-y_b)**2)

def parse_file(f):
    clus = [None for x in range(1001)]
    data = [[None for x in range(100)] for y in range (1001)]
    for line in f.readlines():
        l = json.loads(line)
        data[l["step"]][l["id"]] = (l["x"],l["y"])
    
    for i, stepset in enumerate(data):
        Y = pdist(stepset)
        Z = linkage(Y)
        clus[i] = len(unique(fcluster(Z, 0.017*Y.mean())))

    return clus

files = 100

avg_clus = [0 for x in range(1001)]
for i in range(files):
    # The sorted neighbor distance list for every bug
    clus = parse_file(open("heatbugs_%d.out" % (i), 'r'))
    print "heatbugs_%d.out" % (i)
    for i, x in enumerate(clus):
        avg_clus[i] += x

avg_clus = [x/files for x in avg_clus]


plt.plot(range(1001),avg_clus, 'b.')
#plt.show()
plt.xlabel("Steps")
plt.ylabel("Number of Clusters")
plt.title("Nuber of Clusters at a given Timestep")
plt.savefig('figure_6.png')
plt.savefig('figure_6.eps')
plt.savefig('figure_6.ps')
plt.savefig('figure_6.pgf')
