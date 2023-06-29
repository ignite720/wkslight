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
		g_wkslight.workspace.libraries.projects.foo.includedirs,
		g_wkslight.workspace.libraries.projects.bar.includedirs,
	})
	links({
		"foo",
		"bar",
	})