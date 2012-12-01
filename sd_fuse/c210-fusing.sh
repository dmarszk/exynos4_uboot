#
# Copyright (C) 2010 Samsung Electronics Co., Ltd.
#              http://www.samsung.com/
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
####################################
if [ -z $1 ]
then
    echo "usage: ./sd_fusing.sh <SD Reader's device file>"
    exit 0
fi

#<C210 BL1 fusing>
bl1_position=1
uboot_position=33
env_position=1057
echo "C210 BL1 fusing"

sudo dd iflag=dsync oflag=dsync if=/dev/zero of=$1 bs=512 count=32 seek=$env_position

./c210-mkbl1 ../u-boot.bin SD-bl1-16k.bin 16384
sudo dd iflag=dsync oflag=dsync if=SD-bl1-16k.bin of=$1 seek=$bl1_position
rm -f SD-bl1-16k.bin

####################################
#<C210 u-boot fusing>
echo "C210 u-boot fusing"
sudo dd iflag=dsync oflag=dsync if=../u-boot.bin of=$1 seek=$uboot_position

####################################
#<Message Display>
echo "U-boot image is fused successfully."
echo "Eject SD card and insert it again."
