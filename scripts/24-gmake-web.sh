[[ "$(git rev-parse --is-inside-work-tree 2>/dev/null || echo false)" == true && "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]] && { return 1; }

pushd build
make config=release_wasm
popd

cp -fv app/meta/web/favicon.ico bin/target
echo -e '{ "name": "Alexander", "age": 26, "address": { "city": "Wonderland", "zipcode": "54321" } }' > bin/target/example.json