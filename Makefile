CC               = gcc
SRC_EXT          = .c
HEAD_EXT         = .h
WARN_FLAGS       = --std=c11 -pedantic -W -Wall
OPTIMIZE_FLAGS   = -O2 -march=native
DEBUG_FLAGS      = -g
PROFILE_FLAGS    = -pg

SOURCE_DIR  = src
HEADER_DIR  = include
DEBUG_DIR   = debug
EXECUTABLE  = program

SOURCES = $(shell find $(SOURCE_DIR) -name '*$(SRC_EXT)')
HEADERS = $(shell find $(HEADER_DIR) -name '*$(HEAD_EXT)')

DEBUG_OBJECTS   = $(patsubst $(SOURCE_DIR)/%$(SRC_EXT), $(DEBUG_DIR)/%.o, $(SOURCES))

debug: debug_dir $(DEBUG_DIR)/$(EXECUTABLE)

memcheck: debug
	valgrind --tool=memcheck --leak-check=yes ./$(DEBUG_DIR)/$(EXECUTABLE)

docs: $(HEADERS)
	doxygen Doxyfile

clean:
	rm -rf $(BUILD_DIR) $(DEBUG_DIR) $(PROFILE_DIR) vgcore* *.out

debug_dir:
	@mkdir -p $(DEBUG_DIR)

$(DEBUG_DIR)/$(EXECUTABLE): $(DEBUG_OBJECTS)
	$(CC) $^ $(ADDITIONAL_FLAGS) -o $@

$(DEBUG_OBJECTS): $(DEBUG_DIR)/%.o : $(SOURCE_DIR)/%$(SRC_EXT)
	@mkdir -p $(dir $@)
	$(CC) -c $(WARN_FLAGS) $(DEBUG_FLAGS) -I$(HEADER_DIR) $< -o $@
