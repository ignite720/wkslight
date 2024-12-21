source scripts/tool-path-checker.sh
tool_path_checker

rm -frv bin/target/wasm
sed -i '/<\/head>/i <link rel="icon" href="favicon.ico">' bin/target/index.html