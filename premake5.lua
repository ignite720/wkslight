require("premake5-modules/android-studio/android_studio")
require("premake5-modules/cmake")
require("premake5-modules/emscripten")
require("premake5-modules/ninja")
require("premake5-modules/vspropertysheets")
require("premake5-modules/winrt")
g_wkslight = require("premake5-modules/wkslight")

require("wkslight-config")
g_wkslight = g_wkslight.makereadonlytbl(g_wkslight)

newoption({
    trigger = "target_platform",
    description = "Generate project files for the specified target platform",
    value = "<TARGET_PLATFORM>",
    allowed = {
        { "android", "Generate `Android` projects" },
        { "pc", "Generate `PC` projects" },
        { "uwp", "Generate `Universal Windows Platform` projects" },
        { "web", "Generate `Web` projects" },
    },
    default = "pc",
})

newoption({
    trigger = "asan",
    description = "Enable AddressSanitizer.",
})
newoption({
    trigger = "avx2",
    description = "Enable Advanced Vector Extensions 2.",
})
newoption({
    trigger = "ci",
    description = "Continuous Integration.",
})
newoption({
    trigger = "pc_deploy_assets",
    description = "Whether to deploy assets on PC platform.",
})
newoption({
    trigger = "web_sync_fetch",
    description = "Synchronous Fetch operations are available both on the main thread and pthreads.",
})

workspace(g_wkslight.workspace.name)
    location(path.getbasename(g_wkslight.workspacedir))
    configurations({ "Debug", "Release" })
    characterset("Default")
    cppdialect(g_wkslight.workspace.cppdialect)
    floatingpoint("Default")
    rtti("Default")
    exceptionhandling("Default")
    defines({
        "__STDC_CONSTANT_MACROS",
        "__STDC_FORMAT_MACROS",
        "__STDC_LIMIT_MACROS",
        "_USE_MATH_DEFINES",
    })
    filter("options:target_platform=pc or options:target_platform=uwp")
        platforms({
            --"x86",
            "x64",
        })
    filter("options:target_platform=android")
        defines({ "TARGET_PLATFORM_ANDROID=1" })
        androidabis(g_wkslight.extras.android.androidabis)
        androidsdkversion(g_wkslight.extras.android.androidsdkversion)
        androidminsdkversion(g_wkslight.extras.android.androidminsdkversion)
        androidndkpath(g_wkslight.extras.android.androidndkpath)
        gradleversion(g_wkslight.extras.android.gradleversion)
        gradlewrapper(g_wkslight.extras.android.gradlewrapper)
        androidrepositories(g_wkslight.extras.android.androidrepositories)
        androidnamespace(g_wkslight.extras.android.androidnamespace)
        assetpacks(g_wkslight.extras.android.assetpacks)
    filter("options:target_platform=pc")
        defines({ "TARGET_PLATFORM_PC=1" })
    filter("options:target_platform=uwp")
        defines({ "TARGET_PLATFORM_UWP=1" })
        cppdialect(g_wkslight.workspace.cppdialectuwp)
        system("windowsuniversal")
        defaultlanguage("en-US")
        generatewinmd("false")
        consumewinrtextension2("false")
    filter("options:target_platform=web")
        defines({ "TARGET_PLATFORM_WEB=1" })
        platforms({ "wasm" })
        toolset("emcc")
        buildoptions({
            "-fexceptions",
        })
        linkoptions({
            "-fexceptions",
            "-sNO_DISABLE_EXCEPTION_CATCHING",
            "-sDISABLE_EXCEPTION_CATCHING=0",
        })
    filter("system:windows")
        systemversion("latest")
    filter("system:linux")
        pic("On")
    filter("system:macosx")
        --buildoptions({ "-iquote" })
    filter({ "action:vs* or ninja", "system:windows*" })
        startproject(g_wkslight.workspace.startproject)
        staticruntime("Off")
        characterset("MBCS")
        --usestandardpreprocessor("On")
        conformancemode("Yes")
        flags({ "MultiProcessorCompile" })
        defines({
            --"_CRT_SECURE_NO_DEPRECATE",
            --"_CRT_NONSTDC_NO_DEPRECATE",
            "_CRT_SECURE_NO_WARNINGS",
            --"_CRT_NONSTDC_NO_WARNINGS",
            "_WINSOCK_DEPRECATED_NO_WARNINGS",
            "_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
            "_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS",
            "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS",
            --"_HAS_STD_BYTE=0",
            "NOMINMAX",
        })
        buildoptions({
            --"/permissive",
            "/sdl-",
            "/utf-8",
            "/wd4005",
            "/Zc:__cplusplus",
            --"/Zc:char8_t-",
            "/Zc:preprocessor",
        })
        disablewarnings({
            "4251",
            "4503",
            "4616",
            "4819",
            "4996",
        })
    filter({ "action:gmake*", "system:not linux", "kind:*App or StaticLib" })
        buildoptions({
            "-static",
        })
    filter("action:xcode*")
        xcodebuildsettings({
            ["ALWAYS_SEARCH_USER_PATHS"] = "YES",
            ["GCC_PRECOMPILE_PREFIX_HEADER"] = "YES",
            --["USER_HEADER_SEARCH_PATHS"] = [["foodir" "bardir"]],
        })
    filter("configurations:Debug")
        defines({ "_DEBUG" })
        optimize("Off")
        symbols("On")
    filter("configurations:Release")
        defines({ "NDEBUG" })
        optimize("Speed")
        symbols("Off")
    filter({ "options:target_platform=pc", "options:asan", "configurations:Debug", "action:gmake*", "system:linux", "toolset:gcc or clang" })
        sanitize({
            "Address",
            --"Fuzzer",
            --"Thread",
            --"UndefinedBehavior",
        })
    filter({ "options:target_platform=pc", "options:avx2" })
        vectorextensions("AVX2")
    filter({ "options:target_platform=web", "options:web_sync_fetch" })
        defines({ "WEB_SYNC_FETCH=1" })
        buildoptions({
            "-pthread",
        })
        linkoptions({
            "--proxy-to-worker",
            --"-sPROXY_TO_WORKER=1",
            --"-sPROXY_TO_PTHREAD=1",
            --"-sUSE_PTHREADS=1",
            --"-sPTHREAD_POOL_SIZE=8",
        })
group(g_wkslight.workspace.libraries.group)
    for k, v in pairs(g_wkslight.workspace.libraries.projects) do
        if g_wkslight.isenabled(v) and v.location ~= nil then
            include(v.location)
        end
    end
group("")
    for i, v in ipairs(g_wkslight.workspace.projects) do
        include(v)
    end
group("all_gen")
    project("rebuild_me")
        location(path.join(g_wkslight.workspacedir, g_wkslight.placeholders[1], "%{prj.name}"))
        targetdir(g_wkslight.targetdir)
        objdir(path.join(g_wkslight.baseobjdir, g_wkslight.placeholders[1], "%{wks.name}", "%{prj.name}"))
        kind("StaticLib")
        language("C")
        files({ "dummy.c" })
        filter({ "options:target_platform=pc", "action:vs*" })
            kind("Utility")
            prebuildcommands({ "%{g_wkslight.location}/scripts/premake5-generate-pc-vs.bat rebuild_me" })
        filter({ "options:target_platform=uwp", "action:vs*" })
            postbuildcommands({ "%{g_wkslight.location}/scripts/premake5-generate-uwp.bat rebuild_me" })