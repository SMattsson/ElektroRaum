# tools
Compiling with C++17 for Teensy doesn't work
with the compiler that (in this written moment) comes with
Teensyduino due to old version.

Newer compiler such as GCC 10 can't compile
due to some hard solved linker script errors.

Linker script at:
submodules/cores/teensy4/imxrt1062_t41

GCC 7.2.1 works for C++17 compilation, 
and setup.sh downloads it and
extracts it into this folder.
