import math
import random


def ask_is_gt(our_quess):
    # request here
    unknow_number = 100
    return unknow_number > our_quess


def make_quess_int(qr, tries=0):
    center = math.ceil(sum(qr) / 2.)
    if ask_is_gt(center):
        qr[0] = center
    else:
        qr[1] = center
    diff = qr[1] - qr[0]

    if diff == 1:
        return tries, qr[1]
    else:
        tries += 1
        return make_quess_int(qr, tries=tries)


quess_range = [0, 100]
tries, correct = make_quess_int(quess_range)
print(tries, correct)
