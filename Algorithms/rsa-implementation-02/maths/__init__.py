from random import randint
import math

# Extended Euclidean Algorithm
def xgcd(a, b):
    x0, x1, y0, y1 = 1, 0, 0, 1
    while a != 0:
        q, b, a = b // a, a, b % a
        x0, x1 = x1, x0 - q * x1
        y0, y1 = y1, y0 - q * y1
    return  b, x0, y0

# Modular Exponentataion
# def mod_exp(a, b, c):
#     if b == 1:
#         return 1
#     elif b % 2 == 0:
#         d = mod_exp(a, b//2, c)
#         return (d * d) % c
#     else:
#         return ((a % c) * mod_exp(a, b-1, c)) % c

# Modular Inverse
def mod_inv(a, modulo):
    gcd, x, y = xgcd(a, modulo)
    return y + modulo

# Modular Exponentataion by Squaring
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

# Miller-Rabin primality test
# @params
# n - number tested for primality
# k - accuracy (2 is sufficient in most cases)
# @returns
# True - probably prime
# False - probably not prime
def is_prime_miller_rabin(n, k, debug=False):
    mod_exponentation_function = mod_exp_by_squaring
    # 1
    if n <= 1: return False;
    elif n <= 3: return True;
    elif n % 2 == 0: return False;
    # 2
    result, r, d = 0, 1, 0
    while result == 0:
        result = (n-1) % 2 ** r
        r += 1
    r -= 2
    d = (n-1) // (2**r)
    # 3
    for _ in range(k): # witness loop
        a = randint(2, n-2)
        x = mod_exponentation_function(a, d, n)
        if x == 1 or x == n-1: continue;
        continue_witness = False
        for __ in range(r-1):
            x = (x**2) % n
            if x == n-1:
                continue_witness = True
                break
        if continue_witness: continue;
        return False
    return True

# Least Common Multiple
def lcm(a, b):
    a_cp, b_cp = a, b
    # gcd
    while b != 0:
        a, b = b, a % b
    gcd = a
    return abs(a_cp * b_cp) // gcd

# Greathest Common Divider
def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a
