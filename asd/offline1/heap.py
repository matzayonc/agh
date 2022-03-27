class Heap:
    def __init__(self, t):
        self.t = t
        # self.t = t.copy()
        self.l = len(t)

    def heapify(self, i, limit):
        bigger = self.bigger_child(i, limit)

        if bigger != None and self.t[i] < self.t[bigger]:
            self.t[i], self.t[bigger] = self.t[bigger], self.t[i]
            self.heapify(bigger, limit)

    def bigger_child(self, i, limit):
        l = 2 * i + 1
        r = 2 * i + 2

        if r < limit:
            return r if self.t[r] > self.t[l] else l
        elif l < limit:
            return l
        else:
            return None

    def build(self):
        for i in range(self.l//2 - 1, -1, -1):
            self.heapify(i, self.l)

    def swap(self, f):
        o = t[0]
        self.t[0] = f
        return o


def heap_sort(t):
    h = Heap(t)
    h.build()

    for i in range(len(h.t)-1, 0, -1):
        t[i] = h.swap(t[i])
        h.heapify(0, i)


t = [9, 6, 1, 7, 4, 5, 2, 3]
heap_sort(t)
print(t)
