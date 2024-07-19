# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -std=c++11

# SDL2 and SDL2_ttf paths (adjust these if your SDL installation is in a different location)
SDL2_CFLAGS = $(shell sdl2-config --cflags)
SDL2_LIBS = $(shell sdl2-config --libs) -lSDL2_ttf

# Include directories
INCLUDES = -Iinclude

# Source and object files
SRC_DIR = src
OBJ_DIR = obj
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Output executable
TARGET = ExpenseTracker

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJ_FILES)
	$(CXX) $(CXXFLAGS) $(OBJ_FILES) -o $@ $(SDL2_LIBS)

# Compiling
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SDL2_CFLAGS) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET)

