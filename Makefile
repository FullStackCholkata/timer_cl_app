CC = gcc
CFLAGS = -Wall -Wextra -I./include
SRCS = src/timer.c src/main.c
OBJS = $(SRCS:.c=.o)
TARGET = timer

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -f src/*.o
	rm -f *.o

.PHONY: all clean