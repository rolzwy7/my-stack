import ctypes

class case(ctypes.Union): # In union members share the same memory location
    _fields_   = [
        ("evidence_int", ctypes.c_int),
        ("evidence_long", ctypes.c_long),
        ("evidence_char", ctypes.c_char * 4)
    ]

new_evidence = case(int(42))
print("Evidence as Integer : %i" % new_evidence.evidence_int)
print("Evidence as Long    : %ld" % new_evidence.evidence_long)
print("Evidence as Char    : %s" % new_evidence.evidence_char)
