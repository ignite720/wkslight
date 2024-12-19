[[ "$(pwd)" != "$(git rev-parse --show-toplevel 2>/dev/null)" ]] && { return 1; }

pushd build

#gradlew tasks --all

#gradle :bar:assembleDebug
#gradle :foo:assembleDebug
#gradle :lua:assembleDebug
#gradle :app_core:assembleDebug
#gradle :app:assembleDebug

gradle assembleDebug
#gradle assembleRelease

popd