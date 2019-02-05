# https://www.di-mgt.com.au/rsa_alg.html

import time
import generators as gen
import maths
import random

# Config
# ###################
KEYSIZE = 512
TEST_ITERATIONS = 10
TEST_VALUE = 65
E_ = 65537
# Config
# ###################

# generate p and q
# make sure p and q aren't the same
p,q = 1,1
while p == q:
    q = gen.rsa_generate_random_prime(KEYSIZE)
    p = gen.rsa_generate_random_prime(KEYSIZE)
# make sure p > q (for CRT)
if p < q: p,q = q,p;

# modulus
n = p * q
# totient
t = maths.lcm(p - 1, q - 1)
# public exponent
e = E_
# private exponent
d = maths.mod_inv(e, t)

# Applying CRT
d_p = d % (p - 1)
d_q = d % (q - 1)
q_inv = maths.mod_inv(q, p)

# Encrypt function
def encrypt(m, e, n):
    mod_exp_function = pow
    # mod_exp_function = pow
    return mod_exp_function(m, e, n)

# Decrypt function
def decrypt_crt(c, d_p, d_q, p, q, q_inv):
    mod_exp_function = pow
    # mod_exp_function = pow
    # Decryption with CRT
    m1 = mod_exp_function(c, d_p, p)
    m2 = mod_exp_function(c, d_q, q)
    h = (q_inv * (m1 - m2)) % p
    return m2 + h * q # = m

print(" > p =", p)
print(" > q =", q)
print(" > n =", n)
print(" > t =", t)
print(" > e =", e)
print(" > d =", d)
print(" > d_p   =", d_p)
print(" > d_q   =", d_q)
print(" > q_inv =", q_inv)

# Test if RSA is valid
test_values = [64,85,94,15,24,75,98,45,91,90]
for element in test_values:
    m = element
    m_cp = m
    c = encrypt(m, e, n)
    m = decrypt_crt(c, d_p, d_q, p, q, q_inv)
    if m != m_cp:
        print("[-] RSA - Failure Original != Decoded")
        print("original  =", m_cp)
        print("decrypted =", m)
        exit(0)

print("[+] Validity test passed")

# Speed test - START
# #####################

print("\n[*] Speed Test: RSA-%sbit" % n.bit_length())

for it in range(1, 100 + 1):

    current_iter_test = TEST_ITERATIONS * 10**(it)
    print( "[*] Iterations: {:,}".format(current_iter_test) )
    # Speed test - encrypt
    test_start = time.time()
    for i in range(current_iter_test):
        c = encrypt(TEST_VALUE, e, n)
    test_end = time.time()
    test_result = test_end - test_start
    print(
        "\t- encrypt: %.2f s" % ( test_result)
    )

    # # Speed test - decrypt
    # test_start = time.time()
    # for i in range(current_iter_test):
    #     m = decrypt_crt(c, d_p, d_q, p, q, q_inv)
    # test_end = time.time()
    # test_result = test_end - test_start
    # print(
    #     "\t- decrypt: %.2f s" % ( test_result)
    # )

# Speed test - END
# #####################
