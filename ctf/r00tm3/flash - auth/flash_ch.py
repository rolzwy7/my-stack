import hashlib
from itertools import product
pwd_md5hash = "dbbcd6ee441aa6d2889e6e3cae6adebe"
chars = "1234"


def convert(ch, pwd):
    funcs = {
        "1": lambda x: x + "AB",
        "2": lambda x: x + "14",
        "3": lambda x: x + "59",
        "4": lambda x: x[:-1]
    }
    return funcs.get(ch)(pwd)


def check_valid(pwd):
    fours, not_fours = 0, 0
    for _ in pwd:
        fours += 1 if _ == "4" else 0
        not_fours += 1 if _ != "4" else 0

    return not_fours * 2 - fours == 12


c, c_m = 0, 1000
for p in product(chars, repeat=12):
    pwd = "".join(p)
    if not check_valid(pwd):
        continue
    pwd_converted = ""
    for ch in pwd:
        pwd_converted = convert(ch, pwd_converted)
    pwd_converted = "".join(list(reversed(list(pwd_converted))))
    pwd_converted_hash = hashlib.md5(pwd_converted.encode()).hexdigest()

    if pwd_md5hash == pwd_converted_hash:
        print("\n\n[+] Password:", pwd, pwd_converted, pwd_converted_hash)
        exit(0)

    c += 1
    if c % c_m == 0:
        c = 0
        print(pwd, pwd_converted, pwd_converted_hash)

print("\n\n[-] Couldn't find password")
