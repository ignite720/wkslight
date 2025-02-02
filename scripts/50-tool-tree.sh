tree --dirsfirst --gitignore -d -f -n -I "premake5-modules|scripts" -o bin/tree-dirs.txt
tree --dirsfirst --gitignore -a -f -n -I .git/ -o bin/tree.txt