#!/bin/bash

cp --update -v libraries/bar/lib/linux/x64/Release/libbar.so bin/x64/Release

pushd bin/x64/Release
./app
popd