'''
    Factorial
'''

def factorial(N):
    if N == 0:
        return 1
    else:
        return N * factorial(N - 1)

for i in range(0, 10+1):
    print(i, "|", factorial(i))
