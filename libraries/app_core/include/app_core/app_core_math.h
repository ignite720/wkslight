#pragma once

#include <foo/foo_macros.h>

#include <mathx/mathx_rtm.h>
using namespace rtm;

#if !defined(__APPLE__)
PRAGMA_WARNING_PUSH
PRAGMA_WARNING_IGNORE_CLANG("-Wattributes")
PRAGMA_WARNING_IGNORE_GCC("-Wattributes")
PRAGMA_WARNING_IGNORE_MSVC(4616)
#include <mathx/mathx_xmath.h>
PRAGMA_WARNING_POP

using namespace XMath;
#endif