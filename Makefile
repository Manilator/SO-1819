CC               = gcc
SRC_EXT          = .c
HEAD_EXT         = .h
WARN_FLAGS       = --std=c11 -pedantic -W -Wall
OPTIMIZE_FLAGS   = -O2 -march=native
DEBUG_FLAGS      = -g
PROFILE_FLAGS    = -pg

SOURCE_DIR  = src
MA_DIR		= ma
SV_DIR		= sv
CV_DIR		= cv
AG_DIR		= ag
HEADER_DIR  = include
DEBUG_DIR   = debug
EXECUTABLE_MA  = program_ma
EXECUTABLE_SV  = program_sv
EXECUTABLE_CV  = program_cv
EXECUTABLE_AG  = program_ag

SOURCES = $(shell find $(SOURCE_DIR) -name '*$(SRC_EXT)')
HEADERS = $(shell find $(HEADER_DIR) -name '*$(HEAD_EXT)')

DEBUG_OBJECTS   = $(patsubst $(SOURCE_DIR)/%$(SRC_EXT), $(DEBUG_DIR)/%.o, $(SOURCES))

all: ma sv cv

ma:
	$(CC) -o $(SOURCE_DIR)/$(EXECUTABLE_MA) -g $(WARN_FLAGS) -I$(HEADER_DIR) $(SOURCE_DIR)/$(MA_DIR)/*.c $(SOURCE_DIR)/utils.c $(HEADER_DIR)/utils.h $(HEADER_DIR)/ma.h 

sv:
	$(CC) -o $(SOURCE_DIR)/$(EXECUTABLE_SV) -g $(WARN_FLAGS) -I$(HEADER_DIR) $(SOURCE_DIR)/$(SV_DIR)/*.c $(SOURCE_DIR)/utils.c $(HEADER_DIR)/utils.h $(HEADER_DIR)/sv.h $(SOURCE_DIR)/$(MA_DIR)/ma.c $(HEADER_DIR)/ma.h 

cv:
	$(CC) -o $(SOURCE_DIR)/$(EXECUTABLE_CV) -g $(WARN_FLAGS) -I$(HEADER_DIR) $(SOURCE_DIR)/$(CV_DIR)/main.c $(SOURCE_DIR)/utils.c $(HEADER_DIR)/utils.h 

ag:
	$(CC) -o $(SOURCE_DIR)/$(EXECUTABLE_AG) -g $(WARN_FLAGS) -I$(HEADER_DIR) $(SOURCE_DIR)/$(AG_DIR)/*.c $(SOURCE_DIR)/utils.c $(HEADER_DIR)/utils.h $(HEADER_DIR)/ag.h 

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
