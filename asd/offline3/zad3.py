# Mateusz Zając
# Zadanie 3
#

from zad3testy import runtests


def quick(T, p, r):
    if p < r:
        q = partition(T, p, r)
        quick(T, p, q - 1)
        quick(T, q + 1, r)


def partition(T, p, r):
    x = T[r]
    i = p - 1
    for j in range(p, r):
        if T[j] <= x:
            i += 1
            T[i], T[j] = T[j], T[i]
    T[i + 1], T[r] = T[r], T[i + 1]
    return i + 1


def SortTab(T, P):

    K = []

    for p in P:
        curr, limit, step = p[0], p[1], p[2]
        while curr <= limit:
            K.append(curr)
            curr += step

    print(len(K), len(T))

    quick(T, 0, len(T) - 1)
    return T


runtests(SortTab)
