pushd build
make config=release_wasm app
popd

emrun --no_browser --port=8000 ./bin/