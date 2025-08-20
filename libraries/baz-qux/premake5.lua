project("baz-qux")
    location(path.join(g_wkslight.workspacedir, "libraries", "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, "libraries", "%{prj.name}"))
    kind("StaticLib")
    language("C++")
    files({
        "include/**.h",
        "src/**.cpp",
    })
    includedirs({
        "include",
    })