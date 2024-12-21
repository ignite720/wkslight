project("foo")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdirs[2], "%{prj.name}"))
    kind("SharedLib")
    language("C++")
    files({
        "include/**.h",
        "src/**.cpp",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.foo.includedirs,
    })
    defines({
        g_wkslight.workspace.libraries.projects.foo.defines,
        "FOO_BUILD_AS_DLL",
    })
    filter("options:target_platform=android")
        kind("StaticLib")