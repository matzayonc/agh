from zad5testy import runtests
# W roku 2050 spokojny Maksymilian odbywa podróż przez pustynię z miasta A do miasta B. Dro-
# ga pomiędzy miastami jest linią prostą na której w pewnych miejscach znajdują się plamy ropy.
# Maksymilian porusza się 24 kołową cysterną, która spala 1 litr ropy na 1 kilometr trasy. Cysterna
# wyposażona jest w pompę pozwalającą zbierać ropę z plam. Aby dojechać z miasta A do miasta
# B Maksymilian będzie musiał zebrać ropę z niektórych plam (by nie zabrakło paliwa), co każdo-
# razowo wymaga zatrzymania cysterny. Niestety, droga jest niebezpieczna. Maksymilian musi więc
# tak zaplanować trasę, by zatrzymać się jak najmniej razy. Na szczęście cysterna Maksymiliana jest
# ogromna - po zatrzymaniu zawsze może zebrać całą ropę z plamy (w cysternie zmieściłaby się cała
# ropa na trasie).
# Zaproponuj i zaimplementuj algorytm wskazujący, w których miejscach trasy Maksymilian powi-
# nien się zatrzymać i zebrać ropę. Algorytm powinien być możliwe jak najszybszy i zużywać jak
# najmniej pamięci. Uzasadnij jego poprawność i oszacuj złożoność obliczeniową.


(index, paliwo)
[10, 01, 10, 10, 110100101100110000000000000000000000000000000000000000000000000]


def plan(T):
    M = {}
    stack = [(0, 0, [])]
    print(len(T))

    while len(stack):
        i, b, p = stack.pop(0)

        if (i, b) in M:
            continue
        else:
            M[(i, b)] = p

        e = b + T[i]

        if i + e >= len(T)-1:
            return [*p, i]

        for k in range(1, e+1):
            if e - k < 0 or i >= len(T):
                break

            if T[i+k] == 0:
                continue

            stack.append((i+k, e-k, [*p, i]))


runtests(plan, all_tests=True)


T = [3, 0, 2, 1, 0, 2, 5, 0]
print(plan(T))
