source scripts/tool-path-checker.sh
tool_path_checker

pushd build
make config=release_wasm
popd

cp -fv app/meta/web/favicon.ico bin/target
echo -e '{ "name": "Alexander", "age": 26, "address": { "city": "Wonderland", "zipcode": "54321" } }' > bin/target/example.json