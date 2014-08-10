from __future__ import generators
from __future__ import print_function

class priorityDictionary(dict):
    def __init__(self):
        '''Initialize priorityDictionary by creating binary heap of pairs (value,key).
Note that changing or removing a dict entry will not remove the old pair from the heap
until it is found by smallest() or until the heap is rebuilt.'''
        self.__heap = []
        dict.__init__(self)

    def smallest(self):
        '''Find smallest item after removing deleted items from front of heap.'''
        if len(self) == 0:
            raise IndexError, "smallest of empty priorityDictionary"
        heap = self.__heap
        while heap[0][1] not in self or self[heap[0][1]] != heap[0][0]:
            lastItem = heap.pop()
            insertionPoint = 0
            while 1:
                smallChild = 2*insertionPoint+1
                if smallChild+1 < len(heap) and heap[smallChild] > heap[smallChild+1] :
                    smallChild += 1
                if smallChild >= len(heap) or lastItem <= heap[smallChild]:
                    heap[insertionPoint] = lastItem
                    break
                heap[insertionPoint] = heap[smallChild]
                insertionPoint = smallChild
        return heap[0][1]
    
    def __iter__(self):
        '''Create destructive sorted iterator of priorityDictionary.'''
        def iterfn():
            while len(self) > 0:
                x = self.smallest()
                yield x
                del self[x]
        return iterfn()
    
    def __setitem__(self,key,val):
        '''Change value stored in dictionary and add corresponding pair to heap.
Rebuilds the heap if the number of deleted items gets large, to avoid memory leakage.'''
        dict.__setitem__(self,key,val)
        heap = self.__heap
        if len(heap) > 2 * len(self):
            self.__heap = [(v,k) for k,v in self.iteritems()]
            self.__heap.sort()  # builtin sort probably faster than O(n)-time heapify
        else:
            newPair = (val,key)
            insertionPoint = len(heap)
            heap.append(None)
            while insertionPoint > 0 and newPair < heap[(insertionPoint-1)//2]:
                heap[insertionPoint] = heap[(insertionPoint-1)//2]
                insertionPoint = (insertionPoint-1)//2
            heap[insertionPoint] = newPair
    
    def setdefault(self,key,val):
        '''Reimplement setdefault to pass through our customized __setitem__.'''
        if key not in self:
            self[key] = val
        return self[key]

def Dijkstra(G,start,end=None):
    D = {}  # dictionary of final distances
    P = {}  # dictionary of predecessors
    Q = priorityDictionary()   # est.dist. of non-final vert.
    Q[start] = 0

    for v in Q:
        D[v] = Q[v]
        if v == end:
            break
        for w in G[v]:
            vwLength = D[v] + G[v][w]
            if w in D:
                if vwLength < D[w]:
                    raise ValueError, \
  "Dijkstra: found better path to already-final vertex"
            elif w not in Q or vwLength < Q[w]:
                Q[w] = vwLength
                P[w] = v

    return (D,P)

def shortestPath(G,start,end):
    D,P = Dijkstra(G,start,end)
    Path = []
    while 1:
        Path.append(end)
        if end == start:
            break
        try:
            end = P[end]
        except KeyError:
            return None
    Path.reverse()
    return Path

graph = {
    'A': {'B': 3, 'D': 4, 'F': 5},
    'B': {'C': 1, 'F': 1},
    'C': {'D': 2},
    'D': {'B': 3},
    'E': {'D': 3, 'F': 2},
    'F': {'D': 2},
}

def path_cost(graph, path):
    cost = 0
    if path is not None:
        for a, b in zip(path[:-1], path[1:]):
            cost += graph[a][b]
    return cost


for n in sorted(graph.keys())[1:]:
    path = shortestPath(graph, 'A', n)
    cost = path_cost(graph, path)
    print("%s: %s (%d)" % (n, path, cost))

print("")

def adj(g):
    vertices = g.keys()
 
    dist = {}
    for i in vertices:
        dist[i] = {}
        for j in vertices:
            try:
                dist[i][j] = g[i][j]
            except KeyError:
                # the distance from a node to itself is 0
                if i == j:
                    dist[i][j] = 0
                # the distance from a node to an unconnected node is infinity
                else:
                    dist[i][j] = float('inf')
    return dist
 
def fw(g):
    vertices = g.keys()
 
    d = dict(g)  # copy g
    for k in vertices:
        for i in vertices:
            for j in vertices:
                d[i][j] = min(d[i][j], d[i][k] + d[k][j])
    return d

floyd = fw(adj(graph))
print("\t" + "\t".join(floyd.keys()))
for y in sorted(floyd.keys()):
    print(y + "\t" +  "\t".join([str(floyd[y][e]) for e in sorted(floyd[y].keys())]))


shortest = dict()

for i in sorted(graph.keys()):
    shortest[i] = dict()
    for j in sorted(graph.keys()):
        shortest[i][j] = shortestPath(graph, i, j)

print("")
print("\t" + "\t".join(floyd.keys()))
for i in sorted(graph.keys()):
    print(i, end='')
    for j in sorted(graph.keys()):
        path = shortest[i][j]
        if path is None:
            print("\t" + "inf", end='')
        elif len(path) <= 2:
            print("\t" + str(0), end='')
        elif len(path) == 3:
            print("\t" + shortest[i][j][1], end='')
        else:
            print("\t" + shortest[i][j][1] + "|" + shortest[i][j][2], end='')
    print("")
