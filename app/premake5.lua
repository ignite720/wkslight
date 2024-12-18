project("app")
    location(path.join(g_wkslight.workspacedir, "%{prj.name}"))
    targetdir(g_wkslight.targetdir)
    kind("ConsoleApp")
    language("C++")
    uuid("BE2461B7-236F-4278-81D3-F0D476F9A4C0")
    debugdir("")
    debugargs({
        "--foobar",
    })
    pchheader("pch.h")
    pchsource("src/pch.cpp")
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
    g_wkslight.libs({
        "app_core",
        --"bar",
        "foo",
        "headeronly",
        "lua",
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
            "qux",
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
    filter("options:target_platform=uwp")
        files({
            "Package.appxmanifest",
        })
        -- [[
        -- fix uwp dll start
        libdirs({
            "%{g_wkslight.targetdir}",
        })
        links({
            "app_core.lib",
        })
        -- fix uwp dll end
        --]]
    filter({ "options:target_platform=uwp", "files:assets/*.png", "files:assets/**/*.png" })
        deploy("true")
    filter("platforms:wasm")
        g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)