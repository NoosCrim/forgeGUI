# Compiler and flags
CXX := g++
CXX_FLAGS_COMMON := -std=c++23 -Wall -Wextra -Iheaders
CXX_FLAGS_DEBUG := -fsanitize-address-use-after-scope -fsanitize=leak,address,undefined,float-divide-by-zero,enum -Og
CXX_FLAGS_RELEASE := -O3
CXX_FLAGS_TEST := 
CXX_FLAGS := CXX_FLAGS_COMMON

AR := ar
ARFLAGS := rcs

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

TEST_SRC_DIR := tests
TEST_OBJ_DIR := tests/obj
TEST_BIN_DIR := tests/bin

# Library output
LIB_NAME = myGUI
LIB := lib$(LIB_NAME).a

# Source and object files
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))

# Test sources, object files, and executables
TEST_SRC := $(wildcard $(TEST_SRC_DIR)/test*.cpp)
TEST_OBJ := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_OBJ_DIR)/%.o,$(TEST_SRC))
TEST_BIN := $(patsubst $(TEST_SRC_DIR)/%.cpp,$(TEST_BIN_DIR)/%,$(TEST_SRC))

# Dependencies
DEP := $(OBJ:.o=.d) $(TEST_OBJ:.o=.d)

UNAME := $(shell uname)

# Default OpenGL library (override with make OPENGL_LIB=xxx)
ifeq ($(UNAME), Darwin)
    OPENGL_LIB ?= -framework OpenGL
else ifeq ($(OS), Windows_NT)
    OPENGL_LIB ?= -lopengl32
else
    OPENGL_LIB ?= -lGL
endif

TEST_OPENGL_LOADER_LIB := -lGLEW
TEST_OPENGL_CONTEXT_LIB := -lglfw

TEST_LIBS := $(OPENGL_LIB) $(TEST_OPENGL_CONTEXT_LIB) $(TEST_OPENGL_LOADER_LIB) -L$(BIN_DIR) -l$(LIB_NAME)

all: release

# Default target
release: CXX_FLAGS:= $(CXX_FLAGS_COMMON) $(CXX_FLAGS_RELEASE)
release: $(LIB) $(TEST_BIN)

debug: CXX_FLAGS:= $(CXX_FLAGS_COMMON) $(CXX_FLAGS_DEBUG)
debug: $(LIB) $(TEST_BIN)

# Build static library
$(LIB): $(OBJ) $(BIN_DIR)
	$(AR) $(ARFLAGS) $(BIN_DIR)/$@ $(OBJ)

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# Link test executables with the library
$(TEST_BIN_DIR)/%: $(TEST_OBJ_DIR)/%.o $(LIB) | $(TEST_BIN_DIR)
	$(CXX) $(CXX_FLAGS) $(CSS_FLAGS_TEST) $< -o $@ $(TEST_LIBS)

# Compile test object files
$(TEST_OBJ_DIR)/%.o: $(TEST_SRC_DIR)/%.cpp | $(TEST_OBJ_DIR)
	$(CXX) $(CXX_FLAGS) $(CSS_FLAGS_TEST) -c $< -o $@

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

$(TEST_OBJ_DIR):
	mkdir -p $@

$(TEST_BIN_DIR):
	mkdir -p $@

# Clean build files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_BIN_DIR) $(TEST_OBJ_DIR)

# Include dependencies
-include $(DEP)

.PHONY: all release debug clean