#!/usr/bin/python

import termites
import matplotlib
matplotlib.use("Qt4Agg")
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from scipy import stats
import math

n = 100
res = None
for i in range(n):
    if res is None:
        res = [(a,[b[0]]) for a,b in termites.run(e=1000)]
    else :
        res = [(a[0], a[1] + [b[1][0]]) for a,b in zip(res, termites.run(e=1000))]

ci = []
for x in res:
    i, s = x
    n, min_max, mean, var, skew, kurt = stats.describe(np.array(s))
    std=math.sqrt(var)
    R = stats.norm.interval(0.10,loc=mean,scale=std)
    ci.append((i, R))

x, y = zip(*[(a, sum(b)/n) for a,b in res])
min_ci = [b[0] for a, b in ci]
max_ci = [b[1] for a, b in ci]
plt.plot(np.array(x), np.array(y))
plt.plot(np.array(x), np.array(min_ci))
plt.plot(np.array(x), np.array(max_ci))
plt.title("Average Pile Changes Over Time")
plt.xlabel("Iteration")
plt.ylabel("Average Number of Piles")
plt.show()
