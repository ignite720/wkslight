project("app_core")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    kind("SharedLib")
    language("C++")
    files({
        "include/**.h",
        "src/impl/platform/**.*",
        "src/*.cpp",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.app_core.includedirs,
    })
    defines({
        "APP_CORE_BUILD_AS_DLL",
    })
    g_wkslight.libs({
        "app_core_d3d12",
        "app_core_vulkan",
        "bar",
        "foo",
        "headeronly",
        "lua",
        "sol2",
    })
    filter("options:target_platform=uwp")
        -- [[
        -- fix uwp dll start
        libdirs({
            "%{g_wkslight.targetdir}",
        })
        links({
            "app_core_d3d12.lib",
            "app_core_vulkan.lib",
            "bar.lib",
            "foo.lib",
        })
        -- fix uwp dll end
        --]]
    filter("options:target_platform=android or options:target_platform=web")
        kind("StaticLib")
project("app_core_d3d12")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    kind("SharedLib")
    language("C++")
    files({
        "include/**.h",
        "src/impl/gfx/d3d12/**.*",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.app_core.includedirs,
    })
    defines({
        "APP_CORE_BUILD_AS_DLL",
    })
    g_wkslight.libs({
        "foo",
    })
project("app_core_vulkan")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    kind("SharedLib")
    language("C++")
    files({
        "include/**.h",
        "src/impl/gfx/vulkan/**.*",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.app_core.includedirs,
    })
    defines({
        "APP_CORE_BUILD_AS_DLL",
    })
    g_wkslight.libs({
        "foo",
    })