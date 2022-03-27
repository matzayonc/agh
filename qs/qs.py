def quick_sort(T, p, r):

    if p < r:
        q = partition(T, p, r)
        quick_sort(T, p, q-1)
        quick_sort(T, q+1, r)


def partition(T, p, r):
    x = T[r]
    i = p - 1

    for j in range(p, r):
        if T[j] <= x:
            i += 1
            T[j] , T[i] = T[i], T[j]

    T[r], T[i+1] = T[i+1], T[r]
    return i+1




t = [1, 3, 2, 5, 4,3 ,2,35,235,235,2,5,2,53,3,3,5,3,3]
quick_sort(t, 0, len(t)-1)
print(t)