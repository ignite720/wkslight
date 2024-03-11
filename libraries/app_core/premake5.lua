project("app_core")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("SharedLib")
	language("C++")
	files({
		"src/**.cpp",
	})
	includedirs({
		"src",
	})
	g_wkslight.uselibs({
		"bar",
		"foo",
		"headeronly",
		"linmath",
	})
	filter("options:target_platform=android")
		androidprojectdependencies({
			"bar",
			"foo",
		})
	filter("options:target_platform=uwp")
		---[[fix uwp start]]---
		libdirs({
			"%{g_wkslight.targetdir}",
		})
		links({
			"bar.lib",
			"foo.lib",
		})
		---[[fix uwp end]]---