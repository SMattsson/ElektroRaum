#!/bin/bash
wget -nc -O tools/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2?revision=375265d4-e9b5-41c8-bf23-56cbe927e156?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,7-2017-q4-major
tar --skip-old-files -xf tools/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 -C tools/
rm tools/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2 -rf