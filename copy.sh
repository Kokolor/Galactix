#!/bin/bash

gcc -Llinux/lib/x86_64-linux-gnu/ -Isource/framebuffer/ -o a.out source/init.c -lfb

ldd a.out

mkdir -p initramfs/{dev,lib64,/lib/x86_64-linux-gnu}
cd source/framebuffer/
./build.sh
cd ../../
cp source/framebuffer/libfb.so linux/lib/x86_64-linux-gnu/
gcc -Llinux/lib/x86_64-linux-gnu/ -Isource/framebuffer/ -o linux/bin/graphics source/apps/graphics.c -lfb
cp -r linux/* initramfs/
cp a.out initramfs/init

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
   linux /boot/bzImage ro
   initrd /boot/initramfs.img
}' > cdrom/boot/grub/grub.cfg

grub-mkrescue -o galactix.iso cdrom/
qemu-system-x86_64 -cdrom galactix.iso -m 4096M -enable-kvm -vga virtio

rm initramfs.img
rm -rf initramfs
rm a.out
rm -r cdrom/
rm galactix.iso
