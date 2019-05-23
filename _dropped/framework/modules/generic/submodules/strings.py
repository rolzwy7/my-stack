import re

def regex_strings(data):
    pattern = re.compile(b"[A-Za-z0-9/\-:.,_$%'()[\]<> ]{4,}")
    ret = pattern.findall(data)
    return ret, len(ret)
