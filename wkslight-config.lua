g_wkslight.workspace = {
    name = "wkslight",
    startproject = "app",
    cppdialect = "C++20",
    projects = {
        -- Sort by dependencies
        "foobar",
        "app",
    },
    libraries = {
        group = "libraries",
        projects = {
            -- Sort alphabetically
            --[[
            bar = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/bar/include",
                },
                additionalincludedirs = function()
                    return {
                        "%{wks.librariesdir}/bar/%{cfg.system}/" .. _OPTIONS["target_platform"] .. "/include",
                    }
                end,
                libdirs = {
                    "%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
                    --"%{g_wkslight.librariesdir}/bar/lib/%{cfg.system}/%{cfg.platform:gsub('x86', 'Win32'):gsub('x64', 'Win64')}",
                },
                additionallibdirs = function()
                    return {
                        "%{wks.librariesdir}/bar/%{cfg.system}/" .. _OPTIONS["target_platform"] .. "/lib",
                    }
                end,
                links = {
                    "bar",
                    --"bar-s%{cfg.buildcfg:gsub('[Dd]ebug', '-d'):gsub('[Rr]elease', '')}",
                },
                defines = {
                    "BAR_CONFIG1",
                },
                debugenvs = {
                    "VAR1=value1",
                    "VAR2=value2",
                },
                vslocaldebugenv = "PATH=%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
            },
            ["foo_bar"] = {
                location = "libraries/foo_bar",
                includedirs = {
                    "%{g_wkslight.librariesdir}/foo_bar/include",
                },
                links = {
                    "foo_bar",
                },
            },
            --]]
            app_core = {
                location = "libraries/app_core",
                includedirs = {
                    "%{g_wkslight.librariesdir}/app_core/include",
                },
                libdirs = {
                    "%{g_wkslight.targetdir}",
                },
                links = {
                    "app_core",
                    "app_core_d3d12",
                    "app_core_vulkan",
                },
                defines = {
                    "APP_CORE_DLL",
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
                location = "libraries/bar",
                includedirs = {
                    "%{g_wkslight.librariesdir}/bar/include",
                },
                links = {
                    "bar",
                },
                defines = {
                    --"BAR_DLL",
                },
            },
            foo = {
                location = "libraries/foo",
                includedirs = {
                    "%{g_wkslight.librariesdir}/foo/include",
                },
                links = {
                    "foo",
                },
                defines = {
                    "FOO_DLL",
                },
            },
            headeronly = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/headeronly",
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
            sol2 = {
                location = nil,
                includedirs = {
                    "%{g_wkslight.librariesdir}/sol2/include",
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