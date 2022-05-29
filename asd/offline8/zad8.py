from xmlrpc.server import list_public_methods
from zad8testy import runtests

import heapq
from math import ceil, sqrt
from heapq import heappush, heappop
from queue import PriorityQueue, Queue


def d(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return ceil(sqrt(x*x + y*y))


def is_connected(G):
    V = [False for _ in G]
    Q = Queue()
    Q.put(0)

    while not Q.empty():
        q = Q.get()
        V[q] = True
        for u in range(len(G[q])):
            if G[q][u] != None and not V[u]:
                Q.put(u)

    return all(V)


def highway(A):
    G = [[None for _ in A] for _ in A]
    E = []

    for i in range(len(A)):
        for j in range(i+1, len(A)):
            t = d(A[i], A[j])
            # G[i][j] = G[j][i] = t
            E.append((t, (i, j)))

    E.sort(key=lambda x: x[0])

    low = 0
    high = 0
    m = None

    while True:

        if is_connected(G):
            diff = E[high][0] - E[low][0]
            if m == None or diff < m:
                m = diff

            k, (i, j) = E[low]
            G[i][j] = G[j][i] = None
            low += 1
        else:
            high += 1
            if high >= len(E):
                break

            k, (i, j) = E[high]
            G[i][j] = G[j][i] = k

    return m


runtests(highway, all_tests=True)

# print(highway([(10, 10), (20, 20), (30, 40)]))
