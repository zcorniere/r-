#!/usr/bin/env bash

set -e

builddir=appimage_build
linuxdeploy="linuxdeploy-x86_64.AppImage"
url="https://github.com/linuxdeploy/linuxdeploy/releases/download/continuous/$linuxdeploy"

mkdir -p $builddir
cd $builddir

if [ ! -x $linuxdeploy ]; then
    wget "$url"
    chmod u+x $linuxdeploy
fi

conan install ../.. --build=missing
cmake ../.. -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Release
make install DESTDIR=AppDir -j
$linuxdeploy --appdir AppDir -i ../rtype.png -d ../r-type_client.desktop --output appimage
