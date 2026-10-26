Command to run virtual machine (Raspberry Pi 3b)

sudo qemu-system-aarch64 \
-M raspi3b \
-cpu cortex-a53 \
-m 1G \
-kernel kernel8.img \
-dtb bcm2710-rpi-3-b.dtb \
-serial stdio \
-display gtk \
-drive file=~/Projects/'Raspberry Pi Projects'/raw_sdcard.img,if=sd,format=raw \
-full-screen