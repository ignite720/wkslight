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
		"src-java/**.*",
		"assets/**.*",
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
		androiddependencies({
			"com.android.support:support-v4:27.1.0",
		})
		androidprojectdependencies({
			"bar",
			"foo",
		})
		androidkeystorefile("../../../.android/debug.keystore")
		androidstorepassword("android")
		androidkeyalias("androiddebugkey")
		androidkeypassword("android")
		--androidversioncode("2")
		--androidversionname("1.0")
		assetdirs({
			"assets",
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
	filter({ "options:uwp", "files:assets/*.png" })
		deploy("true")
	filter("platforms:wasm")
		g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)