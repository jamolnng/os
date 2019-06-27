# export PREFIX="$HOME/opt/cross"
# export TARGET=i686-elf
# export PATH="$PREFIX/bin:$PATH"
# 
# rm -rf build
# mkdir build
# nasm -f elf32 src/boot/boot.asm -o build/boot.o
# $TARGET-g++ -D__is_libk -Isrc/libc/include -Isrc/kernel/include src/kernel/arch/i386/tty.c src/libc/stdio/printf.c src/libc/stdio/putchar.c src/libc/stdio/puts.c src/libc/stdlib/itoa.c src/libc/string/strcmp.c src/libc/string/strlen.c src/libc/string/strrev.c src/kernel/kernel/kernel.cpp build/boot.o -o build/kernel.bin -nostdlib -ffreestanding -std=c++11 -mno-red-zone -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -T src/kernel/arch/i386/linker.ld
cd ./build
make
