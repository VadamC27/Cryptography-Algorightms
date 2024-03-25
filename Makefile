# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall

# Source files
SOURCES = main.cpp pseudorandom-sequences-bbs/bbs.cpp pseudorandom-sequences-bbs/bbs_tests.cpp cryptography_utils.cpp rsa-alghorithm/rsa.cpp

# Object files directory
OBJ_DIR = obj

# Object files
OBJECTS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

# Output directory
OUTPUT_DIR = bin

# Output executable
EXECUTABLE = $(OUTPUT_DIR)/program.exe

# Build rule
all: $(EXECUTABLE)

# Rule to link object files into the executable
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Rule to compile source files into object files
$(OBJ_DIR)/%.o: %.cpp#@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# PHONY targets (targets that are not actual files)
.PHONY: all
