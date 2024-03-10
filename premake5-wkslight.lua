g_wkslight = require("premake5-modules/wkslight")
g_wkslight.workspace = {
	name = "workspace_name",
	startproject = "",
	cppdialect = "C++20",
	projects = {
		"app",
	},
	libraries = {
		name = "libraries",
		projects = {
			--[[
			bar = {
				location = nil,
				includedirs = {
					"%{g_wkslight.librariesdir}/bar/include",
				},
				libdirs = {
					"%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
					--"%{g_wkslight.librariesdir}/bar/lib/%{cfg.platform:gsub('x86', 'Win32'):gsub('x64', 'Win64')}",
				},
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
			]]--
			bar = {
				location = "libraries/bar",
				includedirs = {
					"%{g_wkslight.librariesdir}/bar/include",
				},
				links = {
					"bar",
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
			},
			headeronly = {
				location = nil,
				includedirs = {
					"%{g_wkslight.librariesdir}/headeronly",
				},
			},
			linmath = {
				location = nil,
				includedirs = {
					"%{g_wkslight.librariesdir}/linmath.h",
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
		androiddependencies = {
			"com.android.support:support-v4:27.1.0",
		},
		androidsdkversion = "33",
		androidminsdkversion = "24",
		gradleversion = "com.android.tools.build:gradle:7.2",
		gradlewrapper = {
			"distributionUrl=https://services.gradle.org/distributions/gradle-7.5.1-bin.zip",
		},
	},
	wasm = {
		flags = (
			g_wkslight.EWasmFlag.USE_ZLIB |
			g_wkslight.EWasmFlag.USE_SDL2 |
			g_wkslight.EWasmFlag.USE_SDL_IMAGE |
			g_wkslight.EWasmFlag.USE_SDL_MIXER |
			--g_wkslight.EWasmFlag.USE_SDL_NET |
			--g_wkslight.EWasmFlag.USE_SDL_TTF |
			g_wkslight.EWasmFlag.USE_WEBGL2 |
			g_wkslight.EWasmFlag.EXPLICIT_SWAP_CONTROL |
			--g_wkslight.EWasmFlag.ASYNCIFY |
			g_wkslight.EWasmFlag.LINK_OPENAL |
			g_wkslight.EWasmFlag.NONE
		),
		libs = {
			"idbfs.js",
			"websocket.js",
		},
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
			"%{cfg.debugdir}/assets",
		},
		embed_files = {
			--"%{cfg.debugdir}/assets",
		},
		--shell_file = "%{cfg.debugdir}/platform/wasm/shell_minimal.html",
		output_file = "%{cfg.targetdir}/../../index.html",
	},
}