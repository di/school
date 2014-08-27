#!/usr/bin/python

import json, math, sys
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
import collections

def distance(a, b):
    x_a, y_a = a
    x_b, y_b = b
    return math.sqrt(abs(x_a-x_b)**2 + abs(y_a-y_b)**2)

def parse_file(f):
    data = [[None for x in range(100)] for y in range(1001)]
    for line in f.readlines():
        l = json.loads(line)
        data[l["step"]][l["id"]] = ((l["x"],l["y"]), l["ideal"])
    return data




files = 100
ideal_vs_dist = dict()

for i in range(files):
    print "heatbugs_%d.out" % (i)
    data = parse_file(open("heatbugs_%d.out" % (i), 'r'))

    for step, s in enumerate(data):
        for _id, d in enumerate(s):
            loc, ideal = data[step][_id]
            # Cluster the data a little better
            ideal = math.floor(ideal) - (math.floor(ideal) % 100)
            dists = [distance(loc, x) for x,y in data[step]]
            if ideal not in ideal_vs_dist:
                ideal_vs_dist[ideal] = []
            ideal_vs_dist[ideal].append(sum(dists)/len(dists))


print "Condensing data"
#ideal_vs_dist.sort(key=lambda tup: tup[0])
for ideal in ideal_vs_dist:
    l = ideal_vs_dist[ideal]
    ideal_vs_dist[ideal] = sum(l)/len(l)

ivd = collections.OrderedDict(sorted(ideal_vs_dist.items()))
print "Generating figure"
plt.plot(ivd.keys(), ivd.values())
#plt.show()
plt.xlabel("Ideal Temperature")
plt.ylabel("Average Distance")
plt.title("Average distance to all other bugs vs ideal temperature")
plt.savefig('figure_3.png')
plt.savefig('figure_3.ps')
plt.savefig('figure_3.eps')
plt.savefig('figure_3.pgf')
