# Compiler and flags
CC = gcc
CFLAGS = -Wall -O2 -std=c99
LDFLAGS = -lm  # Link math library

# Directories
SRC_DIR = src
BUILD_DIR = build
RESULTS_DIR = results


# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Target executable
TARGET = $(BUILD_DIR)/vmpi_simulation

# Build rules
all: $(TARGET) ensure_results_dir

$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

ensure_results_dir:
	@mkdir -p $(RESULTS_DIR)

clean:
	rm -rf $(BUILD_DIR) $(RESULTS_DIR)

.PHONY: all clean
