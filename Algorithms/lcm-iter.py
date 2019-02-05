'''
    Least common multiple
'''

## gcd(a, b) = abs(a,b) / lcm(a, b)
## lcm(a, b) = abs(a,b) / gcd(a, b)

def lcm(a, b):
    a_cp, b_cp = a, b
    # gcd
    while b != 0:
        a, b = b, a % b
    gcd = a
    # return abs(a_cp * b_cp) / gcd
    return abs(a_cp * b_cp) // gcd

ex = [
    (280, 150),
    (525, 2310),
]

for e in ex:
    a,b = e[0], e[1]
    print("lcm(%s, %s) :" % (a, b), lcm(a, b))
