if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

rm -fr .git

rm -fv .gitmodules
rm -fv LICENSE

rm -fr libraries/headeronly/simplerand
rm -fr libraries/lua
rm -fr libraries/XMath

rm -fr premake5-modules