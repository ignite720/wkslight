source scripts/tool-path-checker.sh
tool_path_checker

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