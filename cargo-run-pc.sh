cp -rv bin/x64/Release/* app-rs/target/release

pushd app-rs
cargo build --release

pushd target/release/
./app
popd

popd