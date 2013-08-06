#!/usr/bin/python

from __future__ import division
import matplotlib
matplotlib.use('PDF')
import matplotlib.pyplot as plt
import matplotlib.patheffects as PathEffects
from matplotlib  import cm
import math

countries = ["Australia", "Austria", "Belgium", "Canada", "Chile", "Czech Rep.", "Denmark", "Estonia", "Finland", "France", "Germany", "Greece", "Hungary", "Iceland", "Ireland", "Israel", "Italy", "Japan", "S. Korea", "Luxembourg", "Mexico", "Netherlands", "New Zealand", "Norway", "Poland", "Portugal", "Slovak Republic", "Slovenia", "Spain", "Sweden", "Switzerland", "Turkey", "UK", "US"]
life_expectancy = [81.6, 80.4, 80.1, 81, 78.8, 77.4, 79, 75, 80.1, 81.5, 80.3, 80.3, 74.4, 81.8, 80.2, 81.5, 82, 83, 80.4, 80.7, 74, 80.8, 80.8, 81, 75.8, 79.6, 75.3, 79.3, 81.8, 81.5, 82.3, 74.1, 80.4, 78.5]
doctor_consults = [6.6, 6.9, 7.6, 7.7, 3.2, 11.2, 4.6, 6.3, 4.2, 6.7, 9.2, None, 11.9, 6.4, None, 6.2, None, 13.1, 12.9, 6.7, 2.9, 5.7, None, 5.2, 6.8, 4, 11.6, 6.6, 7.5, 2.9, None, 7.3, 5, 4.1]
spending = [3734.3511, 4344.8811, 3874.4303, 4309.3453, 1282.7369, 2039.1423, 4390.1844, 1370.6609, 3259.0884, 3961.6686, 4187.1722, 2977.2291, 1566.5622, 3597.1002, 4036.7437, 1990.7832, 3029.5213, 3025.1583, 1894.7449, 4755.3139, 956.7116, 4870.0488, 2983.9616, 5299.8684, 1355.6787, 2691.7105, 2063.4102, 2470.1625, 3080.0395, 3702.9602, 5156.7212, None, 3455.6393, 8005.6601]
health_coverage = [ True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, True, False, True, True, True, True, True, True, True, True, True, True, True, True, False]
exclude = []

scale = 4.0
plt.figure(figsize=(scale*4, scale*3))
data = [countries, life_expectancy, doctor_consults, spending, health_coverage]
for d in data:
    for i in xrange(len(d) - 1, -1, -1):
        if d[i] is None:
            exclude.append(countries[i])
            for l in data:
                del l[i]

for X, Y, Z, S in zip(spending, life_expectancy, countries, doctor_consults):
    plt.annotate('{}'.format(Z), xy=(X,Y), xytext=(0,0), ha='center', va='center',
        textcoords='offset points', size=6,
        path_effects=[PathEffects.withStroke(linewidth=3,foreground="w")])

plt.scatter(spending, life_expectancy, s=[70*n**2 for n in doctor_consults], facecolors='none', c=[health_coverage], cmap = cm.jet_r)

# Averages
avg_le = sum(life_expectancy) / len(life_expectancy)
avg_spending = sum(spending) / len(spending)

plt.plot([0, 9000], [avg_le, avg_le], 'k:')
plt.plot([avg_spending, avg_spending], [72, 84], 'k:')
plt.text(avg_spending, avg_le, "AVERAGE", fontsize=6, ha='center', va='center',
        path_effects=[PathEffects.withStroke(linewidth=3,foreground="w")])

# Legend
labels = ["Nation with universal health coverage", "Nation without universal health coverage", "Average number of doctor consultations per year\nMinimum: 2.9\nMaximum: 13.1", ""]
x = [7000 for _ in range(len(labels))]
y = [76, 75, 73.5, 73.5]
c = [True, False, True, True]
s = [min(doctor_consults), min(doctor_consults), min(doctor_consults), max(doctor_consults)]

for X, Y, Z, S in zip(x, y, labels, s):
    plt.annotate('{}'.format(Z), xy=(X,Y), xytext=(7*S,0), ha='left', va='center',
        textcoords='offset points', size=6,
        path_effects=[PathEffects.withStroke(linewidth=3,foreground="w")])

plt.scatter(x, y, s=[70*n**2 for n in s], facecolors='none', c=c, cmap = cm.jet_r)

plt.xlim([0,9000])
plt.ylim([72,84])
plt.ylabel('Average Life Expectancy at Birth, Total Population')
plt.xlabel('Total health expenditure per capita, US$ PPP')

plt.text(8900,72.25, "Source: OECD Health Data 2013 (http://www.oecd.org/).\nExcludes %s and %s due to insufficient data." % (', '.join(exclude[:-1]), exclude[-1]), fontsize=6, ha='right')

plt.savefig('newgraph', bbox_inches='tight', pad_inches=0)
#plt.show()
