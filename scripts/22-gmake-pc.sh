[[ "$(git rev-parse --is-inside-work-tree 2>/dev/null || echo false)" == true && "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]] && { return 1; }

pushd build
make config=release_x64
popd