BUILD_DIR="build-cmake"
SRC_DIR=build

cmake -B ${BUILD_DIR} -S ${SRC_DIR}
cmake --build ${BUILD_DIR} --config Release