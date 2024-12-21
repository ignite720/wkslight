source scripts/tool-path-checker.sh
tool_path_checker

# deprecated: this is just for prebuilt.
#cp --update -v libraries/bar/lib/linux/x64/Release/libbar.so bin/target/x64/Release

# deprecated: `--pc_deploy_assets` accomplishes the same job.
#cp -frv app/assets bin/target/x64/Release/assets

pushd bin/target/x64/Release
./app
popd