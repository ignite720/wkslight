require("premake5-modules/android-studio/android_studio")
require("premake5-modules/emscripten")
require("premake5-modules/vspropertysheets")
require("premake5-modules/winrt")
require("premake5-wkslight")
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
    default = "pc"
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
    filter("options:not target_platform=android")
        platforms({
            --"x86",
            "x64",
        })
    filter("options:target_platform=android")
        androidabis(g_wkslight.extras.android.androidabis)
        androidsdkversion(g_wkslight.extras.android.androidsdkversion)
        androidminsdkversion(g_wkslight.extras.android.androidminsdkversion)
        androidndkpath(g_wkslight.extras.android.androidndkpath)
        gradleversion(g_wkslight.extras.android.gradleversion)
        gradlewrapper(g_wkslight.extras.android.gradlewrapper)
        androidrepositories(g_wkslight.extras.android.androidrepositories)
    filter("options:target_platform=uwp")
        cppdialect("C++17")
        system("windowsuniversal")
        defaultlanguage("en-US")
        generatewinmd("false")
        consumewinrtextension2("false")
    filter("options:target_platform=web")
        platforms({ "wasm" })
        toolset("emcc")
        linkoptions({
            --"-sUSE_PTHREADS=1",
            --"-sPTHREAD_POOL_SIZE=8",
            "-sNO_DISABLE_EXCEPTION_CATCHING",
        })
    filter("system:windows")
        systemversion("latest")
    filter("system:linux")
        pic("On")
    filter("action:vs*")
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
            --"_HAS_STD_BYTE=0",
            "NOMINMAX",
        })
        buildoptions({
            --"/sdl-",
            "/utf-8",
            "/Zc:char8_t-",
            "/Zc:preprocessor",
            "/Zc:__cplusplus",
        })
    filter({ "action:gmake*", "system:not linux", "kind:*App or StaticLib" })
        buildoptions({ "-static" })
    filter("configurations:Debug")
        defines({ "_DEBUG" })
        symbols("On")
        optimize("Off")
    filter("configurations:Release")
        defines({ "NDEBUG" })
        symbols("Off")
        optimize("Speed")
group(g_wkslight.workspace.libraries.name)
    for k, v in pairs(g_wkslight.workspace.libraries.projects) do
        if v.location ~= nil then
            include(v.location)
        end
    end
group("")
    for i, v in ipairs(g_wkslight.workspace.projects) do
        include(v)
    end