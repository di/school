#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

y = [1134681.68891, 1117079.78528, 1116839.22845, 1116708.79521, 1101636.91363,
1087557.66768]
x = [208.444579124, 834.131259203, 2913.40504098, 5407.13800502, 6446.09419298,
7692.1965692]

plt.plot(np.array(x), np.array(y), 'o-')
plt.title("CPU time vs. Path Length for Argentina using ACO")
plt.xlabel("Time (seconds)")
plt.ylabel("Path length")
plt.show()
