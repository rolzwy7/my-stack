def exp_by_squaring_iter(b, e):
    if e == 0: return 1;
    if e < 0:
        b = 1 / b
        e = -e
    tmp = 1
    while e > 1:
        if e % 2 == 0:
            b = b**2
            e = e/2
        else:
            tmp = b * tmp
            b = b ** 2
            e = (e-1) / 2
    return b * tmp
