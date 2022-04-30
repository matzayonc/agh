def f(T, i, p):

    if i == len(T):
        return 0

    if p != None and (T[i][0] < T[p][0] or T[i][1] > T[p][1]):
        return f(T, i+1, p)

    return max(f(T, i+1, p), f(T, i+1, i)+1)
