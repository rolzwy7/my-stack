from random import randint
import math

# Naive Simple
def is_prime_simple(N):
    if N <= 1:       return False;
    elif N <= 3:     return True;
    elif N % 2 == 0: return False;
    elif N % 3 == 0: return False;
    i = 5
    while i**2 <= N:
        if N % i == 0 or N % (i + 2) == 0:
            return False
        i = i + 6
    return True
