source scripts/tool-options-handler.sh

#premake5 gmakelegacy --asan --avx2 --pc_deploy_assets ${OPTIONS["CI"]}
premake5 gmake --asan --pc_deploy_assets ${OPTIONS["CI"]}