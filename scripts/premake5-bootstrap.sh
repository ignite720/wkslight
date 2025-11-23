OPT_DIRNAME=opt
SHELLRC_PATH=$HOME/.bashrc
SED_PREMAKE5_BRE='/^export PATH=.*premake5.*/'
SED_PREMAKE5_PREVIEW_CMD='sed -n "${SED_PREMAKE5_BRE}p" "${SHELLRC_PATH}"'
SED_PREMAKE5_DELETE_CMD='sed -i "${SED_PREMAKE5_BRE}d" "${SHELLRC_PATH}"'

PREMAKE5=premake5
PREMAKE5_OS=linux
PREMAKE5_VERSION=5.0.0-beta7
PREMAKE5_DOWNLOAD_FILENAME=premake-${PREMAKE5_VERSION}-${PREMAKE5_OS}.tar.gz
PREMAKE5_DOWNLOAD_URL=https://github.com/premake/premake-core/releases/download/v${PREMAKE5_VERSION}/${PREMAKE5_DOWNLOAD_FILENAME}
PREMAKE5_DOWNLOAD_TMP_PATH="${OPT_DIRNAME}/${PREMAKE5_DOWNLOAD_FILENAME}"
PREMAKE5_INSTALL_DIR="$HOME/.local/share/${PREMAKE5}"

if [ -d "${PREMAKE5_INSTALL_DIR}" ]; then
    read -p "Whether to reinstall? (y/N): " is_reinstall
    if [[ $is_reinstall =~ ^[Yy]$ ]]; then
        echo "Removing the old version..."
        rm -fr "${PREMAKE5_INSTALL_DIR}"
    else
        echo "Reinstallation has been cancelled."
        return 0
    fi
fi

rm -fr "${OPT_DIRNAME}"
mkdir ${OPT_DIRNAME}
pushd ${OPT_DIRNAME}

wget --tries=1 --timeout=5 "${PREMAKE5_DOWNLOAD_URL}"

while true; do
    if [ ! -f "${PREMAKE5_DOWNLOAD_FILENAME}" ]; then
        echo "Download failed!"
        break
    fi

    mkdir -p "${PREMAKE5_INSTALL_DIR}"

    tar -xzvf "${PREMAKE5_DOWNLOAD_FILENAME}"
    cp -fv ${PREMAKE5} "${PREMAKE5_INSTALL_DIR}"

    eval ${SED_PREMAKE5_PREVIEW_CMD}
    eval ${SED_PREMAKE5_DELETE_CMD}
    echo -e "export PATH=\"$PATH:${PREMAKE5_INSTALL_DIR}\"" >> "${SHELLRC_PATH}"
    echo $PATH

    source "${SHELLRC_PATH}"
    echo $PATH

    break
done

popd