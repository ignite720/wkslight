project("app")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	debugdir("")
	debugargs({ "" })
	kind("ConsoleApp")
	language("C++")
	files({
		"src/**.h",
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
	filter("options:android")
		androidprojectdependencies({
			"bar",
			"foo",
		})
	filter("options:uwp")
		files({
			"Package.appxmanifest",
		})
		---[[fix uwp start]]---
		libdirs({
			"%{g_wkslight.targetdir}",
		})
		links({
			"bar.lib",
			"foo.lib",
		})
		---[[fix uwp end]]---
	filter("platforms:wasm")
		g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)