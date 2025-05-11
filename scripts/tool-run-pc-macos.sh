pushd bin/target/x64/Release
ls -lah
DYLD_LIBRARY_PATH=. ./app $1
popd