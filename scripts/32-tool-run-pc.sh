#!/bin/bash
[[ "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]] && { return 1; }

# deprecated, this is just for prebuilt.
#cp --update -v libraries/bar/lib/linux/x64/Release/libbar.so bin/target/x64/Release

cp -rv app/assets bin/target/x64/Release

pushd bin/target/x64/Release
./app
popd