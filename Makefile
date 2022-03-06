# Build utilizing all threads
export MAKEFLAGS := "-j $(shell nproc)"

# The name of the project (used to name the compiled .hex file)
TARGET = $(notdir $(CURDIR))

# configurable options, overclock@816MHz
TEENSY_DEFINES = -D__IMXRT1062__ \
				 -DUSB_MIDI_SERIAL \
				 -DLAYOUT_US_ENGLISH \
				 -DTEENSYDUINO=154 \
				 -DARDUINO_TEENSY41 \
				 -DARDUINO=10813 \
				 -DF_CPU=816000000L \
				 -D__ARM_ARCH_7EM__
#-U__STRICT_ANSI__ #Needed for Serial.printf to work, but can't compile audio library with this on

# directory to build src files in
BUILD_SRC_DIR = $(abspath $(CURDIR)/build_src)
# directory to build submodule files in
BUILD_SUB_MODULES_DIR = $(abspath $(CURDIR)/build_submodules)
# directory to build src files in
export BUILD_UNITTEST_DIR = $(abspath $(CURDIR)/build_unittest)

# directory to put elf and hex in
OUT_DIR = $(abspath $(CURDIR)/out)
export OUT_DIR_UNITTEST = $(abspath $(CURDIR)/out_unittest)

# path location for Arduino libraries
LIBRARY_PATH = lib

# patch to teensy 4 core files
INCLUDE = -I submodules/cores/teensy4

CPUOPTIONS = -mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb

# CPPFLAGS = compiler options for C and C++
export CPPFLAGS_SRC = -Wall -O3 -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables
CPPFLAGS = ${CPPFLAGS_SRC} $(CPUOPTIONS) -MMD $(TEENSY_DEFINES) -I. ${INCLUDE}

# compiler options for C++ only
CXXFLAGS_COMMON = -std=c++1z -felide-constructors -fpermissive -fno-rtti -fno-threadsafe-statics
export CXXFLAGS_SRC := ${CXXFLAGS_COMMON} -Wconversion -Wextra
CXXFLAGS_SUBMODULES = ${CXXFLAGS_COMMON} -Wno-error=narrowing

# compiler options for C only
CFLAGS =

# linker options
LDFLAGS = -Os -Wl,--gc-sections,--relax $(CPUOPTIONS) -Lsubmodules/CMSIS/CMSIS/Lib/GCC/ -Tsubmodules/cores/teensy4/imxrt1062_t41.ld -lstdc++

# additional libraries to linkLINKERPATH =
LIBS = -lm

# compiler options
LIBS += -larm_cortexM7lfsp_math -lm

# path for the compiler programs
CC = tools/gcc-arm-none-eabi/bin/arm-none-eabi-gcc
CXX = tools/gcc-arm-none-eabi/bin/arm-none-eabi-g++
OBJCOPY = tools/gcc-arm-none-eabi/bin/arm-none-eabi-objcopy
SIZE = tools/gcc-arm-none-eabi/bin/arm-none-eabi-size

# automatically create lists of the sources and objects, except unittests
SRC_FILES:=$(shell find src $(LIBRARY_PATH) -type f -not -path "*/unittest/*")
SRC_C_FILES:=$(filter %.c, $(SRC_FILES))
SRC_CC_FILES:=$(filter %.cc, $(SRC_FILES))
SRC_CCP_FILES:=$(filter %.cpp, $(SRC_FILES))
SRC_S_FILES:=$(filter %.S, $(SRC_FILES))

SUB_MODULE_SRC_FILES:=$(shell find submodules/cores/teensy4 -type f)
SUB_MODULE_SRC_FILES+=$(shell find submodules/SPI submodules/Audio submodules/SD/src submodules/Wire submodules/SerialFlash submodules/MIDI/src -maxdepth 1 -type f)
SUB_MODULE_SRC_FILES+=$(shell find submodules/Audio/utility -maxdepth 1 -type f)
SUB_MODULE_SRC_FILES+=$(shell find submodules/SdFat/src -type f)
SRC_MODULE_C_FILES:=$(filter %.c, $(SUB_MODULE_SRC_FILES))
SRC_MODULE_CC_FILES:=$(filter %.cc, $(SUB_MODULE_SRC_FILES))
SRC_MODULE_CPP_FILES:=$(filter %.cpp, $(SUB_MODULE_SRC_FILES))
SRC_MODULE_CPP_FILES:=$(filter-out submodules/cores/teensy4/main.cpp, $(SRC_MODULE_CPP_FILES))
SRC_MODULE_S_FILES:=$(filter %.S, $(SUB_MODULE_SRC_FILES))

# include all headers, except from folders named unittest
HEADER_FILES_SRC := $(shell find src lib -type d -not -path "*/unittest" -print)
HEADER_FILES_SUBMODULES = submodules/SPI
HEADER_FILES_SUBMODULES += submodules/Audio
HEADER_FILES_SUBMODULES += submodules/Audio/utility
HEADER_FILES_SUBMODULES += submodules/SD/src
HEADER_FILES_SUBMODULES += submodules/SdFat/src
HEADER_FILES_SUBMODULES += submodules/Wire
HEADER_FILES_SUBMODULES += submodules/SerialFlash
HEADER_FILES_SUBMODULES += submodules/MIDI/src
HEADER_FILES_SRC := $(foreach lib, $(HEADER_FILES_SRC), -I$(lib))
HEADER_FILES_SUBMODULES := $(foreach lib, $(HEADER_FILES_SUBMODULES), -I$(lib))

SOURCES := $(SRC_C_FILES:.c=.o) $(SRC_CC_FILES:.cc=.o) $(SRC_CCP_FILES:.cpp=.o) $(SRC_S_FILES:.S=.o)
OBJS := $(foreach src,$(SOURCES), $(BUILD_SRC_DIR)/$(src))

SUB_MODULE_SOURCES := $(SRC_MODULE_C_FILES:.c=.o) $(SRC_MODULE_CC_FILES:.cc=.o) $(SRC_MODULE_CPP_FILES:.cpp=.o) $(SRC_MODULE_S_FILES:.S=.o)
SUB_MODULE_OBJS := $(foreach src,$(SUB_MODULE_SOURCES), $(BUILD_SUB_MODULES_DIR)/$(src))

ALL_OBJS := ${SUB_MODULE_OBJS}
ALL_OBJS += ${OBJS}

all: hex

hex: $(TARGET).hex

reboot:
	@submodules/teensy_loader_cli/teensy_loader_cli --mcu=TEENSY41 -s -v -b

upload: $(TARGET).hex
	@submodules/teensy_loader_cli/teensy_loader_cli --mcu=TEENSY41 -s -w -v /${OUT_DIR}/"$(basename $<)".hex

unittests:
	@cd test && ${MAKE} --no-print-directory -f unittests.mk

$(BUILD_SRC_DIR)/%.o: %.S
	@echo "[S]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SRC) $(HEADER_FILES_SRC) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SRC_DIR)/%.o: %.c
	@echo "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(HEADER_FILES_SRC) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SRC_DIR)/%.o: %.cc
	@echo "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SRC) $(HEADER_FILES_SRC) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SRC_DIR)/%.o: %.cpp
	@echo "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SRC) $(HEADER_FILES_SRC) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SUB_MODULES_DIR)/%.o: %.S
	@echo "[S]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SUBMODULES) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SUB_MODULES_DIR)/%.o: %.c
	@echo "[CC]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CC) $(CPPFLAGS) $(CFLAGS) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SUB_MODULES_DIR)/%.o: %.cc
	@echo "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SUBMODULES) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(BUILD_SUB_MODULES_DIR)/%.o: %.cpp
	@echo "[CXX]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS) $(CXXFLAGS_SUBMODULES) $(HEADER_FILES_SUBMODULES) -o "$@" -c "$<"

$(TARGET).elf: $(ALL_OBJS)
	@echo "[LD]\t$@"
	@$(CXX) $(LDFLAGS) $(LIBS) -o ${OUT_DIR}/"$@" $(ALL_OBJS)

%.hex: %.elf
	@echo "[HEX]\t$@"
	@$(OBJCOPY) -O ihex -R .eeprom ${OUT_DIR}/"$<" ${OUT_DIR}/"$@"
	@cd submodules/teensy_loader_cli && $(MAKE) --no-print-directory
	@cd submodules/teensy_size && $(MAKE) --no-print-directory
	@submodules/teensy_size/teensy_size /${OUT_DIR}/"$(basename $<)".elf
	@echo ""

-include $(OBJS:.o=.d)
-include $(SUB_MODULE_OBJS:.o=.d)

clean:
	@echo Deleting compiled files from src, lib
	@find ${OUT_DIR}   -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +
	@find ${BUILD_SRC_DIR} -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +

cleanAll:
	@echo Deleting compiled files from src, lib, submodules and unittest
	@find ${OUT_DIR}   -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +
	@find ${BUILD_SRC_DIR} -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +
	@find ${BUILD_SUB_MODULES_DIR} -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +
	@find ${BUILD_UNITTEST_DIR} -mindepth 1 -maxdepth 1 ! -name ".*" ! -name "README.md" -exec rm -r -- {} +
