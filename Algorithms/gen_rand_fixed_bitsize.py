from random import randint

def gen_rand_fixed_bitsize(bitsize):
    lower_limit = 1 << (bitsize - 1)
    higher_limit = 1
    for i in range(bitsize-1):
        higher_limit = higher_limit << 1
        higher_limit = higher_limit | 1
    return randint(lower_limit, higher_limit)

a = generate(512)
print("num        :", a)
print("bit_length :", a.bit_length())
