import ctypes

# __cdecl
#mydll = ctypes.CDLL("bin/x64/Release/foo.dll")

# __stdcall(msvc)
mydll = ctypes.WinDLL("bin/x64/Release/foo.dll")

mydll.foo_print.argtypes = [ctypes.c_double]
mydll.foo_print.restype = ctypes.c_void_p
mydll.foo_print(10.0)

mydll.foo_printi(20)