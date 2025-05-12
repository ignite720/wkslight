source scripts/tool-option-handler.sh

#premake5 gmakelegacy --asan --avx2 --pc_deploy_assets ${OPTION_CI}
premake5 gmake --asan --pc_deploy_assets ${OPTION_CI}