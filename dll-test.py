import platform
import ctypes

if platform.system() == 'Windows':
	# __stdcall(msvc)
	mydll = ctypes.WinDLL("bin/x64/Release/foo.dll")
else:
	# __cdecl(linux/macOS)
	mydll = ctypes.CDLL("bin/x64/Release/libfoo.so")

mydll.foo_print.argtypes = [ctypes.c_double]
mydll.foo_print.restype = ctypes.c_void_p
mydll.foo_print(10.0)

mydll.foo_printi(20)