set +e
emcc --generate-config $HOME/.emscripten
stat $HOME/.emscripten

mkdir -p $HOME/emsdk-tmp
cp -fv $HOME/.emscripten $HOME/emsdk-tmp/dot-emscripten-dup
set -e

cp -fv $(realpath $(dirname $(realpath $(which emcc)))/../../.emscripten) $HOME/emsdk-tmp/dot-emscripten-dup
cat $HOME/emsdk-tmp/dot-emscripten-dup