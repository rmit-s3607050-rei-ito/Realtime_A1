# Compiler
CC = g++

# Compiler flags
FLAGS = -lSDL2 -lGL -lGLU -lglut

# Executable result
TARGET = grid-fw

all: $(TARGET)

# Command to run when make called
$(TARGET): $(TARGET).c
		$(CC) -o $(TARGET) $(TARGET).c $(FLAGS)

clean:
		$(RM) $(TARGET)
