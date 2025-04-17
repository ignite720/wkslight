tree -d -n -I "premake5-modules|scripts" | tee bin/tree-dirs.txt
tree --dirsfirst --gitignore -a -f -n -I .git/ -o bin/tree.txt