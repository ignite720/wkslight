APP_RS_DIR=app-rs
APP_RS_TARGET_RELEASE_DIR=${APP_RS_DIR}/target/release

pushd ${APP_RS_DIR}
cargo clean
popd

mkdir -p ${APP_RS_TARGET_RELEASE_DIR}
cp -rv bin/target/x64/Release/lib*.* $APP_RS_TARGET_RELEASE_DIR
cp -rv app/assets ${APP_RS_DIR}

pushd ${APP_RS_DIR}
cargo run -v --release $1
popd