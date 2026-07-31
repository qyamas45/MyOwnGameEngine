# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -g -Wextra -std=c++11

# Linker flags for OpenGL and GLUT
LDFLAGS = -Llibs -lopengl32 -lglfw3dll

INCLUDES = -Iinclude -Iinclude/core -Iinclude/game -Iinclude/collider

# Target executable
TARGET = program

# Source files (objects/*.cpp are #included by main.cpp, not compiled separately)
SRCS = src/main.cpp glad.c src/application.cpp src/obj/ball.cpp  src/collider.cpp src/collisionDetection.cpp

# Object files
OBJS = src/main.o glad.o src/application.o src/obj/ball.o src/collider.o src/collisionDetection.o
# Default target
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Rule to compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Rule to compile glad.c (needs -Iinclude for glad/glad.h)
glad.o: glad.c
	$(CC) $(INCLUDES) -c $< -o $@

%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
	
# Clean up build files
clean:
ifeq ($(OS), Windows_NT)
	del /f /q $(subst /,\,$(OBJS)) $(TARGET).exe 2>NUL || true
else
	rm -f $(OBJS) $(TARGET)
endif
.PHONY: all clean