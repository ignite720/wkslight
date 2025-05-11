# deprecated: this is just for prebuilt.
#cp --update -v libraries/bar/lib/linux/x64/Release/libbar.so bin/target/x64/Release

# deprecated: use `--pc_deploy_assets` instead.
#cp -frv app/assets bin/target/x64/Release/assets

pushd bin/target/x64/Release
ls -lah
LD_LIBRARY_PATH=. ./app $1
popd