project("app")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[1], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[1], "%{wks.name}", "%{prj.name}"))
    kind("ConsoleApp")
    language("C++")
    --uuid("BE2461B7-236F-4278-81D3-F0D476F9A4C0")
    pchheader("pch.h")
    pchsource("src/pch.cpp")
    debugdir("")
    debugargs({
        "99999",
    })
    files({
        "assets/**.*",
        "shaders/**.*",
        "src/**.h",
        "src/**.cpp",
        "src-java/**.*",
    })
    --[[
    vpaths({
        --["*"] = "src",
        ["VHeaders/*"] = { "src/**.h", "src/**.hpp", "src/**.inl" },
        ["VSources/*"] = { "**.c", "**.cpp" },
        ["VDocs/*"] = "**.txt",
        ["VResources/*"] = { "**.rc", "*.ico" },
    })
    --]]
    includedirs({
        "%{g_wkslight.location}/foobar/include",
        "src",
    })
    links({
        "foobar",
    })
    g_wkslight.libs_executable({
        "app_core",
        "baz-qux",
        "foo",
        "headeronly",
        "lua",
        "sdl2",
        "spdlog",
        "XMath",
    })
    filter("options:target_platform=android")
        links({
            "log",
        })
        linkoptions({
            "-Wl,--no-undefined",
        })
        androiddependencies({
            "com.android.support:support-v4:27.1.0",
        })
        assetpackdependencies({
            "pack",
        })
        --[[
        androidprojectdependencies({
            "quux",
        })
        --]]
        androidkeystorefile("../../../../.android/wkslight.keystore")
        androidstorepassword("android")
        androidkeyalias("wkslightkey")
        androidkeypassword("android")
        apkoutputpath("../../../../../../../bin/apk-")
        assetdirs({
            "assets",
        })
    filter({ "options:target_platform=pc", "options:pc_deploy_assets" })
        prebuildcommands({
            --"{MKDIR} %[%{!cfg.targetdir}/assets]",
            --"{COPYDIR} %[%{!cfg.debugdir}/assets/*] %[%{!cfg.targetdir}/assets]",
            --"{MKDIR} %[%{!cfg.targetdir}/assets/shaders]",
            "{COPYDIR} %[%{!cfg.debugdir}/assets] %[%{!cfg.targetdir}/assets]",
        })
    filter({ "options:target_platform=pc", "options:pc_deploy_assets", "options:ci", "files:shaders/**.vert", "action:not ninja" })
        buildmessage("Compiling %[%{!file.relpath}], %[%{!file.abspath}]")
        buildcommands({
            "glslangValidator -V %[%{!file.abspath}] -o %[%{!cfg.targetdir}/assets/shaders/%{file.name}.spv]",
        })
        buildoutputs({
            "%{!cfg.targetdir}/assets/shaders/%{file.name}.spv",
        })
    filter({ "options:target_platform=pc", "system:windows" })
        files({
            "**.rc",
            "*.ico",
        })
    filter("options:target_platform=uwp")
        files({
            "Package.appxmanifest",
        })
        -- [[
        -- fix uwp dll start
        links({
            "app_core.lib",
        })
        -- fix uwp dll end
        --]]
    filter({ "options:target_platform=uwp", "files:assets/*.png or assets/**/*.png" })
        deploy("true")
    filter("options:target_platform=web")
        links({
            "imgui",
        })
    filter("platforms:wasm")
        g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)
    filter({ "action:codelite" })
    filter({ "action:ninja", "system:windows*" })
        links({ "Shell32" })
    filter({ "action:ninja", "system:windows*", "kind:ConsoleApp" })
        linkoptions({ "/SUBSYSTEM:CONSOLE" })
    filter({ "action:ninja", "system:windows*", "kind:WindowedApp" })
        linkoptions({ "/SUBSYSTEM:WINDOWS" })
    filter("action:not xcode*")
    filter("action:vs*")
        vspropertysheets({
            -- [[..\..\app\doc\SDL2.props]],
        })