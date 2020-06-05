#!/bin/sh

./build.sh

if [ -d isodir/ ]; then
	rm -rf isodir/
fi

mkdir -p isodir/boot/grub

cat << EOF > isodir/boot/grub/grub.cfg
menuentry "Navy" {
	multiboot /boot/navy.bin
}
EOF

cp navy.bin isodir/boot/
grub-mkrescue -o navy.iso isodir
rm -rf isodir
