CC=gcc
CFLAGS=-Wall $(shell sdl-config --cflags)
LDFLAGS=$(shell sdl-config --libs)

EXEC=sokoban
SRC=sokoban.c
OBJ=$(SRC:.c=.o)

all: $(EXEC)

sokoban: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean

clean:
	rm -rf $(EXEC) $(OBJ)

