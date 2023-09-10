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
				localdebugenv = "PATH=%{g_wkslight.librariesdir}/bar/lib/%{g_wkslight.targettriple}",
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
	foobar = 0.0,
}