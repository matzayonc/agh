from zad7testy import runtests


def go(G, V, i, l, f):
    if V[i]:
        return None

    s = 0
    if f in G[i][s]:
        s = 1

    if l == len(G):
        if 0 in G[i][s]:
            return [i]
        else:
            return None

    for v in G[i][s]:
        V[i] = True
        r = go(G, V, v, l+1, i)
        V[i] = False

        if r != None:
            return [i, *r]


def droga(G):
    V = [False for _ in G]
    r = go(G, V, 0, 1, 0)
    print(r)
    if(len(G) > 107):
        print('107: ', G[107])
    return r


runtests(droga, all_tests=True)
