fastboot flash fwbl1 ./p4412_s_fwbl1.bin
fastboot flash bl2 ../bl2.bin
fastboot flash bootloader ../u-boot.bin
fastboot flash tzsw ./p4412_s_tzsw.bin