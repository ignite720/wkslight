project("tests")
    location(path.join(g_wkslight.workspacedir, "%{prj.group}", "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, "%{prj.group}", "%{prj.name}"))
    kind("ConsoleApp")
    language("C++")
    files({
        "src/**.*",
    })
    g_wkslight.libs_executable({
        "Catch2",
    })