# Zadanie offline 5

# Algorytm znajduje największą plame która znajduje się przed polem na ktorym braklo paliwa
# do znajdywania maksimum używany jest kopiec

# Złożonośc to O(n log n), ponieważ jest n elementów, z którego dodanie każdego do kolejku zajmuje log n czasu

from zad5testy import runtests


class Heap:
    def __init__(self, T):
        self.T = T
        self.K = []

    def insert(self, v):
        self.K.append(v)
        self.heapify_up(len(self.K)-1)

    def heapify_up(self, i):
        p = int(((i-1)/2))

        if self.K[p] > 0:
            if self.T[self.K[i]] > self.T[self.K[p]]:
                self.K[i], self.K[p] = self.K[p], self.K[i]
                self.heapify_up(p)

    def heapify_down(self, n, i):
        l = 2 * i + 1
        r = 2 * i + 2
        m = i

        if l < n and self.T[self.K[m]] < self.T[self.K[l]]:
            m = l
        if r < n and self.T[self.K[m]] < self.T[self.K[r]]:
            m = r

        if m != i:
            self.K[m], self.K[i] = self.K[i], self.K[m]
            self.heapify_down(n, m)

    def pop(self):
        self.K[0] = self.K[-1]
        self.K.pop()
        self.heapify_down(len(self.K), 0)

    def top(self):
        return self.K[0]


def plan(T):
    oasis = []
    heap = Heap(T)

    i = 0
    fuel = 0

    for i in range(len(T)-1):

        if T[i] > 0:
            heap.insert(i)

        if fuel == 0:
            fuel += T[heap.top()]
            oasis.append(heap.top())
            heap.pop()

        fuel -= 1

    oasis.sort()
    return oasis


runtests(plan, all_tests=True)
