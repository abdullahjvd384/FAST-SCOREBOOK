# FAST-SCOREBOOK Makefile
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Iinclude

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
BIN_DIR = bin

# Target executable
TARGET = $(BIN_DIR)/fast-scorebook

# Source files
SRCS = $(SRC_DIR)/main.cpp

# Object files
OBJS = $(BUILD_DIR)/main.o

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)
	@echo "Build successful! Executable: $(TARGET)"

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo "Cleaned build artifacts"

# Run the program
run: all
	./$(TARGET)

# Rebuild everything
rebuild: clean all

# Help
help:
	@echo "FAST-SCOREBOOK Build System"
	@echo "============================"
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make all      - Build the project"
	@echo "  make run      - Build and run the program"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make rebuild  - Clean and rebuild"
	@echo "  make help     - Show this help message"

.PHONY: all directories clean run rebuild help
