project("app_core")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("SharedLib")
	language("C++")
	files({
		"include/**.h",
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
		"foobar",
		"foo",
		"headeronly",
		"linmath",
		"lua",
		"sol2",
	})
	filter("options:target_platform=android")
		androidprojectdependencies({
			"bar",
			"foo",
			"lua",
		})
	filter("options:target_platform=uwp")
		--[[
		--[[fix uwp dll start]]--
		libdirs({
			"%{g_wkslight.targetdir}",
		})
		links({
			"bar.lib",
			"foo.lib",
		})
		--[[fix uwp dll end]]--
		--]]
	filter("options:target_platform=android or options:target_platform=web")
		kind("StaticLib")