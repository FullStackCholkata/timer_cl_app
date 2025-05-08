# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -I./include

# Source files
SRCS = src/timer.c src/main.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = timer.exe

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compile source files to object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	if exist $(TARGET) del $(TARGET)
	if exist *.o del *.o

.PHONY: all clean