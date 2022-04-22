from zad4testy import runtests

M = {}


def collides(T, i, j):
    return T[i][2] >= T[j][1] and T[i][1] <= T[j][2]


def cache(func):
    def wrapper(*args):

        k = str(args[1]) + '-' + str(args[2])

        if k not in M:
            M[k] = func(*args)
        return M[k]

    return wrapper


@cache
def select(T, p, i):
    m = (0, [])

    for k in range(i+1, len(T)):
        if collides(T, i, k) or p - T[i][3] < T[k][3]:
            continue
        c = select(T, p - T[i][3], k)

        if c[0] > m[0]:
            m = c

    return (m[0] + T[i][0], [i, *m[1]])


def select_buildings(T, p):
    global M
    M = {}
    for i in range(len(T)):
        T[i] = ((T[i][2] - T[i][1]) * T[i][0], *T[i][1:4], i)

    T.sort(key=lambda x: x[1])

    m = (0, [])
    for k in range(0, len(T)):
        if p < T[k][3]:
            continue

        c = select(T, p, k)

        if c[0] > m[0]:
            m = c

    m = [T[m[1][i]][4] for i in range(len(m[1]))]
    m.sort()
    return m


runtests(select_buildings)
