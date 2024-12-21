source scripts/tool-path-checker.sh
tool_path_checker

pushd build

gradle wrapper
#./gradlew build --info
./gradlew assembleDebug

popd