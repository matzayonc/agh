# Algorytm zaczyna od sortowania `quick sort` tablicy po dolnej granicy przedziału
# Następnie idzie po kolejnych dolnych przedziałach zawsze zaczynając od pierwszego o danej wartości
# Dzięki temu że przedziały są posortowane, a dolny przedział jest mniejszy od górnego
# wystarczy sprawdzać czy górna granica mieści się wewnątrz przedziału aby stwierdzić zawieranie się przedziałów.
# A jeśli górny przekroczy to można przerwać sprawdzanie, ponieważ każdy kolejny też przekroczy

# Złożoność pesymistyczna dla sortowania to n ^ 2, podobnie jak dla samego algorytmu,
# Złożoność średnią ciężko określić ze względu na dane, dla podanych O(n log n))
# Złożoność optymistyczna O(n log n) ze względu na sortowanie i O(n) ze względu na algorytm
# Złożoność pamięciowa to O(n)
from zad2testy import runtests


def quick_sort_by_first(T):

    s = [(0, len(T) - 1)]

    while len(s) > 0:
        p, r = s.pop()

        i = p - 1
        for j in range(p, r):
            if T[j][0] < T[r][0]:
                i += 1
                T[j], T[i] = T[i], T[j]

        T[i + 1], T[r] = T[r], T[i + 1]
        q = i + 1

        if p < i:
            s.append((p, i))
        if i + 2 < r:
            s.append((i + 2, r))


def depth(T):
    quick_sort_by_first(T)
    l = 0

    for t in T:
        t.append(False)

    for k in range(len(T)):
        if T[k][2] == True:
            continue

        lowest_same = k
        i = k
        while lowest_same > 0 and T[lowest_same - 1][0] == T[i][0]:
            lowest_same -= 1

        c = -1
        for j in range(lowest_same, len(T)):
            if T[j][1] <= T[i][1]:
                c += 1
                T[j][2] = True

            elif T[j][0] > T[i][1]:
                break

        l = max(c, l)

    return l


runtests(depth)
