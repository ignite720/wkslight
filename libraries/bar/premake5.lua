project("bar")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    kind("StaticLib")
    language("C++")
    files({
        "include/**.h",
        "src/**.cpp",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.bar.includedirs,
    })
    defines({
        g_wkslight.workspace.libraries.projects.bar.defines,
        "BAR_BUILD_AS_DLL",
    })