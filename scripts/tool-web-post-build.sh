rm -frv bin/target/wasm
sed -i '/<\/head>/i <link rel="icon" href="favicon.ico">' bin/target/index.html