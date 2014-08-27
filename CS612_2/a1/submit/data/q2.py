#!/usr/bin/python

import json, math
import matplotlib.pyplot as plt

def distance(a, b):
    x_a, y_a = a
    x_b, y_b = b
    return math.sqrt(abs(x_a-x_b)**2 + abs(y_a-y_b)**2)

def parse_file(f):
    data = [None for x in range(100)]
    for line in f.readlines():
        l = json.loads(line)
        if l["step"] == 1000:
            data[l["id"]] = (l["x"],l["y"])
    neighbors = [[] for x in range(100)]
    for _id_a, loc_a in enumerate(data):
        for _id_b, loc_b in enumerate(data):
            neighbors[_id_a].append(distance(loc_a, loc_b))
    neighbors = [sorted(x) for x in neighbors]
    return neighbors


files = 100
totals = [0 for x in range(100)]

for i in range(files):
    # The sorted neighbor distance list for every bug
    neighbors = parse_file(open("heatbugs_%d.out" % (i), 'r'))

    total_dist = [0 for x in range(100)]
    for n in neighbors:
        for i in range(100):
            total_dist[i] += n[i] 
    avg_dist = [t/100 for t in total_dist]


    blah = [0 for x in range(100)]
    for x in range(100):
        for e in avg_dist[:x]:
            blah[x] += e

    for i in range(99):
        blah[i+1] = blah[i+1]/(i+1)


    # Total across all files
    for i, x in enumerate(avg_dist):
        totals[i] += x

#Average across all files
totals = [x/files for x in totals]

plt.plot(range(100),totals)
plt.show()
