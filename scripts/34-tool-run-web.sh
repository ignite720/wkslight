if [ ! -f "scripts/tool-path-checker.sh" ]; then return 1; fi

EMSDK_TMP_CACHE_SYSROOT_INC_PATH=~/emsdk-tmp/cache/sysroot/include
echo $EMSDK_TMP_CACHE_SYSROOT_INC_PATH

#export C_INCLUDE_PATH=${EMSDK_TMP_CACHE_SYSROOT_INC_PATH}
#export CPLUS_INCLUDE_PATH=${EMSDK_TMP_CACHE_SYSROOT_INC_PATH}
source scripts/24-gmake-web.sh

#emrun --no_browser --port=8000 ./bin/target
scripts/tool-run-web-server bin/target