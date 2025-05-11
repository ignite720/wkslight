pushd app-rs-android

THE_SO_DIR=$(find ../build/app/app/.cxx/Debug -type d -path "*/arm64-v8a" | head -n 1)
echo "THE_SO_DIR=${THE_SO_DIR}"
ls -lah $(realpath ${THE_SO_DIR})
RUSTFLAGS="-L ${THE_SO_DIR} -lc++_shared -lapp_core_d3d12 -lapp_core_vulkan -lfoo" cargo apk build --profile android-cargo-apk

popd

mkdir -p bin/android-cargo-apk
cp -fv app-rs-android/target/android-cargo-apk/apk/app.apk bin/android-cargo-apk