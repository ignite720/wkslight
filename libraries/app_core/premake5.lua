project("app_core")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("SharedLib")
	language("C++")
	files({
		"src/**.h",
		"src/**.cpp",
	})
	includedirs({
		g_wkslight.workspace.libraries.projects.app_core.includedirs,
	})
	defines({
		"APP_CORE_BUILD_DLL",
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