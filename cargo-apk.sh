pushd app-rs-android
RUSTFLAGS="${RUSTFLAGS} -lc++_shared -lbar -lfoo -llua" cargo apk build --profile android-apk
popd

mkdir -p bin/android-apk
cp -fv app-rs-android/target/android-apk/apk/app.apk bin/android-apk