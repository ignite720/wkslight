if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

pushd build

gradle wrapper
#./gradlew build --info
./gradlew assembleDebug

popd