g_wkslight = require("premake5-modules/wkslight")
g_wkslight.workspace = {
	name = "wkslight",
	startproject = "",
	cppdialect = "C++20",
	libraries = {
		name = "libraries",
		projects = {
			foo = {
				location = "libraries/foo",
				includedirs = {
					"%{wks.location}/../libraries/foo/include",
				},
			},
			bar = {
				location = "libraries/bar",
				includedirs = {
					"%{wks.location}/../libraries/bar/include",
				},
			},
		},
	},
	projects = {
		"app",
	},
}
g_wkslight.extras = {
	foobar = 0.0,
}