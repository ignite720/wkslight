pushd build
make -j$(($(nproc)/2)) config=release_x64
popd