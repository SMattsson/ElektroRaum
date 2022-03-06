HEADERS = \
	-I${SRC_ROOT}/utils/audioUtils/inc

SOURCE_FILES = \
	${SRC_ROOT}/utils/audioUtils/src/audioUtils.cc \
	${SRC_ROOT}/utils/audioUtils/unittest/audioUtilsTest.cc


SOURCES := $(SOURCE_FILES:.cc=.o)
OBJS := ${subst $(SRC_ROOT),$(BUILD_UNITTEST_DIR),$(SOURCES)}

audioUtilsTest: $(OBJS)

$(BUILD_UNITTEST_DIR)/%.o: $(SRC_ROOT)/%.cc
	@echo "[CXX UNITTEST]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS_SRC) $(CXXFLAGS_SRC) ${UNITTEST_FLAGS} $(HEADERS) -o "$@" -c "$<"
