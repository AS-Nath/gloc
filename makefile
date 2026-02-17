# ===== Project name =====
TARGET := gloc

# ===== Directories =====
SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
BIN_DIR := bin

# ===== Compilers =====
CXX := g++
CC  := gcc

# ===== Flags =====
CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INC_DIR)
CFLAGS   := -Wall -Wextra -I$(INC_DIR)

# Debug vs Release
DEBUG_FLAGS := -g
RELEASE_FLAGS := -O2

# Default build mode
MODE ?= debug

ifeq ($(MODE),debug)
	CXXFLAGS += $(DEBUG_FLAGS)
	CFLAGS   += $(DEBUG_FLAGS)
else
	CXXFLAGS += $(RELEASE_FLAGS)
	CFLAGS   += $(RELEASE_FLAGS)
endif

# ===== Source files =====
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   := $(wildcard $(SRC_DIR)/*.c)

CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
C_OBJS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

OBJS := $(CPP_OBJS) $(C_OBJS)

# ===== Targets =====
all: $(BIN_DIR)/$(TARGET)

# Link step
$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $@

# Compile C++ files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create directories if missing
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Rebuild
rebuild: clean all

# Debug build explicitly
debug:
	$(MAKE) MODE=debug

# Release build explicitly
release:
	$(MAKE) MODE=release

.PHONY: all clean rebuild debug release
