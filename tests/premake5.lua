project("tests")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, "%{wks.name}", "%{prj.name}"))
    kind("ConsoleApp")
    language("C++")
    files({
        "src/**.*",
    })
    g_wkslight.libs_executable({
        "Catch2",
    })