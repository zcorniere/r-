FROM fedora:32 as builder
MAINTAINER julien.philippon@epitech.eu

RUN dnf -y install cmake \
    pip \
    gcc-c++ \
    libtool \
    automake \
    libglvnd-devel \
    libfontenc-devel \
    libXaw-devel \
    libXcomposite-devel \
    libXcursor-devel \
    libXdmcp-devel \
    libXft-devel \
    libXtst-devel \
    libXinerama-devel \
    xorg-x11-xkb-utils-devel \
    libXrandr-devel \
    libXres-devel \
    libXScrnSaver-devel \
    libXvMC-devel \
    xorg-x11-xtrans-devel \
    xcb-util-wm-devel \
    xcb-util-image-devel \
    xcb-util-keysyms-devel \
    xcb-util-renderutil-devel \
    libXdamage-devel \
    libXxf86vm-devel \
    libXv-devel \
    xkeyboard-config-devel \
    libudev-devel

RUN pip install conan
RUN conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
RUN conan remote add epitech https://api.bintray.com/conan/epitech/public-conan

WORKDIR /rtype/build
COPY conanfile.txt ..
RUN conan install .. --build=missing

COPY . /rtype
RUN cmake ..
RUN make r-type_server

FROM fedora:32 as runner

COPY --from=builder /rtype/build/bin/r-type_server /r-type_server
COPY --from=builder /rtype/server/assets /draft/assets

EXPOSE 25555

CMD /r-type_server
