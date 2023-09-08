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
					"%{wks.location}/../libraries/bar/include",
				},
				libdirs = {
					"%{wks.location}/../libraries/bar/lib/%{g_wkslight.targettriple}",
				},
				links = {
					"bar",
					--"bar-s%{cfg.buildcfg:gsub('[Dd]ebug', '-d'):gsub('[Rr]elease', '')}",
				},
				defines = {
					"TGUI_STATIC",
				},
				debugenvs = {
					"VAR1=value1",
					"VAR2=value2",
				},
				localdebugenv = "PATH=%{wks.location}/../libraries/bar/lib/%{g_wkslight.targettriple}",
			},
			foo = {
				location = "libraries/foo",
				includedirs = {
					"%{wks.location}/../libraries/foo/include",
				},
				links = {
					"foo",
				},
			},
			linmath = {
				location = nil,
				includedirs = {
					"%{wks.location}/../libraries/linmath.h",
				},
			},
		},
	},
}
g_wkslight.extras = {
	foobar = 0.0,
}