#!/bin/bash

host=$1

mkdir -p build-newlib
mkdir -p build-newlib/toolchain
mkdir -p build-newlib/release


exit_and_clean() {
#    rm -rf build-newlib
    exit $1
}


pushd build-newlib/toolchain
    wget https://github.com/kwrx/aplus-toolchain/releases/latest/download/$host-aplus-toolchain-nocxx.tar.xz || exit_and_clean 1
    tar -xJf $host-aplus-toolchain-nocxx.tar.xz || exit_and_clean 1
popd

pushd build-newlib

    export PATH="$PATH:$(pwd)/toolchain/bin"


    ../configure --target=$host-aplus --prefix=                          || exit_and_clean 1

    # Build
    make -j2 CFLAGS_FOR_TARGET="-w -g -O2" CFLAGS_FOR_BUILD=" -w -g -O2" || exit_and_clean 1
    make -j2 DESTDIR="$(pwd)/toolchain" install                          || exit_and_clean 1

    # Test
    echo "int main() {return 0;}" | $host-aplus-gcc -x c -               || exit_and_clean 1

    # Release
    make -j2 DESTDIR="$(pwd)/release" install                            || exit_and_clean 1
    
popd



pushd build-newlib/release
    tar -cJf $host-aplus-newlib.tar.xz *    || exit_and_clean 1
    mv $host-aplus-newlib.tar.xz ../..      || exit_and_clean 1
popd


exit_and_clean 0
