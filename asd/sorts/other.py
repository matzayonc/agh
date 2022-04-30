def heapify(T, n, i):
    l = i * 2 + 1
    r = i * 2 + 2
    m = i

    if l < n and T[l] > T[m]:
        m = l

    if r < n and T[r] > T[m]:
        m = r

    if m != i:
        T[m], T[i] = T[i], T[m]
        heapify(T, n, m)


def greatest(T, n, k):
    for i in range(n // 2, -1, -1):
        heapify(T, n, i)

    for i in range(n - 1, 0, -1):
        if n-1 - i == k-1:
            return T[0]
        T[0] = T[i]
        heapify(T, i, 0)


T = [8, 4, 6, 3, 1, 2, 5, 7]
k = greatest(T, len(T), 4)
print(k)
