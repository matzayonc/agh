# Zadanie Offline 8 - Mateusz Zajac 411113
# Graf powstaje poprzez potraktowanie każdego miasta jak wierzcholka, a możliwej drogi jako krawędzi
# Algorytm 'pełznie' po posortowanej tablicy krawędzi:
#    * usuwając najkrótszą krawędź jeśli graf jest spójny
#    * dodając najkrótszą większą od pozostałycg w grafie
# oraz monitorując minimalną różnice między najkrótszą a najdłuższą
# Złożonośc pamięciowa to O(n^2), a obliczeniowa to O(E^2 log V) (sprawdzenie spójności dla E krawędzi)


from zad8testy import runtests

from math import ceil, sqrt
from queue import PriorityQueue, Queue
from collections import deque


def d(a, b):
    x = a[0] - b[0]
    y = a[1] - b[1]
    return ceil(sqrt(x*x + y*y))


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


def highway(A):
    G = [deque() for _ in A]
    E = []

    for i in range(len(A)):
        for j in range(i+1, len(A)):
            t = d(A[i], A[j])
            E.append((t, (i, j)))

    E.sort(key=lambda x: x[0])
    F = deque(E)
    E = deque(E)

    low = None
    high = None
    m = None

    while True:
        while is_connected(G):

            low = E.popleft()
            k, (i, j) = low

            diff = high[0] - k
            if m == None or diff < m:
                m = diff

            G[i].popleft()
            G[j].popleft()

        else:
            if not F:
                break

            high = F.popleft()

            _, (i, j) = high
            G[i].append(j)
            G[j].append(i)

    return m


runtests(highway, all_tests=True)
