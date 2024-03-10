require("premake5-modules/android-studio/android_studio")
require("premake5-modules/emscripten")
require("premake5-modules/vspropertysheets")
require("premake5-modules/winrt")
require("premake5-wkslight")
newoption({
	trigger = "android",
	description = "Generate Android projects",
})
newoption({
	trigger = "uwp",
	description = "Generate Universal Windows Platform projects",
})
newoption({
	trigger = "web",
	description = "Generate Web projects",
})
workspace(g_wkslight.workspace.name)
	location(path.getbasename(g_wkslight.workspacedir))
	platforms({ "x86", "x64" })
	configurations({ "Debug", "Release" })
	characterset("Default")
	cppdialect(g_wkslight.workspace.cppdialect)
	floatingpoint("Default")
	rtti("Default")
	exceptionhandling("Default")
	defines({
		"__STDC_LIMIT_MACROS",
		"__STDC_FORMAT_MACROS",
		"__STDC_CONSTANT_MACROS",
	})
	filter("options:android")
		androidabis(g_wkslight.extras.android.androidabis)
		androidsdkversion(g_wkslight.extras.android.androidsdkversion)
		androidminsdkversion(g_wkslight.extras.android.androidminsdkversion)
		gradleversion(g_wkslight.extras.android.gradleversion)
		--gradlewrapper(g_wkslight.extras.android.gradlewrapper)
		androidrepositories(g_wkslight.extras.android.androidrepositories)
		androidappid(g_wkslight.extras.android.androidappid)
	filter("options:uwp")
		cppdialect("C++17")
		system("windowsuniversal")
		defaultlanguage("en-US")
		generatewinmd("false")
		consumewinrtextension2("false")
	filter("options:web")
		platforms({ "wasm" })
		toolset("emcc")
		linkoptions({
			--"-sUSE_PTHREADS=1",
			--"-sPTHREAD_POOL_SIZE=8",
		})
	filter("system:windows")
		systemversion("latest")
	filter("system:linux")
		pic("On")
	filter("action:vs*")
		startproject(g_wkslight.workspace.startproject)
		staticruntime("Off")
		characterset("MBCS")
		flags({ "MultiProcessorCompile" })
		defines({
			"_CRT_SECURE_NO_WARNINGS",
			"_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS",
			"_SILENCE_ALL_CXX20_DEPRECATION_WARNINGS",
			"_HAS_STD_BYTE=0",
		})
		buildoptions({
			"/utf-8",
			"/Zc:char8_t-",
		})
	filter({ "action:gmake*", "system:not linux", "kind:*App or StaticLib" })
		buildoptions({ "-static" })
	filter("configurations:Debug")
		defines({ "_DEBUG" })
		symbols("On")
		optimize("Off")
	filter("configurations:Release")
		defines({ "NDEBUG" })
		symbols("Off")
		optimize("Speed")
group(g_wkslight.workspace.libraries.name)
	for k, v in pairs(g_wkslight.workspace.libraries.projects) do
		if v.location ~= nil then
			include(v.location)
		end
	end
group("")
	for i, v in ipairs(g_wkslight.workspace.projects) do
		include(v)
	end