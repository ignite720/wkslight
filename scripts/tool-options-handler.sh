declare -A OPTIONS
for arg in "$@"; do
    OPTIONS["${arg%=*}"]="${arg#*=}"
done