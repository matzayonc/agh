#!/usr/bin/python3
from ast import While
from collections import deque
import queue

IN_ORDER_EXAMPLE = [
    [1],  # A
    [3, 2],  # B
    [4],  # C
    [],  # D
    [7],  # E
    [2, 6],  # F
    [4],  # G
    [],  # H
]

EULER_EXAMPLE = [
    [1, 2],
    [0, 5, 2, 3],
    [0, 1, 3, 5],
    [1, 2, 4, 5],
    [3, 5],
    [3, 4, 2, 1]
]

CONNECTED_SUBGRAPH_EXAMPLE = [
    [4, 1],
    [2],
    [0, 10],
    [4, 6],
    [5],
    [3],
    [5],
    [8],
    [3, 9],
    [5, 10],
    [7],
]


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


# print(eulerian_cycle(EULER_EXAMPLE))


def vertices_with_time(G):
    Q = deque([])
    V = [None for _ in G]

    t = 0  # timer for timing visits

    for i in range(len(G)):
        if V[i] == None:
            Q.append(i)

            while Q:
                q = Q.pop()
                if V[q] != None:
                    continue
                V[q] = t
                t += 1

                for v in G[q]:
                    Q.append(v)

    return V


def vertices_in_order(G):
    Q = deque([])
    V = [False for _ in G]
    T = []

    for i in range(len(G)):
        if V[i] == False:
            Q.append(i)

            while Q:
                q = Q.pop()
                if V[q] != False:
                    continue
                V[q] = True
                T.append(q)

                for v in G[q]:
                    Q.append(v)

    return T


def reverse_graph(G):
    T = [[] for _ in G]

    for v in range(len(G)):
        for e in G[v]:
            T[e].append(v)

    return T

# print(vertices_in_order(IN_ORDER_EXAMPLE))


def find_connected_subgraphs(G):
    O = vertices_in_order(G)
    G = reverse_graph(G)

    V = [False for _ in G]

    R = []

    Q = deque()

    for i in O:
        if not V[i]:
            R.append([])
            Q.append(i)

            while Q:
                q = Q.pop()
                V[q] = True
                R[-1].append(q)

                for v in G[q]:
                    if not V[v]:
                        Q.append(v)

    return R


# print(find_connected_subgraphs(CONNECTED_SUBGRAPH_EXAMPLE))


BRIDGES_EXAMPLE = [
    [1, 6],
    [0, 2],
    [1, 3, 5, 6],
    [2, 4],
    [3, 5],
    [2, 4],
    [0, 2],
    [6]
]
