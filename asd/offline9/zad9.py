from collections import deque
from zad9testy import runtests


BIG = 10 ** 10


def find_path(G, s=0, t=None):
    if t == None:
        t = len(G) - 1

    Q = deque([s])
    P = [None for _ in G]

    while Q:
        q = Q.pop()

        for v in G[q]:
            if P[v] == None:
                P[v] = q
                Q.append(v)

            if v == t:
                return P

    return None


def index_of_first_in_tuple(T, v):
    for i, (u, _) in enumerate(T):
        if u == v:
            return i
    return None


def find_max_flow(G, s=0, t=None):
    if t == None:
        t = len(G) - 1

    g = 0
    # P = find_path(G)

    while True:
        Q = deque([s])
        P = [None for _ in G]

        while Q:
            q = Q.pop()

            for u, _ in G[q]:
                if P[u] == None:
                    P[u] = q
                    Q.append(u)

                if u == t:
                    break

        if P[t] == None:
            return g

        v = t
        f = BIG
        while v != s:
            p = P[v]
            for u, c in G[p]:
                if u == v:
                    f = min(f, c)
                    break

            v = p
        g += f

        v = t
        while v != s:  # p --> v
            p = P[v]

            j = index_of_first_in_tuple(G[p], v)
            u, c = G[p][j]

            if f < c:
                G[p][j] = (u, c - f)
            elif f == c:
                G[p].pop(j)
            else:
                r = f - c
                G[p].pop(j)
                k = index_of_first_in_tuple(G[v], p)
                if k == None:
                    G[v].append((p, r))
                else:
                    G[v][k] += (G[v][k][0],  G[v][k][1] + r)

            v = p


def list_to_graph(G):
    D = [[] for _ in G]
    m = 0
    for f, t, c in G:
        D[f].append((t, c))
        m = max(m, t, f)

    while len(D)-1 > m:
        D.pop()

    return D


def maxflow(D, s):

    m = 0

    G = list_to_graph(D)

    print(G)

    l = len(G)

    for i in range(l):
        for j in range(i+1, l):
            if i == s or j == s:
                continue

            G[i].append((l, BIG))
            G[j].append((l, BIG))
            G.append([])

            m = max(m, find_max_flow(G, s, l))
            G = list_to_graph(D)

    return m


runtests(maxflow, all_tests=True)
