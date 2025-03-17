project("all_gen")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[1], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[1], "%{wks.name}", "%{prj.name}"))
    kind("StaticLib")
    language("C")
    files({
        "src/dummy.c",
    })
    filter("action:vs*")
        prebuildcommands({ "%{g_wkslight.location}/scripts/premake5-generate-pc-vs.bat dummy" })