from zad4testy import runtests


def value(T, S):
    s = 0
    for i in S:
        s += (T[i][2] - T[i][1]) * T[i][0]

    return s


def collides(T, i, j):
    return T[i][2] > T[j][1] and T[i][1] < T[j][2]


def select(T, p, i):

    m = []

    if i >= len(T) or p < 0:
        return m

    for k in range(i+1, len(T)):
        if collides(T, i, k):
            continue
        c = select(T, p - T[i][3], k)

        if value(T, c) > value(T, m):
            m = c

    return [i, *m]


def select_buildings(T, p):

    for i in range(len(T)):
        T[i] = (*T[i], i)

    T.sort(key=lambda x: x[1])

    m = []
    for k in range(0, len(T)):
        c = select(T, p, k)

        if value(T, c) > value(T, m):
            m = c

    for i in range(len(m)):
        m[i] = T[m[i]][4]

    m.sort()

    return m

    # tu prosze wpisac wlasna implementacje
    # return select(T, p, 0)


runtests(select_buildings)


T = [
    (1, 1, 2, 1),
    (1, 1, 3, 1),
    (1, 2, 3, 1),
    (1, 3, 4, 1)
]
print(select_buildings([(3, 7, 9, 2), (2, 1, 5, 3),

                        (2, 8, 11, 1)], 5))
