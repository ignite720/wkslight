if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

pushd app-rs-android
RUSTFLAGS="${RUSTFLAGS} -lc++_shared -lapp_core_d3d12 -lapp_core_vulkan -lbar -lfoo -llua" cargo apk build --profile android-cargo-apk
popd

mkdir -p bin/android-cargo-apk
cp -fv app-rs-android/target/android-cargo-apk/apk/app.apk bin/android-cargo-apk