g_wkslight = require("premake5-modules/wkslight")
g_wkslight.workspace = {
	name = "wkslight",
	startproject = "",
	cppdialect = "C++20",
	projects = {
		"app",
	},
	libraries = {
		name = "libraries",
		projects = {
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
			"armeabi-v7a",
			--"arm64-v8a",
			--"x86",
			--"x86_64",
		},
		androidndkpath = "ndk/path/???",
		androiddependencies = {
			"com.android.support:support-v4:27.1.0",
		},
		androidsdkversion = "28",
		androidsdkversion = "28",
		gradleversion = "com.android.tools.build:gradle:7.3.1",
		gradlewrapper = {
			"distributionUrl=https://services.gradle.org/distributions/gradle-7.5.1-bin.zip",
		},
	},
	wasm = {
		libs = {
			"idbfs.js",
			"websocket.js",
		},
		extra_exported_runtime_methods = {
			--"ccall",
			--"cwrap",
		},
		exported_functions = {
			--"_main",
		},
		use_pthreads = false,
		asyncify = true,
		asyncify_whitelist = {
			--"main",
		},
		image_formats = {
			--"bmp",
			--"jpg",
			"png",
		},
		preload_files = {
			"assets",
			"res",
		},
		shell_file = "%{cfg.debugdir}/platform/wasm/shell.html",
		output_file = "%{cfg.targetdir}/../../index.html",
	},
}