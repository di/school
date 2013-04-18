#!/usr/bin/python

import termites
import matplotlib
matplotlib.use("Qt4Agg")
import matplotlib.pyplot as plt
import numpy as np

n = 100
res = None
for i in range(n):
    if res is None:
        res = [(a,[b]) for a,b in termites.run(e=1000)]
    else :
        res = [(a[0], a[1] + [b[1]]) for a,b in zip(res, termites.run(e=1000))]

x, y = zip(*[(a, sum(b)/n) for a,b in res])
plt.plot(np.array(x), np.array(y))
plt.title("Average Pile Changes Over Time")
plt.xlabel("Iteration")
plt.ylabel("Average Number of Piles")
plt.show()
