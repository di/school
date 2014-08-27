#!/usr/bin/python

import json, math
import matplotlib.pyplot as plt

def distance(a, b):
    x_a, y_a = a
    x_b, y_b = b
    return math.sqrt(abs(x_a-x_b)**2 + abs(y_a-y_b)**2)

def parse_file(f):
    data = [[None for x in range(100)] for y in range(1001)]
    for line in f.readlines():
        l = json.loads(line)
#        print "%d %d" % (l["step"], l["id"])
        data[l["step"]][l["id"]] = (l["x"],l["y"])
    dist_arr = []
    for step, d in enumerate(data):
        total = 0
        count = 0
        for _id_a, loc_a in enumerate(d):
            count += 1
            sub_total = 0
            sub_count = 0
            for _id_b, loc_b in enumerate(d):
                #print '\t\t', loc_a, loc_b, distance(loc_a, loc_b)
                sub_count += 1
                sub_total += distance(loc_a, loc_b)
            #print '\t', _id_a, sub_total/sub_count
            total += sub_total/sub_count
        dist_arr.append(total/count)
    return dist_arr

files = 100
steps = 1001
totals = [0 for x in range(steps)]

for i in range(files):
    dist_arr = parse_file(open("heatbugs_%d.out" % (i), 'r'))
    for i, x in enumerate(dist_arr):
        totals[i] += x

for i, x in enumerate(totals):
    totals[i] = totals[i]/files

plt.plot(range(1001),totals)
plt.show()



