Utils = {}

function Utils.print_debug_info()
    local dinfo = debug.getinfo(2, "Sln")
    print(string.format(
        "%s:%d, %s(%s/%s), line: [%d, %d]",
        dinfo.source,
        dinfo.currentline,
        dinfo.name,
        dinfo.namewhat,
        dinfo.what,
        dinfo.linedefined,
        dinfo.lastlinedefined
    ))
end