# Makefile for the Chess Game (All files in a single directory)

# Compiler
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

# Source Files
SRC_FILES := $(wildcard *.cpp)

# Object Files
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# Executable Name
TARGET = chess

# Default Target
all: $(TARGET)

# Build the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJ_FILES)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

# Phony targets
.PHONY: all clean
