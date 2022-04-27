from operator import le
from zad5testy import runtests


RANGE = 380


def heapify(arr, n, i, T):
    largest = i
    l = 2 * i + 1
    r = 2 * i + 2

    if l < n and T[arr[largest]] > T[arr[l]]:
        largest = l
    if r < n and T[arr[largest]] > T[arr[r]]:
        largest = r

    if largest != i:
        arr[i], arr[largest] = arr[largest], arr[i]  # swap
        heapify(arr, n, largest, T)


def find_top(T, K, a, b, allow_add=True):

    for i in range(a, b+1):
        if len(K) < RANGE and allow_add:
            K.append(i)

            if len(K) == RANGE:
                for i in range(len(K)//2 - 1, -1, -1):
                    heapify(K, len(K), i, T)

            continue

        if T[i] > T[K[0]]:
            K[0] = i
            heapify(K, len(K), 0, T)

    return


def max_from_minheap(K, T):
    m = 0
    for i in range(1, len(K)):
        if T[K[i]] > T[K[m]]:
            m = i

    if m == len(K)-1:
        return K.pop()

    r = K[m]
    K[m] = K.pop()
    heapify(K, len(K), m, T)
    return r


def drain_biggest_below(T, K, below, prev=None):

    if len(K) > 0 and len(K) < RANGE and prev != None:
        find_top(T, K, prev+1, below, False)
    else:
        find_top(T, K, 0, below)

    m = max_from_minheap(K, T)

    r = T[m]
    T[m] = 0
    return (r, m)


def plan(T):
    fire_stations = []
    farthest = 0
    prev = 0
    K = []

    while True:
        r, m = drain_biggest_below(T, K, farthest, prev)
        prev = farthest
        farthest += r

        fire_stations.append(m)

        if farthest >= len(T)-1:
            return sorted(fire_stations)


runtests(plan, all_tests=True)
