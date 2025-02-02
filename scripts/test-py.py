import platform
import ctypes

if platform.system() == 'Windows':
    # __stdcall(msvc)
    the_dll = ctypes.WinDLL("../bin/target/x64/Release/foo.dll")
else:
    # __cdecl(linux/macOS)
    if platform.system() == 'Linux':
        the_dll_suffix = "so"
    else:
        the_dll_suffix = "dylib"
    the_dll = ctypes.CDLL(f"bin/target/x64/Release/libfoo.{the_dll_suffix}")

the_dll.foo_print.argtypes = [ctypes.c_double]
the_dll.foo_print.restype = ctypes.c_void_p
the_dll.foo_print(10.0)

the_dll.foo_printi(20)