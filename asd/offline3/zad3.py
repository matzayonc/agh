# Mateusz Zając
# Zadanie 3
# W tym zadaniu oczywistym wyborem wydaje się użycie sortowania przez kubełkowanie.
# Złożonośc tego alorytmu wynosi O(n) dla optymalnego przypadku, O(n^2) dla pesymistycznego, złożonośc pamięciowa jest liniowa

# Algorytm najpierw kubełkuje elementy, a następnie sortuje je algorytmem quick sort.
# Sortowanie kubełkowe działa tutaj dobrze ze względu na równomierny rozkład elementów oraz znaczącą ich ilość.

from zad3testy import runtests


def quick_sort(T, p, r):
    if p < r:
        q = partition(T, p, r)
        quick_sort(T, p, q - 1)
        quick_sort(T, q + 1, r)


def partition(T, p, r):
    x = T[r]
    i = p - 1
    for j in range(p, r):
        if T[j] <= x:
            i += 1
            T[i], T[j] = T[j], T[i]
    T[i + 1], T[r] = T[r], T[i + 1]
    return i + 1


def bucket_sort(T, n, m):

    print(n, m)

    def get_index(x):
        return int((x - n) / (m - n) * (len(T) - 1))

    B = [None for _ in range(len(T))]
    # indeks pierwszego z elementów
    C = [0 for _ in range(len(T))]
    # używane wyłącznie do sprawdzania czy dany element jest ostatnim z kubełka
    F = [0 for _ in range(len(T))]
    # przetrzymuje ilość elementów w kubełku
    D = [0 for _ in range(len(T))]

    for t in T:
        i = get_index(t)
        C[i] += 1

    D[0] = C[0]
    F[0] = C[0]

    for i in range(1, len(C)):
        D[i], F[i] = C[i], C[i]
        C[i] += C[i - 1]

    for t in T:
        i = get_index(t)
        C[i] -= 1
        D[i] -= 1
        B[C[i]] = t

        if D[i] == 0:
            quick_sort(B, C[i], C[i] + F[i] - 1)

    return B


def SortTab(T, P):
    n, m = P[0][0], P[0][1]

    for p in P:
        if p[0] < n:
            n = p[0]
        if p[1] > m:
            m = p[1]

    return bucket_sort(T, n, m)


runtests(SortTab)
