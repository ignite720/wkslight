project("tests")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[1], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[1], "%{wks.name}", "%{prj.name}"))
    kind("ConsoleApp")
    language("C++")
    files({
        "src/**.*",
    })
    g_wkslight.libs_executable({
        "Catch2",
        "headeronly",
    })