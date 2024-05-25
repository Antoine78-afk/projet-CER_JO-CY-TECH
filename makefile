# Makefile to compile the project

# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Executable name
TARGET = main

# Source files
SRCS = performance.c athlete.c file_utils.c main.c  stats.c

# Object files
OBJS = $(SRCS:.c=.o)

# Default rule to build the executable
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

# Rebuild the project
rebuild: clean all
