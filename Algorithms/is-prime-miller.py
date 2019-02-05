from random import randint
import math

# Miller Rabin
def miller(n, k, debug=False):
    def mod_exp(b, e, m):
        c,E = 1,0
        while E < e:
            E += 1
            c = (b * c) % m
        return c
    # 1
    if n <= 1: return False;
    elif n <= 3: return True;
    elif n % 2 == 0: return False;
    if debug: print("Finished basic check");
    # 2
    result, r, d = 0, 1, 0
    while result == 0:
        result = (n-1) % 2 ** r
        r += 1
    r -= 2
    d = (n-1) // (2**r)
    if debug: print("Finished calculating r & d");
    # print(r,d)
    # 3
    for _ in range(k): # witness loop
        if debug: print("loop / k =", _, "/", k);
        a = randint(2, n-2)
        if debug: print("Got random a");
        if debug: print("d bit lenght:", d.bit_length());
        # x = mod_exp(a, d, n)
        x = pow(a, d, n)
        if debug: print("Calculated mod exp");
        if x == 1 or x == n-1: continue;
        continue_witness = False
        for __ in range(r-1):
            x = (x**2) % n
            if x == n-1:
                continue_witness = True
                break
        if continue_witness: continue;
        if debug: print("Finished inner loop: composite");
        return False
    if debug: print("Finished witnessed loop: probably prime");
    return True
