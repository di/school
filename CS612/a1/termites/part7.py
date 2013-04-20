#!/usr/bin/python
from __future__ import division
import termites
import matplotlib
matplotlib.use("Qt4Agg")
import matplotlib.pyplot as plt
import numpy as np
import scipy as sp
from scipy import stats
import math

n = 10
for n_woods in range(2,11):
    res = None
    for i in range(n):
        if res is None:
            res = [(a,[b[1]/b[0]]) for a,b in termites.run(e=1000, n_termites=10, n_woods=n_woods)]
        else :
            res = [(a[0], a[1] + [b[1][1]/b[1][0]]) for a,b in zip(res, termites.run(e=1000, n_termites=10, n_woods=n_woods))]

    x, y = zip(*[(a, sum(b)/n) for a,b in res])
    plt.plot(np.array(x), np.array(y))
    print n_woods

plt.title("Percentage of Mixed-Type Pile Changes Over Time for 2-10 Wood Types")
plt.xlabel("Iteration")
plt.ylabel("Percentage of Mixed-Type Piles")
plt.show()
