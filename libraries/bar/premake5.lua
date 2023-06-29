project("bar")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("SharedLib")
	language("C++")
	files({
		"include/**.h",
		"src/**.cpp",
	})
	includedirs({
		g_wkslight.workspace.libraries.projects.bar.includedirs,
	})
	defines({
		"BAR_BUILD_DLL",
	})