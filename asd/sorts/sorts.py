def bubble(T):
    for j in range(len(T) - 1, -1, -1):
        for i in range(j):
            if T[i] > T[i+1]:
                T[i], T[i+1] = T[i+1], T[i]


def selection(T):
    for i in range(len(T)):
        m = i
        for j in range(i+1, len(T)):
            if T[j] < T[m]:
                m = j

        T[i], T[m] = T[m], T[i]


def quick(T, p, r):
    if p < r:
        k = partition(T, p, r)
        quick(T, p, k-1)
        quick(T, k+1, r)


def partition(T, p, r):
    i = p-1
    for j in range(len(T)):
        if T[j] < T[r]:
            i += 1
            T[i], T[j] = T[j], T[i]

    i += 1
    T[i], T[r] = T[r], T[i]
    return i


def counting(T):
    base = 10
    M = [0 for _ in range(base)]
    for t in T:
        M[t] += 1

    for i in range(1, len(M)):
        M[i] += M[i-1]

    U = [None for _ in T]
    for i in range(len(T) - 1, -1, -1):
        M[T[i]] -= 1
        U[M[T[i]]] = T[i]

    for i in range(len(T)):
        T[i] = U[i]


def heapify(T, i, n):
    l = 2 * i + 1
    r = 2 * i + 2
    m = i
    if l < n and T[l] > T[m]:
        m = l
    if r < n and T[r] > T[m]:
        m = r

    if m != i:
        T[i], T[m] = T[m], T[i]
        heapify(T, m, n)


def heap(T):

    for i in range(len(T) // 2, -1, -1):
        heapify(T, i, len(T))

    for i in range(len(T)-1, -1, -1):
        T[0], T[i] = T[i], T[0]
        heapify(T, 0, i)


T = [8, 4, 6, 3, 1, 2, 5, 7]
# bubble(T)
# selection(T)
quick(T, 0, len(T)-1)
# counting(T)
# heap(T)
print(T)
