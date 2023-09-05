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
			},
			foo = {
				location = "libraries/foo",
				includedirs = {
					"%{wks.location}/../libraries/foo/include",
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
				bindir = "%{wks.location}/../libraries/TGUI/bin",
			},
		},
	},
}
g_wkslight.extras = {
	foobar = 0.0,
}