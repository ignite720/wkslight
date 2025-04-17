project("app")
    location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[1], "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[1], "%{wks.name}", "%{prj.name}"))
    kind("ConsoleApp")
    language("C++")
    --uuid("BE2461B7-236F-4278-81D3-F0D476F9A4C0")
    debugdir("")
    debugargs({
        "99999",
    })
    files({
        "assets/**.*",
        "src/**.h",
        "src/**.cpp",
        "src-java/**.*",
    })
    -- [[
    vpaths({
        --["*"] = "src",
        ["VHeaders/*"] = { "src/**.h", "src/**.hpp", "src/**.inl" },
        ["VSources/*"] = { "**.c", "**.cpp" },
        ["VDocs/*"] = "**.txt",
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
        postbuildcommands({
            "{COPYDIR} %[%{!cfg.debugdir}/assets] %[%{!cfg.targetdir}/assets]",
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
        -- pass
    filter("action:not ninja")
        -- pass
    filter("action:not xcode*")
        pchheader("pch.h")
        pchsource("src/pch.cpp")
    filter("action:vs*")
        vspropertysheets({
            [[..\..\app\doc\SDL2.props]],
        })