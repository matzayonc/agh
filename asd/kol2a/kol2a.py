# Mateusz Zając 411113

# Funkcja run działa z parametrami oznaczającymi obecne miejsce, cel, oraz flage czy w danym momencie prowadzi marian
# Jeśli marian nie prowadzi koszt jest zerowy
# Dla każdego z 3 kolejnych punktów przesiadkowych wywoławana jest rekurencyjnie ta sama funkcja
# Minimum z wywołań funkcji jest zwracane
# Złożoność po zaimplementowaniu cachowania to O(n log n) wynikająca z sortowania


from kol2atesty import runtests


def count(P, a, b):
    control, switch = 0, 0
    for i in range(a, b+1):
        if P[i][1] == True:
            switch += 1
        else:
            control += 1

    return control, switch


def run(P, b, B, marian=False):
    if b >= len(P) or P[b][0] >= B:
        return 0, []

    i = b
    m = None
    o = []

    while P[i][0] < B:
        i += 1
        if i >= len(P) or P[i][0] >= B:
            break

        control, switch = count(P, b, i)

        if not marian:
            control = 0

        if switch > 3:
            break

        if P[i][1] == True:

            r, t = run(P, i, B, not marian)

            if m == None or m > r + control:
                m = r + control
                P[i][0]
                o = [i, *t]

    if m == None:
        return 0, []

    return m, o


def drivers(P, B):
    P.sort(key=lambda x: x[0])
    r, t = run(P, 0, B)
    return t


# zmien all_tests na True zeby uruchomic wszystkie testy
runtests(drivers, all_tests=False)
