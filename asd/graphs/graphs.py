#!/usr/bin/python3
from collections import deque


class Visited:
    def __init__(self, v: bool):
        self.v = v


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
    cycle = [0]
    Q = deque(cycle)

    while Q:
        q = Q.pop()

        v = G[q].pop(0)

        found = False
        for index, i in enumerate(G[v]):
            if i == q:
                G[v].pop(index)
                found = True

        if not found:
            print('exception')

        if G[v]:
            Q.append(v)
            cycle.append(v)

    return cycle


G = [[1, 3], [2, 0], [3, 1], [0, 2]]
print(eulerian_cycle(G))
