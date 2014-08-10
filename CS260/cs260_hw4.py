#!/usr/bin/python

B = 16

def h(i, k):
    if i == 1:
        return 6
    p = h(i-1, k)
    if 2*p < B:
        return 2*p
    return (2*p-B)^k

for k in range(1, B):
    if len(set([h(i, k) for i in range(1, B)])) == B-1:
        print "k=%d" % (k)

print [h(i, k) for i in range(1, B)]

for i in range(1, 20):
    l = []
    for x in range(1, 16):
        l.append(2+(x-1)^i)
    print i
    print sorted(l)


'''
l = [1, 8, 27, 64, 125, 216, 343]
o = [[] for _ in range(len(l))]

for x in l:
    o[x % 7].append(x)

print "Open:"
print o

c = [None for _ in range(len(l))]

for x in l:
    for i in range((x % 7), len(c)) + range(0, x % 7):
        if c[i] is None:
            c[i] = x
            break

print "Closed:"
print c
'''
