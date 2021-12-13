CC=gcc
CFLAGS=-c -Wall `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -lSDL_ttf
SOURCES=src/main.c src/toolbox.c src/game.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=bin/prog
.PHONY: clean
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)