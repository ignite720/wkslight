[[ "$(pwd)" != "$(git rev-parse --show-toplevel)" ]] && { return 1; }

pushd build
make config=release_x64
popd