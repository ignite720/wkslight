APP_RS_ANDROID_DIR=app-rs-android
BIN_ANDROID_CARGO_APK_DIR=bin/android-cargo-apk

pushd ${APP_RS_ANDROID_DIR}

THE_SO_DIR=$(find ../build/app/app/.cxx/Debug -type d -path "*/arm64-v8a" | head -n 1)
echo "THE_SO_DIR=${THE_SO_DIR}"
ls -lah $(realpath ${THE_SO_DIR})
RUSTFLAGS="-L ${THE_SO_DIR} -lc++_shared -lapp_core_d3d12 -lapp_core_vulkan -lfoo" cargo apk build --profile android-cargo-apk

popd

mkdir -p ${BIN_ANDROID_CARGO_APK_DIR}
cp -fv ${APP_RS_ANDROID_DIR}/target/android-cargo-apk/apk/app.apk ${BIN_ANDROID_CARGO_APK_DIR}