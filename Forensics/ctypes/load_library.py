import ctypes

# load get printf from msvcrt
msvcrt_lib = ctypes.cdll.msvcrt
printf = msvcrt_lib.printf

a = ctypes.c_int(56)

printf(b"Value: %d", a.value)
