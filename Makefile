CC      = gcc
CFLAGS  = -Wall -Wextra -std=c11 -pedantic
LDFLAGS = -lm
TARGET  = graphics_editor
SRCS    = main.c canvas.c draw.c objects.c menu.c utils.c
OBJS    = $(SRCS:.c=.o)

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c graphics.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: all
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)