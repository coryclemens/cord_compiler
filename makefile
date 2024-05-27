# MAKEFILE - CLEMCO 02/03/2023
#-----------------------------
# COMPILER / C++ VERSIONS
CXX := gcc
CPP_VER := -std=c++11

# PATHS
SRC_DIR := ./src
OBJ_DIR := ./obj
BIN_DIR := ./bin
EXE := $(BIN_DIR)/cord

# SRC/OBJ FILE EXPANSIONS - COLLECT ALL FILES
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

#FLAGS
LDFLAGS :=
CFLAGS := -g -Wall -Werror -Wextra
CXXFLAGS := -MMD
DEBUG := -DNDEBUG_BULD

.PHONY: all clean debug


# RELEASE BUILD: make / make all
all: $(EXE)

$(EXE): $(OBJ_FILES) | $(BIN_DIR)
	@$(CXX) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CXX) $(DEBUG) $(CXXFLAGS) $(CFLAGS) -c -o $@ $<


# DEBUG BUILD: make debug
debug: DEBUG = -DDEBUG_BUILD

debug: all
	$(info WARNING: Debug Build)


# CREATE DIRS IF THEY DONT EXIST
$(BIN_DIR) $(OBJ_DIR):
	@mkdir -p $@
	$(info CREATING $@)


# CLEANER: make clean
clean:
	@$(RM) -rf ./obj ./bin
	$(info CLEANING ./obj ./bin)


-include $(OBJ_FILES:.o=.d)