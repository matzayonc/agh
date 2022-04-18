def quick_sort(T):

    s = [(0, len(T) - 1)]

    while len(s) > 0:
        p, r = s.pop()
        q = partition(T, p, r)

        if p < q - 1:
            s.append((p, q - 1))
        if q + 1 < r:
            s.append((q + 1, r))


def partition(T, p, r):
    i = p - 1

    for j in range(p, r):
        if T[j] < T[r]:
            i += 1
            T[j], T[i] = T[i], T[j]

    T[i + 1], T[r] = T[r], T[i + 1]
    return i + 1
    



t = [1, 3, 2, 5, 4,3 ,2,35,235,235,2,5,2,53,3,3,5,3,3]
quick_sort(t)
print(t)