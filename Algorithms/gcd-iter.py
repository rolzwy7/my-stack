'''
    Greatest common divisor
'''

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


ex = [
    (53, 101),
    (12, 3) ,
    (11, 66),
]

for e in ex:
    a,b = e[0], e[1]
    print("gcd(%s, %s) :" % (a, b), gcd(a, b))
