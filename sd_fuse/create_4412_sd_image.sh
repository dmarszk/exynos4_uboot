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
    echo "usage: ./create_4412_sd_image.sh <output file>"
    exit 0
fi

#<C210 BL1 fusing>
fwbl1_position=1
bl2_position=17
uboot_position=49
tzsw_position=705
env_position=1025

####################################
echo "Exynos4412 BL1 fusing"
dd iflag=dsync oflag=dsync if=/dev/zero of=$1 bs=512 count=32 seek=$env_position
dd iflag=dsync oflag=dsync if=./p4412_s_fwbl1.bin of=$1 seek=$fwbl1_position

####################################
echo "Exynos4412 BL2 fusing"
dd iflag=dsync oflag=dsync if=../bl2.bin of=$1 seek=$bl2_position

####################################
echo "Exynos4412 bootloader fusing"
dd iflag=dsync oflag=dsync if=../u-boot.bin of=$1 seek=$uboot_position

####################################
echo "Exynos4412 tzsw fusing"
dd iflag=dsync oflag=dsync if=./p4412_s_tzsw.bin of=$1 seek=$tzsw_position

####################################
#<Message Display>
echo "U-boot image is fused successfully."
