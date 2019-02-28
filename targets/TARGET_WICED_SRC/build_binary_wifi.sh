#!/bin/sh

compiler=$1
TARGETS=$2

echo "compiler = $compiler"

# Temporary change, use IAR-linux instead of IAR
test [$compiler = "IAR-linux"] && compiler=IAR

export compiler

if [ "$compiler" = "IAR" ]; then
    iccarm --version
fi

set -ex

TOOLCHAIN=$compiler
mbed toolchain $TOOLCHAIN

#
# Generate libraries from object files
#
for target in $TARGETS;do
    TARGET_OBJECTS=$(find ./BUILD/$target/$TOOLCHAIN/mbed-os/targets/TARGET_WICED_SRC/ -name \*.o)

    md5sum $TARGET_OBJECTS

    # Generate target specific library
    mkdir -p mbed-os/targets/TARGET_WICED/TOOLCHAIN_$TOOLCHAIN/TARGET_$target
    if [ "$TOOLCHAIN" = ARM ]; then
        LIB="mbed-os/targets/TARGET_WICED/TOOLCHAIN_$TOOLCHAIN/TARGET_$target/libwiced_drivers.ar"
        armar -rsc $LIB $TARGET_OBJECTS
    elif [ "$TOOLCHAIN" = GCC_ARM ]; then
        LIB="mbed-os/targets/TARGET_WICED/TOOLCHAIN_$TOOLCHAIN/TARGET_$target/libwiced_drivers.a"
        arm-none-eabi-ar -rsc $LIB $TARGET_OBJECTS
    elif [ "$TOOLCHAIN" = IAR ]; then
        LIB="mbed-os/targets/TARGET_WICED/TOOLCHAIN_$TOOLCHAIN/TARGET_$target/libwiced_drivers.a"
        iarchive $TARGET_OBJECTS --create -o $LIB
    fi
done
