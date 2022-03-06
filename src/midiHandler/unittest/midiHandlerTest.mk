NAME = midiHandler.cc
TEST_NAME = midiHandler

HEADERS = \
	-I${SRC_ROOT}/midiHandler/inc \
	-I${SRC_ROOT}/soundEngine/if \
	-I${TEST_ROOT}/mocks/submodules \
	-I${TEST_ROOT}/mocks/soundEngine

SOURCE_FILES = \
	${SRC_ROOT}/midiHandler/src/midiHandler.cc \
	${SRC_ROOT}/midiHandler/unittest/midiHandlerTest.cc


SOURCES := $(SOURCE_FILES:.cc=.o)
OBJS := ${subst $(SRC_ROOT),$(BUILD_UNITTEST_DIR),$(SOURCES)}

midiHandlerTest: $(OBJS)

$(BUILD_UNITTEST_DIR)/%.o: $(SRC_ROOT)/%.cc
	@echo "[CXX UNITTEST]\t$<"
	@mkdir -p "$(dir $@)"
	@$(CXX) $(CPPFLAGS_SRC) $(CXXFLAGS_SRC) ${UNITTEST_FLAGS} $(HEADERS) -o "$@" -c "$<"