from zad1testy import Node, runtests


def heapify(t, i, limit):
    bigger = bigger_child(t, i, limit)

    if bigger != None and t[i] < t[bigger]:
        t[i], t[bigger] = t[bigger], t[i]
        heapify(t, bigger, limit)


def bigger_child(t, i, limit):
    l = 2 * i + 1
    r = 2 * i + 2

    if r < limit:
        return r if t[r] > t[l] else l
    elif l < limit:
        return l
    else:
        return None


def SortH(t, k):

    # def heap_sort(t):
    #     for i in range(len(t)//2 - 1, -1, -1):
    #         heapify(t, i, len(t))

    #     for i in range(len(t)-1, 0, -1):
    #         t[i], t[0] = t[0], t[i]
    #         heapify(t, 0, i)

    # def sort(t, k):
    #     for i in range(k//2 - 1, -1, -1):
    #         heapify(t, i, k)

    for i in range(k//2 - 1, -1, -1):
        heapify(t, i, k)

    for i in range(len(t)-1, 0, -1):
        t[i], t[0] = t[0], t[i]
        heapify(t, 0, i)


runtests(SortH)
