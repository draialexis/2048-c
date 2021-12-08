CC=gcc
CFLAGS=-c -Wall `sdl-config --cflags`
LDFLAGS=`sdl-config --libs` -l SDL_ttf -lSDL_image
SOURCES=src/main.c include/toolbox.c include/game.c
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