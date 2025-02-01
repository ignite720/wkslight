require("assets.scripts.foobar")

function hi(go)
    print("3-1, <LUA>: hi " .. go:get_name())
end

function hi2(go)
    go:set_name("Emily")
    print("3-2, <LUA>: hi2 " .. go:get_name())
end

local co = coroutine.create(function()
    print("Coroutine running")
    coroutine.yield()
    print("Coroutine resumed")
end)

print(string.upper("2, <LUA>: world"))
print(os.date("%Y-%m-%d %H:%M:%S"), os.time())
print(math.pi, math.sqrt(16), math.sin(math.pi / 2))

local t = { 1, 2, 3 }
table.insert(t, 4)
print(table.concat(t, ", "))

io.write(string.format("%d, %d\n\n", 1000, 2000))

coroutine.resume(co)
Foo.print()
print("")

coroutine.resume(co)
Bar.print()
print("")