from kol1atesty import runtests
# Mateusz Zając 411113 Kolokwium I
# 1) Algorytm zaczynam od "odwrócenia" wszystkich wyrazów, tak aby 2 wyrazy były równowarzne wyłącznie wtedy, gdy są równe
#       złożoność tego kroku to O(n), gdyż wymaga iteracji po wszystkich elementach tablicy

# 2) Kolejnym krokiem jest sortowanie tablicy, mające na celu łatwiejsze zliczanie w kroku trzecim
# Używany algorytm sortowania to quick sort, ze względu na długie wyrazy

# 3) Ostatnik krokiem jest iteracja przez talbice i zliczenia ilość powtórzeń każdego elementu(po etapie pierwszym wszystkie równoważne elementy będą identycznie)

# Złożoność całego algorytmu to ( O(n log n) ) pod względem obliczeń oraz O(1) pod względem pamięci
# Złożoneść pesymistyczna to O(n^2)


def rotate_if_needed(s):
    i = 0
    while i < len(s) and s[i] == s[len(s)-1-i]:
        i += 1

    if i == len(s):
        return s

    if s[i] > s[len(s)-1-i]:
        return s[::-1]
    else:
        return s


def find_most_common(T):
    last = "A"  # Big letter so will never match
    m = c = 0

    for i in range(len(T)):
        if T[i] == last:
            c += 1
        else:
            if c > m:
                m = c
            c = 1
            last = T[i]

    return m


def quick(T, p, r):
    if p < r:
        k = partition(T, p, r)
        quick(T, p, k-1)
        quick(T, k+1, r)


def partition(T, p, r):
    i = p-1
    for j in range(p, r):
        if T[j] <= T[r]:
            i += 1
            T[i], T[j] = T[j], T[i]

    i += 1
    T[i], T[r] = T[r], T[i]
    return i


def counting_on_position(T, p):

    def to_index(c):
        return ord(c) - ord('a')

    base = ord('z') - ord('a') + 2
    last = to_index('z') + 1

    M = [0 for _ in range(base + 2)]

    for t in T:
        if len(t) <= p:
            M[last] += 1
        else:
            M[to_index(t[p])] += 1

    for i in range(1, len(M)):
        M[i] += M[i-1]

    A = [None for _ in range(len(T))]

    for i in range(len(T)-1, -1, -1):
        if len(T[i]) <= p:
            M[last] -= 1
            A[M[last]] = T[i]
        else:
            M[to_index(T[i][p])] -= 1
            A[M[to_index(T[i][p])]] = T[i]

    return A


def radix_sort(T):
    m = len(T[0])
    for t in T:
        if len(t) > m:
            m = len(t)

    D = T
    for i in range(m, -1, -1):
        D = counting_on_position(D, i)

    return D


def g(T):
    for i in range(len(T)):
        T[i] = rotate_if_needed(T[i])

    # T.sort()
    # T = radix_sort(T)
    quick(T, 0, len(T)-1)

    m = find_most_common(T)

    return m


# Zamien all_tests=False na all_tests=True zeby uruchomic wszystkie testy
runtests(g, all_tests=True)
