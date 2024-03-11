cp -rv bin/x64/Release/* app-rs/target/release

pushd app-rs
cargo run --release
popd