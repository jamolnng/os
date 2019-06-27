@echo off
call ./scripts/build.bat
qemu-system-x86_64 -cdrom build/os.iso
