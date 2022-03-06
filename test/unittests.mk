export SRC_ROOT = $(shell cd .. && pwd)/src
export TEST_ROOT = $(shell cd .. && pwd)/test

SUB_DIRS := $(shell find ${SRC_ROOT} -type f -path "*/unittest/*.mk" -print)
ALL_OBJS := $(shell find ${BUILD_UNITTEST_DIR} -type f -name "*.o" -print)

export CXX = g++
export UNITTEST_FLAGS := -pthread -lgtest_main -lgtest -lgmock

run: unittest.o
	@${OUT_DIR_UNITTEST}/unittest.o

unittest.o: compileTests
	$(eval ALL_OBJS := $(shell find ${BUILD_UNITTEST_DIR} -type f -name "*.o" -print))
	@echo "[LD UNITTEST]\t$@"
	@$(CXX) -o ${OUT_DIR_UNITTEST}/"$@" $(ALL_OBJS) $(UNITTEST_FLAGS)

compileTests: $(SUB_DIRS)
$(SUB_DIRS):
	@$(MAKE) --no-print-directory -f $@

.PHONY: compile $(SUB_DIRS)
