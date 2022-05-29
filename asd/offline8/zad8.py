from zad8testy import runtests

from math import ceil, sqrt
from queue import PriorityQueue, Queue
from collections import deque


def d(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return ceil(sqrt(x*x + y*y))


def is_connected(G):
    V = [False for _ in G]
    Q = deque([0])

    while Q:
        q = Q.pop()
        if V[q]:
            continue
        V[q] = True
        for u in G[q]:
            if not V[u]:
                Q.append(u)

    return all(V)


def highway(A):
    G = [deque() for _ in A]
    E = []

    for i in range(len(A)):
        for j in range(i+1, len(A)):
            t = d(A[i], A[j])
            E.append((t, (i, j)))

    E.sort(key=lambda x: x[0])
    E = deque(E)

    low = 0
    high = -1
    m = None

    while True:
        while is_connected(G):
            diff = E[high][0] - E[low][0]
            if m == None or diff < m:
                m = diff

            k, (i, j) = E[low]
            G[i].popleft()
            G[j].popleft()

            E.popleft()
            high -= 1

        else:
            high += 1
            if high >= len(E):
                break

            k, (i, j) = E[high]
            # G[i][j] = G[j][i] = True
            G[i].append(j)
            G[j].append(i)

    return m


runtests(highway, all_tests=True)
