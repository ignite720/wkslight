pushd build/
make config=release_wasm
popd

cp -fv app/meta/web/favicon.ico bin/
echo -e '{ "name": "Alexander", "age": 26, "address": { "city": "Wonderland", "zipcode": "54321" } }' > bin/example.json