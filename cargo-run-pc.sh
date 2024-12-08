cp -rv bin/x64/Release/*.so app-rs/target/release
cp -rv app/assets app-rs/target/release

pushd app-rs

cargo build --release

pushd target/release
./app-rs
popd

popd