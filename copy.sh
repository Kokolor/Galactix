#!/bin/bash

gcc -static -o init source/init.c source/shell/shell.c source/framebuffer/framebuffer.c
gcc -static -o ls source/commands/ls.c
cd source/applications/
bash build.sh
cd ../../
mv ls linux/bin/

mkdir -p initramfs/dev
cp -r linux/* initramfs/
cp init initramfs/init

sudo mknod -m 600 initramfs/dev/console c 5 1
sudo mknod -m 666 initramfs/dev/null c 1 3
sudo mknod initramfs/dev/fb0 c 29 0

cd initramfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.img
cd ..

mkdir -p cdrom/boot/grub

cp linux/boot/bzImage cdrom/boot/
cp initramfs.img cdrom/boot/

echo 'set timeout=30
set default=0

menuentry "Galactix" {
   linux /boot/bzImage ro quiet
   initrd /boot/initramfs.img
}' > cdrom/boot/grub/grub.cfg

grub-mkrescue -o galactix.iso cdrom/
qemu-system-x86_64 -cdrom galactix.iso -m 4096M -enable-kvm -vga virtio

rm initramfs.img
rm -rf initramfs
rm init
rm -r cdrom/
rm galactix.iso
