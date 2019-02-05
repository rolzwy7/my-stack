def mod_exp(b, e, m):
    c,E = 1,0
    while E < e:
        E += 1
        c = (b * c) % m
    return c
