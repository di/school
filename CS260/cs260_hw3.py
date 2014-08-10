#!/usr/bin/python

class Counter:

    def __init__(self):
        self.first = 0
        self.end = 0
        self.nxt = 0

    def f(self, l):
        p = self.FIRST(l)
        while p != self.END(l):
            q = p
            while q != self.END(l):
                q = self.NEXT(q, l)
                r = self.FIRST(l)
                while r != q:
                    r = self.NEXT(r, l)
            p = self.NEXT(p, l)

    def FIRST(self, l):
        self.first += 1
        return 0

    def END(self, l):
        self.end += 1
        return len(l)

    def NEXT(self, i, l):
        self.nxt += 1
        return i+1


c = Counter()

l = ['a', 'b', 'c', 'd', 'e', 'f', 'g']
c.f(l)

print [c.first, c.end, c.nxt]
n = len(l)
print n
print [1+(n*(n+1))/2, 1 + 2*n + (n*(n+1))/2, n + (n * (n+1))/2 + (n * (n+1) * (2*n+1))/6]
