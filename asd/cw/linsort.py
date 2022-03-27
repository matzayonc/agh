from random import randint

base = 10


def count_sort(A, B):
    for i in A:
        C[i % base] += 1

    for i in range(1, len(C)):
        C[i] += C[i-1]

    for i in range(len(A) - 1, -1, -1):
        k = A[i] % base
        C[k] -= 1
        B[C[k]] = A[i]


def radix_sort(A):
    B = [None for _ in A]
    C = [0 for _ in range(base)]

    for i in A:
        C[i % base] += 1

    for i in range(1, len(C)):
        C[i] += C[i-1]

    for i in range(len(A) - 1, -1, -1):
        k = A[i] % base
        C[k] -= 1

        B[C[k]] = A[i]

    C = [0 for _ in C]

    for i in B:
        C[i // base] += 1

    for i in range(1, len(C)):
        C[i] += C[i-1]

    for i in range(len(A) - 1, -1, -1):
        k = B[i] // base
        C[k] -= 1
        A[C[k]] = B[i]


def bucket_sort(T, n):
    m = min(T)
    diff = (max(T) - m) / (n - 1)

    C = [0 for _ in range(n)]
    B = [None for _ in range(n)]

    for i in T:
        d = i - m
        k = (i-m) // n

        C[k] += 1

    for i in range(1, len(C)):
        C[i] += C[i-1]

    print(C)

    for i in range(len(T) - 1, -1, -1):
        k = (i-m) // n
        C[k] -= 1
        B[C[k]] = T[i]

    return B

    # print(radix_sort([1, 3, 4]))
    # T = [randint(0, 99) for _ in range(1000000000)]
    # A = radix_sort(T)
    # print(T)
T = [1, 2, 4]
C = bucket_sort(T, 4)
print(C)
