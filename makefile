CC=gcc
CFLAGS=-c -Wall `sdl-config --cflags`
CFLAGS_BIS=-c -Wall
LDFLAGS=`sdl-config --libs` -lSDL_ttf
SOURCES=src/main.c src/toolbox.c src/game.c
SOURCES_BIS=console/src_b/main_b.c console/src_b/toolbox_b.c console/src_b/game_b.c
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_BIS=$(SOURCES_BIS:.c=.o)
EXECUTABLE=bin/prog
EXECUTABLE_BIS=bin/console
.PHONY: clean
all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@

console: $(SOURCES_BIS) $(EXECUTABLE_BIS)

$(EXECUTABLE_BIS): $(OBJECTS_BIS)
	$(CC) $(OBJECTS_BIS) -o $@

clean:
	rm -f $(OBJECTS) $(OBJECTS_BIS) $(EXECUTABLE) $(EXECUTABLE_BIS)