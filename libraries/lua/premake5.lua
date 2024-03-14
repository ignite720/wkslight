project("lua")
	location(g_wkslight.workspacedir .. "/%{prj.name}")
	targetdir(g_wkslight.targetdir)
	kind("StaticLib")
	language("C")
	files({
		"src/**.c",
	})
	removefiles({
		"src/luac.c",
	})
	includedirs({
		g_wkslight.workspace.libraries.projects.lua.includedirs,
	})
	--filter("files:src/luac.c")
	--flags({ "ExcludeFromBuild" })