from zad8testy import runtests

from math import ceil, sqrt
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
            if G[q][u] and not V[u]:
                Q.put(u)

    return all(V)


def highway(A):
    G = [[False for _ in A] for _ in A]

    Top = PriorityQueue()
    Bottom = PriorityQueue()
    # E = []

    for i in range(len(A)):
        for j in range(i+1, len(A)):
            t = d(A[i], A[j])
            Top.put((t, (i, j)))
            Bottom.put((t, (i, j)))
            # E.append((t, (i, j)))

    # E.sort(key=lambda x: x[0])

    low = Bottom.get()
    high = Top.get()
    i, j = high[1]
    G[i][j] = G[j][i] = True

    m = None

    while True:
        while is_connected(G):
            diff = high[0] - low[0]

            if m == None or diff < m:
                m = diff

            i, j = low[1]
            G[i][j] = G[j][i] = None
            low = Bottom.get()
        else:
            if Top.empty():
                break
            high = Top.get()

            i, j = high[1]
            G[i][j] = G[j][i] = True

    return m


runtests(highway, all_tests=True)

# print(highway([(100, 100), (100, 200), (200, 100), (200, 200), (150, 151)]))
