# Mateusz Zając 411113 - Zadanie Offline  4

# funkcja select wywołana dla danego i oznacza że budynek o tym indeksie jest wybierany
# jako następny wybierany jest ciąg budynków mieszczący największą liczbe studentów na prawo od niego

# Złozoność obliczeniowa to O(n log n) (ze wzgledu na sortowanie), a pamięciowa to O(n)

from zad4testy import runtests

M = []


def collides(T, i, j):
    return T[i][2] >= T[j][1] and T[i][1] <= T[j][2]


def cache(func):
    def wrapper(*args):

        if M[args[2]][args[1]] is None:
            M[args[2]][args[1]] = func(*args)

        return M[args[2]][args[1]]

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
    M = [[None for _ in range(p+1)] for _ in range(len(T))]

    for i in range(len(T)):
        T[i] = ((T[i][2] - T[i][1]) * T[i][0], *T[i][1: 4], i)

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
