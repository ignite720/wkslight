project("foo")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
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