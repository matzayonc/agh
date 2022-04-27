from zad5testy import runtests


RANGE = 139


def find_top(T, K, a, b, allow_add=True):
    for i in range(a, b+1):
        if len(K) < RANGE and allow_add:
            K.append(i)
            K.sort(key=lambda x: T[x], reverse=True)
            continue

        if T[i] > T[K[-1]]:
            K.append(i)
            K.sort(key=lambda x: T[x], reverse=True)
            K.pop()

    return


def drain_biggest_below(T, K, below, prev=None):

    if len(K) > 0 and len(K) < RANGE and prev != None:
        find_top(T, K, prev+1, below, False)
    else:
        find_top(T, K, 0, below)

    K.sort(key=lambda x: T[x], reverse=True)
    m = K.pop(0)

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

# print(plan([3, 0, 2, 1, 0, 2, 5, 0]))

# print(drain_biggest_below([3, 0, 2, 1, 0, 2, 5, 0], 7))
