from zad8testy import runtests

import heapq
from math import sqrt
from heapq import heappush, heappop
from queue import PriorityQueue


def eval(G):
    m = None
    n = None

    for j in G:
        for i in j:
            if i != None:
                if m == None:
                    m = i
                else:
                    m = min(m, i)
                if n == None:
                    n = i
                else:
                    n = max(n, i)

    return n - m


def d(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return sqrt(x*x + y*y)


def is_valid(A):
    Q = [0]
    V = [False for _ in A]
    heappush(Q, 0)

    while len(Q) > 0:
        q = heappop(Q)
        V[q] = True

        for u in range(len(A[q])):
            if A[q][u] != None:
                if not V[u]:
                    heappush(Q, u)

    return all(V)


def try_remove(G, Q):
    k, (i, j) = Q.get()
    G[i][j] = G[j][i] = None
    if not is_valid(G):
        G[i][j] = G[j][i] = abs(-k)
        return False
    return True


def highway(A):
    G = [[0 for _ in A] for _ in A]
    Q = PriorityQueue()
    U = PriorityQueue()

    for i in range(len(A)):
        for j in range(i, len(A)):
            k = d(A[i], A[j])
            G[i][j] = G[j][i] = k
            Q.put((k, (i, j)))
            U.put((-k, (i, j)))

    G2 = [[i for i in j] for j in G]

    while not U.empty():
        if not try_remove(G, U):
            break

    while not Q.empty():
        if not try_remove(G, Q):
            break

    return eval(G)


runtests(highway, all_tests=True)
