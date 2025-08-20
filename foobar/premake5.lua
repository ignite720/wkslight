project("foobar")
    location(path.join(g_wkslight.workspacedir, "%{prj.group}", "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, "%{prj.group}", "%{prj.name}"))
    kind("StaticLib")
    language("C++")
    files({
        "include/**.h",
        "src/**.cpp",
    })
    includedirs({
        "include",
    })
    g_wkslight.libs({
        "spdlog",
    })