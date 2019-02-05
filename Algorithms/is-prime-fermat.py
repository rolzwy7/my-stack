from random import randint
import math

def is_prime_fermat(n, k):
    # 1
    if n <= 1: return False;
    elif n <= 3: return True;
    elif n % 2 == 0:
        return False
    # 2
    for _ in range(k):
        a = randint(2, n-2)
        if pow(a, n-1, n) != 1:
            return False
    return True

test = int(63514e+150)
print(test.bit_length())
p = test

for i in range(1000):
    testcase = p+i
    if is_prime_fermat(testcase, 2):
        print("Prime:", testcase)
