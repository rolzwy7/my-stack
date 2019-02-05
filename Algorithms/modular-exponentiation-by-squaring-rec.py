def mod_exp_by_squaring(b, e, m):
    if (e == 0):
        return 1;
    if (e == 1):
        return b % m;

    t = mod_exp_by_squaring(b, e // 2, m);
    t = (t * t) % m;

    if (e % 2 == 0):
        return t;
    else:
        return ((b % m) * t) % m;
