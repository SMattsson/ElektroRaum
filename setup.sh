#!/bin/bash

echo " ______ _      _    _             _____                       "
echo "|  ____| |    | |  | |           |  __ \                      "
echo "| |__  | | ___| | _| |_ _ __ ___ | |__) |__ _ _   _ _ __ ___  "
echo "|  __| | |/ _ \ |/ / __|  __/ _ \|  _  // _  | | | |  _  _  \ "
echo "| |____| |  __/   <| |_| | | (_) | | \ \ (_| | |_| | | | | | |"
echo "|______|_|\___|_|\__\__|_|  \___/|_|  \_\__ _|\__ _|_| |_| |_|"
echo ""
                                                               
while true; do
    read -p "Do you wish to install dependencies for this project (y/n)? " yn
    case $yn in
        [Yy] ) echo  "Installing dependencies for project...."; break;;
        [Nn] ) echo  "Installation canceled"; exit;;
        * ) echo  "Please answer y or n.";;
    esac
done

#To be able to use the teensy_loader_cli for uploading firmware
#https://libusb.info/
sudo apt -qq install libusb-dev -y

#Google test
sudo apt -qq install libgtest-dev -y

#Google mock
sudo apt -ww install libgmock-dev -y

#Python 3 for GUI
sudo apt install python3 python3-tk
sudo apt install python3-pip
sudo pip install pyserial

#Udev rule for teensy
#https://wiki.debian.org/udev
rm /etc/udev/rules.d/00-teensy.rules -rf
sudo wget -nc -q -O /etc/udev/rules.d/00-teensy.rules https://www.pjrc.com/teensy/00-teensy.rules

echo ""

#--------------------------------------------------
#Install the ARM X86 crosscompiler into the project.
#https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads
#The newest compiler supported is 2017-q4-major due to unresolved linker errors with newer one.
#----------------------------------------------------------------------------------------------

COMPILER_LINK=https://developer.arm.com/-/media/Files/downloads/gnu-rm/7-2017q4/gcc-arm-none-eabi-7-2017-q4-major-linux.tar.bz2?revision=375265d4-e9b5-41c8-bf23-56cbe927e156?product=GNU%20Arm%20Embedded%20Toolchain,64-bit,,Linux,7-2017-q4-major

#Clear tools folder
find tools/ -mindepth 1 -not -iname ".gitignore" -not -iname "README.md" -execdir rm -r {} \; > /dev/null 2>&1
#Download gcc-arm-none-eabi
echo "Downloading gcc-arm-none-eabi ........\r"
wget -nc -O tools/gcc-arm-none-eabi.tar.bz2 $COMPILER_LINK
#Extract
echo "Extracing gcc-arm-none-eabi ........"
tar -xf tools/gcc-arm-none-eabi.tar.bz2 -C tools/
#Rename gcc folder to generic name (excluding version)
find tools -maxdepth 1 -mindepth 1 -type d -name 'gcc-arm-none-eabi*' -execdir mv {} gcc-arm-none-eabi \;
#Remove archive
rm tools/gcc-arm-none-eabi.tar.bz2

echo ""
echo "------------------------------------------------------------------"
echo "--------IMPORTANT! Do not remove if a modem is installed!---------"
echo "------------------------------------------------------------------"
echo "ModemManager tends to interfere with USB Serial devices like Teensy."
echo "Problems manifest as the Arduino Serial Monitor missing some incoming"
echo "data, and 'Unable to open /dev/ttyACM0 for reboot request' when uploading."
echo "More details at https://www.pjrc.com/teensy/00-teensy.rules"
echo ""

while true; do
    read -p "Do you want to remove ModemManager (y/n)? " yn
    case $yn in
        [Yy] ) sudo apt remove modemmanager -y ; break;;
        [Nn] ) echo  "Skipping removal of modemmanager"; break;;
        * ) echo  "Please answer y or n.";;
    esac
done

echo ""
echo "git submodule init ........"
git submodule init
echo "git submodule update ........"
git submodule update
echo "Complete!"
