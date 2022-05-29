from zad8testy import runtests

from math import ceil, sqrt
from queue import PriorityQueue, Queue


def d(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return ceil(sqrt(x*x + y*y))


def is_connected(G):
    V = [False for _ in G]
    Q = []
    Q.append(0)

    while len(Q) > 0:
        q = Q.pop()
        V[q] = True
        for u in range(len(G[q])):
            if G[q][u] and not V[u]:
                Q.append(u)

    return all(V)


def highway(A):
    G = [[False for _ in A] for _ in A]
    E = []

    for i in range(len(A)):
        for j in range(i+1, len(A)):
            t = d(A[i], A[j])
            E.append((t, (i, j)))

    E.sort(key=lambda x: x[0])

    low = 0
    high = -1
    m = None

    while True:
        while is_connected(G):
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
            G[i][j] = G[j][i] = True

    return m


runtests(highway, all_tests=True)

# print(highway([(100, 100), (100, 200), (200, 100), (200, 200), (150, 151)]))
