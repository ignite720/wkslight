if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

pushd build
make config=release_x64
popd