# ===== Project =====
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
CXXFLAGS := -Wall -Wextra -std=c++17 -I$(INC_DIR) -MMD -MP
CFLAGS   := -Wall -Wextra -I$(INC_DIR) -MMD -MP

LDFLAGS :=

# ===== Build mode =====
MODE ?= debug

DEBUG_FLAGS := -g
RELEASE_FLAGS := -O2

ifeq ($(MODE),debug)
	CXXFLAGS += $(DEBUG_FLAGS)
	CFLAGS   += $(DEBUG_FLAGS)
else
	CXXFLAGS += $(RELEASE_FLAGS)
	CFLAGS   += $(RELEASE_FLAGS)
endif

# ===== Sources =====
CPP_SRCS := $(wildcard $(SRC_DIR)/*.cpp)
C_SRCS   := $(wildcard $(SRC_DIR)/*.c)

CPP_OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(CPP_SRCS))
C_OBJS   := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(C_SRCS))

OBJS := $(CPP_OBJS) $(C_OBJS)

DEPS := $(OBJS:.o=.d)

# ===== Default target =====
all: $(BIN_DIR)/$(TARGET)

# ===== Link =====
$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# ===== Compile C++ =====
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ===== Compile C =====
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# ===== Create dirs if missing =====
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# ===== Utility targets =====
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

rebuild: clean all

run: all
	./$(BIN_DIR)/$(TARGET)

debug:
	$(MAKE) MODE=debug

release:
	$(MAKE) MODE=release

# ===== Include header deps =====
-include $(DEPS)

.PHONY: all clean rebuild run debug release
