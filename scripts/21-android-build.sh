if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

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