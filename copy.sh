gcc -static -o init source/init.c
mkdir -p initramfs/
cp -r linux/* initramfs/
cp init initramfs/init
cd initramfs
find . -print0 | cpio --null -ov --format=newc | gzip -9 > ../initramfs.img
cd ..
qemu-system-x86_64 -kernel linux/boot/bzImage -initrd initramfs.img
rm initramfs.img
rm -rf initramfs
rm init