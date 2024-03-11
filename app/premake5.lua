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
		"app_core",
		"bar",
		"foo",
		"linmath",
	})
	filter("options:target_platform=android")
		links({
			"log",
		})
		androiddependencies({
			"com.android.support:support-v4:27.1.0",
		})
		androidprojectdependencies({
			"app_core",
		})
		androidkeystorefile("../../../.android/debug.keystore")
		androidstorepassword("android")
		androidkeyalias("androiddebugkey")
		androidkeypassword("android")
		apkoutputpath("../../../../../../../bin/apk-")
		assetdirs({
			"assets",
		})
	filter("options:target_platform=uwp")
		files({
			"Package.appxmanifest",
		})
		---[[fix uwp start]]---
		libdirs({
			"%{g_wkslight.targetdir}",
		})
		links({
			"app_core.lib",
		})
		---[[fix uwp end]]---
	filter({ "options:target_platform=uwp", "files:assets/*.png" })
		deploy("true")
	filter("platforms:wasm")
		g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)