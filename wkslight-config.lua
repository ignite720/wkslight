g_wkslight.clean = {
    dirs_to_delete = {
        enabled = true,
        items = {
            ".vs",
            "bin",
            "build",
            "build-cmake",
        },
    },
    files_to_delete = {
        enabled = false,
        items = {
            --"*.db",
            --"*.Makefile",
            --"*.make",
            --"*.opendb",
            --"*.sln",
            --"*.vcxproj",
            --"*.vcxproj.filters",
            --"*.vcxproj.user",
            --"*.xcodeproj",
            --"*.xcworkspace",
        },
    },
}
g_wkslight.workspace = {
    name = "wkslight",
    startproject = "app",
    cppdialect = "C++20",
    cppdialectuwp = "C++20",
    projects = { -- Sort by dependencies
        foobar = {
            location = "foobar",
        },
        app = {
            location = "app",
        },
        tests = {
            enabled = function()
                if _OPTIONS["target_platform"] == "pc" then
                    return true
                end
                return false
            end,
            location = "tests",
        },
    },
    libraries = {
        group = "libraries",
        projects = { -- Sort alphabetically
            app_core = {
                location = "libraries/app_core",
                includedirs = {
                    "%{g_wkslight.librariesdir}/app_core/include",
                },
                libdirs = {
                    "%{g_wkslight.targetdir}",
                },
                defines = {
                    "APP_CORE_DLL",
                },
                links = {
                    "app_core",
                    "app_core_d3d12",
                    "app_core_vulkan",
                },
            },
            app_core_d3d12 = {
                location = "libraries/app_core",
                includedirs = {
                    "%{g_wkslight.librariesdir}/app_core/include",
                },
                links = {
                    "app_core_d3d12",
                },
            },
            app_core_vulkan = {
                location = "libraries/app_core",
                includedirs = {
                    "%{g_wkslight.librariesdir}/app_core/include",
                },
                links = {
                    "app_core_vulkan",
                },
            },
            bar = {
                enabled = function()
                    return true
                end,
                location = "libraries/bar",
                includedirs = {
                    "%{g_wkslight.librariesdir}/bar/include",
                },
                additionalincludedirs = function()
                    return {
                        --"%{g_wkslight.librariesdir}/bar/%{cfg.system}/" .. _OPTIONS["target_platform"] .. "/include",
                    }
                end,
                libdirs = {
                    --"%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
                    --"%{g_wkslight.librariesdir}/bar/lib/%{cfg.system}/%{cfg.platform:gsub('x86', 'Win32'):gsub('x64', 'Win64')}",
                },
                additionallibdirs = function()
                    return {
                        --"%{g_wkslight.librariesdir}/bar/%{cfg.system}/" .. _OPTIONS["target_platform"] .. "/%{cfg.buildcfg}/lib",
                        --path.join("%{g_wkslight.librariesdir}/bar/%{cfg.system}/", _OPTIONS["target_platform"], "lib"),
                        --path.join(g_wkslight.librariesdir, "bar", "%{cfg.system}", _OPTIONS["target_platform"], "lib"),
                    }
                end,
                defines = {
                    --"BAR_DLL",
                },
                links = {
                    "bar",
                    --"bar-s%{cfg.buildcfg:gsub('[Dd]ebug', '-d'):gsub('[Rr]elease', '')}",
                },
                debugenvs = {
                    "FOO=foo",
                    "BAR=bar",
                },
                vslocaldebugenvs = {
                    --"%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
                },
            },
            ["baz-qux"] = {
                location = "libraries/baz-qux",
                includedirs = {
                    "%{g_wkslight.librariesdir}/baz-qux/include",
                },
                links = {
                    "baz-qux",
                },
            },
            Catch2 = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/Catch2/single_include",
                },
                defines = {
                    "CATCH_CONFIG_MAIN",
                },
            },
            FastNoise2 = {
                enabled = function()
                    if _OPTIONS["target_platform"] == "web" then
                        return false
                    end
                    return true
                end,
                location = "libraries/FastNoise2",
                includedirs = {
                    "%{g_wkslight.librariesdir}/FastNoise2/include",
                },
                defines = {
                    "FASTNOISE_STATIC_LIB",
                },
                links = {
                    "FastNoise2",
                },
            },
            foo = {
                location = "libraries/foo",
                includedirs = {
                    "%{g_wkslight.librariesdir}/foo/include",
                },
                defines = {
                    "FOO_DLL",
                },
                links = {
                    "foo",
                },
            },
            headeronly = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/headeronly",
                },
            },
            imgui = {
                location = "libraries/imgui",
                includedirs = {
                    "%{g_wkslight.librariesdir}/imgui",
                },
                links = {
                    "imgui",
                },
            },
            lua = {
                location = "libraries/lua",
                includedirs = {
                    "%{g_wkslight.librariesdir}/lua/src",
                },
                links = {
                    "lua",
                },
            },
            sdl2 = {
                enabled = function()
                    if _OPTIONS["target_platform"] == "android" or _OPTIONS["target_platform"] == "web" then
                        return false
                    end
                    return true
                end,
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/sdl2/include",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2-2.32.4/include",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_image-2.8.8/include",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_mixer-2.8.1/include",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_net-2.2.0/include",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_ttf-2.24.0/include",
                },
                libdirs = {
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2-2.32.4/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_image-2.8.8/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_mixer-2.8.1/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_net-2.2.0/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_ttf-2.24.0/lib/x64",
                },
                links = {
                    "SDL2",
                    "SDL2main",
                    "SDL2_image",
                    "SDL2_mixer",
                    "SDL2_net",
                    "SDL2_ttf",
                },
                vslocaldebugenvs = {
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2-2.32.4/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_image-2.8.8/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_mixer-2.8.1/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_net-2.2.0/lib/x64",
                    "%{g_wkslight.workspacedir}/../bin/opt/SDL2_ttf-2.24.0/lib/x64",
                },
            },
            sol2 = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/sol2/include",
                },
            },
            spdlog = {
                location = "libraries/spdlog",
                includedirs = {
                    "%{g_wkslight.librariesdir}/spdlog/include",
                },
                defines = {
                    "SPDLOG_COMPILED_LIB",
                    "SPDLOG_NO_EXCEPTIONS",
                },
                links = {
                    "spdlog",
                },
            },
            spdlog_headeronly = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/spdlog/include",
                },
            },
            XMath = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/XMath/Inc",
                },
            },
        },
    },
}
g_wkslight.extras = {
    android = {
        androidabis = {
            --"armeabi",
            --"armeabi-v7a",
            "arm64-v8a",
            --"x86",
            --"x86_64",
        },
        androidsdkversion = "33",
        androidminsdkversion = "24",
        androidndkpath = os.getenv("ANDROID_NDK_ROOT"),
        gradleversion = "com.android.tools.build:gradle:7.0.0",
        gradlewrapper = {
            "distributionUrl=https://services.gradle.org/distributions/gradle-7.5.1-bin.zip",
        },
        androidrepositories = {
            --"jcenter()",
            --"maven { url 'http://maven.gameanalytics.com/release' }",
        },
        androidnamespace = "premake.andoid.studio",
        assetpacks = {
            ["pack"] = "install-time",
        },
    },
    wasm = {
        --em_config = "~/emsdk-tmp/dot-emscripten-dup",
        libs = {
            "idbfs.js",
            "websocket.js",
        },
        flags = (
            g_wkslight.EWasmFlag.USE_ZLIB |
            g_wkslight.EWasmFlag.USE_SDL2 |
            g_wkslight.EWasmFlag.USE_SDL_IMAGE |
            g_wkslight.EWasmFlag.USE_SDL_MIXER |
            --g_wkslight.EWasmFlag.USE_SDL_NET |
            g_wkslight.EWasmFlag.USE_SDL_TTF |
            g_wkslight.EWasmFlag.USE_WEBGL2 |
            g_wkslight.EWasmFlag.EXPLICIT_SWAP_CONTROL |
            --g_wkslight.EWasmFlag.ASYNCIFY |
            g_wkslight.EWasmFlag.LINK_OPENAL |
            g_wkslight.EWasmFlag.NONE
        ),
        exported_runtime_methods = {
            "ccall",
            "cwrap",
        },
        exported_functions = {
            "_main",
            --"_malloc",
            --"_free",
        },
        asyncify_whitelist = {
            --"main",
        },
        image_formats = {
            "bmp",
            "jpg",
            "png",
        },
        preload_files = {
            "%{cfg.debugdir}/assets@assets",
        },
        embed_files = {
            --"%{cfg.debugdir}/assets@/",
        },
        --shell_file = "%{cfg.debugdir}/meta/web/shell_minimal.html",
        output_file = "%{cfg.targetdir}/../../index.html",
    },
}