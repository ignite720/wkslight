project("bar")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdirs[2], "%{prj.name}"))
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
    })
    filter("kind:SharedLib")
        defines({ "__BAR_CONFIG_BUILD_DLL" })