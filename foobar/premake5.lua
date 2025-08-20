project("foobar")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, "%{wks.name}", "%{prj.name}"))
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