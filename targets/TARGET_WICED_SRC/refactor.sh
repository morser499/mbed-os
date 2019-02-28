#!/bin/bash

#set -ex

# helper from http://wiki.bash-hackers.org/syntax/quoting
# escapestr_sed()
# read a stream from stdin and escape characters in text that could be interpreted as
# special characters by sed
escape_sed() {
 echo $1 | sed \
  -e 's/\//\\\//g' \
  -e 's/\&/\\\&/g'
}

mv WICED/platforms/WISE_1530A1/ WICED/platforms/TARGET_MTB_ADV_WISE_1530
mv WICED/WICED/WWD/internal/chips/43362/ WICED/WICED/WWD/internal/chips/TARGET_MTB_MXCHIP_EMW3166
mv WICED/WICED/WWD/internal/chips/4343x/ WICED/WICED/WWD/internal/chips/TARGET_MTB_ADV_WISE_1530
mv WICED/resources/firmware/4343W/ WICED/resources/firmware/TARGET_MTB_ADV_WISE_1530
mv WICED/resources/firmware/43362/ WICED/resources/firmware/TARGET_MTB_MXCHIP_EMW3166
mv WICED/libraries/drivers/bluetooth/firmware/43438A1/37_4MHz/bt_firmware_controller.c WICED/resources/firmware/TARGET_MTB_ADV_WISE_1530
mv WICED/WICED/WWD/internal/wwd_clm.c WICED/WICED/WWD/internal/chips/TARGET_MTB_ADV_WISE_1530/


#
# Step 1: Remove ignored and unused files
#
echo "Remove ignored and unused files"
dos2unix .mbedignore
cat .mbedignore | xargs rm -rf

# Step 3: Rename include only C files to .inc
# Easier to do before renaming
echo "Rename include only C files to .inc"
for file in $(grep -R '#include .*\.c' WICED -l); do
    cfile=$(find WICED -name $(sed -n '/#include/s/ *#include "\(.*\)\.c"/\1.c/p' $file))
    sed -i '/#include/s/\(.*\)\.c"/\1.inc"/' $file
    mv $cfile $(echo $cfile | sed 's/\.c/\.inc/')
done

#
# Step 2.0: Rename all .c files by adding 'w_' prefix
#
c_files=()
echo "Renaming all C files..."
#for file in WICED/WICED/internal/dct.c ./WICED/WICED/WWD/internal/wwd_thread.c WICED/WICED/WWD/internal/wwd_sdpcm.c WICED/WICED/platform/MCU/STM32F4xx/WWD/wwd_SDIO.c; do
for file in $(find WICED -iname \*.c); do
    # Skip files with wiced_ or wwd_ prefix
    if echo $file | grep "/wiced_" >/dev/null || echo $file | grep "/wwd_" >/dev/null; then
        new=$file
    else
        d=$(dirname $file)
        f=$(basename $file)
        new=$d/w_$f
        mv $file $new
    fi
    c_files=(${c_files[@]} $new)
done

#
# Step 2: Rename all .h files
# skip files with wiced_ or wwd_ prefix
#
echo "Renaming all H files..."
headers=($(find WICED -iname \*.h |grep -v "/wiced_" |grep -v "/wwd_"))
#headers=(WICED/include/wiced_defaults.h WICED/WICED/platform/include/platform_dct.h WICED/WICED/platform/MCU/STM32F4xx/peripherals/libraries/inc/stm32f4xx_crc.h WICED/libraries/utilities/crc/crc.h WICED/WICED/platform/MCU/STM32F4xx/peripherals/libraries/stm32f4xx_conf.h)
renamed_headers=()
rm -f /tmp/refactor.sed
for file in ${headers[@]}; do
    d=$(dirname $file)
    f=$(basename $file)
    new=$d/w_$f
    mv $file $new
    echo "s/#include [<\"]\(.*\/\)\?$f[>\"]/#include \"\1w_$f\"/" >> /tmp/refactor.sed
    renamed_headers=(${renamed_headers[@]} $new)
done

# Add extra includes to refactor
echo "s/#include [<\"]\(.*\/\)\?rtos.h[>\"]/#include \"\1w_rtos.h\"/" >> /tmp/refactor.sed
echo "s/#include [<\"]\(.*\/\)\?resources.h[>\"]/#include \"\1w_resources.h\"/" >> /tmp/refactor.sed
echo "/platform_cache.h/d" >> /tmp/refactor.sed # Not neede file

#
# Step 2: refactor .c&.h files to include new name
#
echo "Fix include paths"
for file in ${c_files[@]} $(find WICED -iname \*.h);do
    sed -i -f /tmp/refactor.sed $file
done
#rm /tmp/refactor.sed
