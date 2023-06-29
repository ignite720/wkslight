project("foo")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("SharedLib")
	language("C++")
	files({
		"include/**.h",
		"src/**.cpp",
	})
	includedirs({
		g_wkslight.workspace.libraries.projects.foo.includedirs,
	})
	defines({
		"FOO_BUILD_DLL",
	})