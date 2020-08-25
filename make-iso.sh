#!/bin/sh

make

if [ -d isodir/ ]; then
		rm -rf isodir/
fi

mkdir -p isodir/boot/grub

cat << EOF > isodir/boot/grub/grub.cfg
menuentry "Navy" {
	multiboot2 /boot/navy.bin
}
EOF

cp kernel.bin isodir/boot/navy.bin
grub-mkrescue -o navy.iso isodir
rm -rf isodir
