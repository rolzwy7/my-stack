import random
import maths

def rsa_generate_random_number(keysize):
    choices = [2**x for x in range(4, 12 + 1)]
    if keysize not in choices:
        print("[error] Keysize choices are:")
        for e in choices:
            print(e, ", ", end="")
        print("\n")
        return None
    # @Random number function used - start
    random_number_generator = random.randint
    # @Random number function used - end
    bitsize = keysize // 2
    # Set low limit
    low_limit = 1 << (bitsize - 1)
    # Set high limit
    high_limit = 1
    for i in range(bitsize - 1):
        high_limit = high_limit << 1
        high_limit = high_limit | 1
    # return random number within range [low_limit, high_limit]
    return random_number_generator(low_limit, high_limit)

def rsa_generate_random_prime(keysize, k=2):
    bitsize = keysize // 2
    # generate random number
    number = rsa_generate_random_number(keysize)
    # make sure number is odd
    number = number | 1
    # set two highest bits to 1 (this ensures that high bit of n=p*q is also set)
    number = number | (3 << (bitsize - 2))
    # find prime
    while not maths.is_prime_miller_rabin(number, k):
        number += 2
    return number
