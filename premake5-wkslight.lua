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
				location = "libraries/bar",
				includedirs = {
					"%{wks.location}/../libraries/bar/include",
				},
				links = {
					"bar",
				},
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
			TGUI = {
				location = nil,
				includedirs = {
					"%{wks.location}/../libraries/TGUI/include",
				},
				libdirs = {
					"%{wks.location}/../libraries/TGUI/lib/%{cfg.buildcfg}",
				},
				links = {
					"tgui-s%{cfg.buildcfg:gsub('[Dd]ebug', '-d'):gsub('[Rr]elease', '')}",
				},
				defines = {
					"TGUI_STATIC",
				},
				debugenvs = {
					"VAR1=value1",
					"VAR2=value2",
				},
				localdebugenv = "%{wks.location}/../libraries/TGUI/bin",
			},
		},
	},
}
g_wkslight.extras = {
	foobar = 0.0,
}