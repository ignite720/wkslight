APP_RS_DIR=app-rs
APP_RS_TARGET_RELEASE_DIR=${APP_RS_DIR}/target/release

pushd app-rs
cargo clean
popd

mkdir -p ${APP_RS_TARGET_RELEASE_DIR}
cp -rv bin/target/x64/Release/lib*.* $APP_RS_TARGET_RELEASE_DIR
cp -rv app/assets ${APP_RS_DIR}

pushd app-rs
cargo run -v --release $1
popd