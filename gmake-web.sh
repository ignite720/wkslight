set -e

pushd build
make config=release_wasm
popd

emrun --no_browser --port=8000 ./bin/