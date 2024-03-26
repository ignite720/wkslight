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
		--"bar",
		--"foo",
		"linmath",
		"lua",
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
			"bar",
			"foobar",
			"foo",
			"lua",
		})
		androidkeystorefile("../../../../.android/wkslight.keystore")
		androidstorepassword("android")
		androidkeyalias("wkslightkey")
		androidkeypassword("android")
		apkoutputpath("../../../../../../../bin/apk-")
		assetdirs({
			"assets",
		})
		-- [[
		--[[fix uwp dll start]]--
		links({
			"bar",
			"foo",
		})
		--[[fix uwp dll end]]--
		-- ]]
	filter("options:target_platform=uwp")
		files({
			"Package.appxmanifest",
		})
		-- [[
		--[[fix uwp dll start]]--
		libdirs({
			"%{g_wkslight.targetdir}",
		})
		links({
			"app_core.lib",
		})
		--[[fix uwp dll end]]--
		-- ]]
	filter({ "options:target_platform=uwp", "files:assets/*.png" })
		deploy("true")
	filter("platforms:wasm")
		--[[
		--[[fix web so start]]--
		links({
			"foobar",
			"foo",
		})
		--[[fix web so end]]--
		--]]
		g_wkslight.wasmlinkoptions(g_wkslight.extras.wasm)