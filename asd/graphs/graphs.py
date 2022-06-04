#!/usr/bin/python3
from collections import deque


def is_connected(G):
    for v in G:
        if not len(v):
            return False

    V = [False for _ in G]
    Q = deque([0])

    while Q:
        for v in G[Q.pop()]:
            if not V[v]:
                V[v] = True
                Q.append(v)

    return all(V)


def eulerian_cycle(G):
    cycle = []
    Q = deque([0])

    while Q:
        q = Q[-1]
        if not G[q]:
            cycle.append(Q.pop())
            continue

        v = G[q].pop()
        G[v].remove(q)

        Q.append(v)

    return cycle


EULER_EXAMPLE = [
    [1, 2],
    [0, 5, 2, 3],
    [0, 1, 3, 5],
    [1, 2, 4, 5],
    [3, 5],
    [3, 4, 2, 1]
]
print(eulerian_cycle(EULER_EXAMPLE))
