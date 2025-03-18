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
    --yield(0.5)
    coroutine.yield()

    print("Coroutine resumed2")
end)

print("1-3, <LUA>:", _VERSION)
print(string.upper("1-4, <LUA>: world"))
print("1-5, <LUA>:", os.date("%Y-%m-%d %H:%M:%S"), os.time())
print("1-6, <LUA>:", math.pi, math.sqrt(16), math.sin(math.pi / 2))

local t = { 1, 2, 3 }
table.insert(t, 4)
print("1-7, <LUA>:", table.concat(t, ", "))

io.write(string.format("1-8, <LUA>: %d, %d\n\n", 1000, 2000))

Foo.print(table.pack(coroutine.resume(co)), coroutine.status(co))
print("")

Bar.print(table.pack(coroutine.resume(co)), coroutine.status(co))
print("")

coroutine.resume(co)
print("2, <LUA>:")
print("")