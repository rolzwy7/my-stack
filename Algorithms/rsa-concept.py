# Doesn't work on big numbers

import math
import base64

# algorithms - start
def mod_exp(b, e, m):
    c,E = 1,0
    while E < e:
        E += 1
        c = (b * c) % m
    return c

def mod_mul_inv(a, m):
    for i in range(1,m):
        if ( m*i + 1) % a == 0:
            return ( m*i + 1) // a
    return None

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def lcm(a, b):
    a_cp, b_cp = a, b
    # gcd
    while b != 0:
        a, b = b, a % b
    gcd = a
    ret = abs(a_cp * b_cp) / gcd
    return int(ret)
# algorithms - stop

p = 53 # prime #secret
q = 61 # prime #secret
n = p * q #mul of primes #public
t = lcm(p-1, q-1) # tot function #secret
e = None #used in encrypt #public
for i in range( int(t / 2), 1, -1):
    if gcd(i, t) == 1:
        e = 17
        break
d = mod_mul_inv(e, t) #used in decrypt #for owner only (secret)

print("p =", p)
print("q =", q)
print("n =", n)
print("t =", t)
print("e =", e)
print("d =", d)

print("\nPublic key:")
print("\t(n=%s, e=%s)" % (n, e) )
print("\nPrivate key:")
print("\t(n=%s, d=%s)" % (n, d) )

def encrypt(m):
    c = mod_exp(m, e, n)
    return c

def decrypt(c):
    m = mod_exp(c, d, n)
    return m

pt = 65
print("\nPlaintext =", pt)

c = encrypt(pt)
c_b64 = base64.b64encode(hex(c).encode("utf8"))
c_num = int(base64.b64decode(c_b64), 16)
print("\nEncrypt:")
print("\tbase64 =", c_b64)
print("\tnumber =", c_num)

m = decrypt(c_num)
print("\nDecrypt:")
print("\tmsg    =", m)

if m == pt:
    print("[+] Success")
else:
    print("[-] Failure")
