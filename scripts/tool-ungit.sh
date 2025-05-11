if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

rm -fr .git

rm -fv .gitmodules
rm -fv LICENSE

rm -fr libraries/FastNoise2
rm -fr libraries/headeronly/mathx
rm -fr libraries/headeronly/wkstk
rm -fr libraries/imgui
rm -fr libraries/lua
rm -fr libraries/spdlog
rm -fr libraries/XMath

rm -fr premake5-modules