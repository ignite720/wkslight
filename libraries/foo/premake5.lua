project("foo")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[2], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[2], "%{prj.name}"))
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
    })
    filter("options:target_platform=android or options:target_platform=web")
        kind("StaticLib")
    filter("kind:SharedLib")
        defines({ "__FOO_CONFIG_BUILD_DLL" })