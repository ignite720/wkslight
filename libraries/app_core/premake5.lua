project("app_core")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[2], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[2], "%{prj.name}"))
    kind("SharedLib")
    language("C++")
    pchheader("pch.h")
    pchsource("src/pch.cpp")
    files({
        "include/**.h",
        "src/impl/libs/*.cpp",
        "src/impl/test/*.cpp",
        "src/*.cpp",
    })
    includedirs({
        g_wkslight.workspace.libraries.projects.app_core.includedirs,
        "include/app_core",
    })
    libdirs({
        g_wkslight.workspace.libraries.projects.app_core.libdirs,
    })
    defines({
        g_wkslight.workspace.libraries.projects.app_core.defines,
    })
    g_wkslight.libs({
        "app_core_d3d12",
        "app_core_vulkan",
        "bar",
        "baz-qux",
        "FastNoise2",
        "foo",
        "headeronly",
        "imgui",
        "lua",
        "sdl2",
        "sol2",
        "spdlog",
        "XMath",
    })
    filter("options:target_platform=android")
        files({
            "src/impl/platform/android/**.*",
        })
    filter("options:target_platform=pc")
        files({
            "src/impl/platform/pc/**.*",
        })
    filter({ "options:target_platform=pc", "system:linux" })
    filter("options:target_platform=uwp")
        files({
            "src/impl/platform/uwp/**.*",
        })
        -- [[
        -- fix uwp dll start
        links({
            "app_core_d3d12.lib",
            "app_core_vulkan.lib",
            "foo.lib",
        })
        -- fix uwp dll end
        --]]
    filter("options:target_platform=web")
        files({
            "src/impl/platform/web/**.*",
        })
    filter("options:target_platform=android or options:target_platform=web")
        kind("StaticLib")
    filter({ "action:vs* or ninja", "system:windows*", "configurations:Release" })
        exceptionhandling("SEH")
    filter("kind:SharedLib")
        defines({ "__APP_CORE_CONFIG_BUILD_DLL" })
project("app_core_d3d12")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[2], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[2], "%{prj.name}"))
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
        g_wkslight.workspace.libraries.projects.app_core.defines,
    })
    g_wkslight.libs({
        "foo",
        "headeronly",
        "spdlog",
        "XMath",
    })
    filter("options:target_platform=android or options:target_platform=web")
        kind("StaticLib")
    filter("kind:SharedLib")
        defines({ "__APP_CORE_CONFIG_BUILD_DLL" })
project("app_core_vulkan")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[2], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[2], "%{prj.name}"))
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
        g_wkslight.workspace.libraries.projects.app_core.defines,
    })
    g_wkslight.libs({
        "foo",
        "headeronly",
        "spdlog",
        "XMath",
    })
    filter("options:target_platform=android or options:target_platform=web")
        kind("StaticLib")
    filter("kind:SharedLib")
        defines({ "__APP_CORE_CONFIG_BUILD_DLL" })