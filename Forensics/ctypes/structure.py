import ctypes

class case(ctypes.Structure): # In union members share the same memory location
    _fields_   = [
        ("name", ctypes.c_char * 16),
        ("surname", ctypes.c_char * 16),
        ("age", ctypes.c_short)
    ]

new_record = case(b"Name", b"Surname", 17)

print(new_record.name)
print(new_record.surname)
print(new_record.age)
