class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

    def from_array(T):
        r = Node(None)
        c = r
        for i in T:
            c.next = Node(i)
            c = c.next
        return r

    def to_array(self):
        T = []
        c = self.next
        while c != None:
            T.append(c.data)
            c = c.next

        return T

    def split(self):
        if self.next.next == None:
            return self, None

        f = self.next
        s = self.next
        while f.next != None:
            if f.next.next == None:
                break
            f = f.next.next
            s = s.next

        middle = Node(None)
        middle.next = s.next
        s.next = None

        return self, middle

    def merge(self, other):
        if self == None:
            return other
        if other == None:
            return self

        l = self.next
        r = other.next

        result = Node(None)
        t = result
        while l != None and r != None:
            print(l.data, r.data)
            if l.data > r.data:
                t.next = l
                l = l.next
            else:
                t.next = r
                r = r.next
            t = t.next

        if l == None:
            t.next = r
        else:
            t.next = l

        return result

    def sort(self):
        a, b = self.split()
        if a == None:
            return b
        if b == None:
            return a
        return a.sort().merge(b.sort())


T = [8, 4, 6, 3, 1, 2, 5, 7]
T = Node.from_array(T)
print(T.sort().to_array())
