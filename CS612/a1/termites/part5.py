#!/usr/bin/python

import termites
import matplotlib
matplotlib.use("Qt4Agg")
import matplotlib.pyplot as plt
import numpy as np

n = 10
avg = []

for n_termites in range(1, 50):
    res = None
    for i in range(n):
        if res is None:
            res = [(a, [b[0]]) for a, b in termites.run(e=1000)]
        else:
            res = [(a[0], a[1] + [b[1][0]]) for a, b in zip(res, termites.run(e=1000, n_termites=n_termites))]

    _, end = res[-1]
    avg.append((n_termites, sum(end)/n))

x, y = zip(*avg)

plt.plot(np.array(x), np.array(y))

plt.title("Average Piles Left After 100,000 Iterations")
plt.xlabel("Number of Termites")
plt.ylabel("Average Number of Piles")
plt.show()
