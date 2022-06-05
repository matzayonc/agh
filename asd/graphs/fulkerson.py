from collections import deque


FLOW_EXAMPLE = [
    [(1, 4), (3, 3)],
    [(2, 2), (3, 2)],
    [(5, 4)],
    [(2, 2), (4, 2)],
    [(5, 5)],
    [],
]


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


def find_max_flow(G):
    t = len(G) - 1
    s = 0

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
                    Q = deque()

        if P[t] == None:
            return g

        v = t
        f = 10 ** 10
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


print(find_max_flow(FLOW_EXAMPLE))


FAILING_TEST = [
    [(1, 7), (3, 3)],
    [(3, 4), (4, 6)],
    [(0, 9), (3, 7), (5, 9)],
    [(4, 9), (6, 2)],
    [],
    [(3, 3), (6, 4)],
    [(4, 8)]
]
