#!/bin/bash

# deprecated, this is just for prebuilt.
#cp --update -v libraries/bar/lib/linux/x64/Release/libbar.so bin/x64/Release

cp -r app/assets bin/x64/Release

pushd bin/x64/Release
./app
popd