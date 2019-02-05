#          Array #  BST       # Hash Table #
############################################
# insert   O(1)     O(log n)    O(1)
# search   O(n)     O(log n)    O(1)
# delete   O(n)     O(log n)    O(1)

def gcd(a,b):
    while b != 0:
        a,b = b,a % b
    return a

###########################
#   Adresowanie liniowe   #
###########################
# h(x, 0) = x mod 8
# h(x, i) = [h(x,0) + 3i] mod 8
print("h(x, 0) = x mod 8")
print("h(x, i) = [h(x,0) + 3i] mod 8")
print("GCD(8, 3) =", gcd(8,3), end="\n\n")
def add(array, x):

    if isinstance(x, str):
        for_zero = len(x) % 8
    else:
        for_zero = x % 8

    for i in range(len(array)):
        for_gt_zero = ( for_zero + 3 * i ) % 8
        if array[for_gt_zero] == None:
            array[for_gt_zero] = x
            break
    return array

array = 8 * [None]
to_add = [  57,
            14,
            18,
            8,
            111,
            87,
            25,
            33
        ]
for _ in to_add:
    array = add(array, _)
    print(array)

array = 8 * [None]
to_add = [  "John",
            "Bob",
            "Anna",
            "Max",
            "Charlie",
            "George",
            "Diane",
            "Chloe"
        ]
for _ in to_add:
    array = add(array, _)
    print(array)

# h(x, 0) = x mod 8
# h(x, i) = [h(x,0) + 3i] mod 8
# GCD(8, 3) = 1

# [None, 57, None, None, None, None, None, None]
# [None, 57, None, None, None, None, 14, None]
# [None, 57, 18, None, None, None, 14, None]
# [8, 57, 18, None, None, None, 14, None]
# [8, 57, 18, None, None, None, 14, 111]
# [8, 57, 18, None, None, 87, 14, 111]
# [8, 57, 18, None, 25, 87, 14, 111]
# [8, 57, 18, 33, 25, 87, 14, 111]
#
# [None, None, None, None, 'John', None, None, None]
# [None, None, None, 'Bob', 'John', None, None, None]
# [None, None, None, 'Bob', 'John', None, None, 'Anna']
# [None, None, None, 'Bob', 'John', None, 'Max', 'Anna']
# [None, None, 'Charlie', 'Bob', 'John', None, 'Max', 'Anna']
# [None, 'George', 'Charlie', 'Bob', 'John', None, 'Max', 'Anna']
# [None, 'George', 'Charlie', 'Bob', 'John', 'Diane', 'Max', 'Anna']
# ['Chloe', 'George', 'Charlie', 'Bob', 'John', 'Diane', 'Max', 'Anna']
