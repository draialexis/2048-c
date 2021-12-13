# 2048 in C
2-person university project to code 2048 in C, using SDL
([instructions.pdf](https://github.com/draialexis/2048-c/files/7647069/TP_DM_subj.pdf))

## Compiling and executing
### Graphical version (main) with SDL
You will need to use Linux, and install SDL 1.2 on you system first, as well as the TTF library.
#### Linux with ***make***
```
make
bin/prog
```
#### Linux without ***make***
```
gcc -c -Wall `sdl-config --cflags` src/main.c -o src/main.o
gcc -c -Wall `sdl-config --cflags` src/toolbox.c -o src/toolbox.o
gcc -c -Wall `sdl-config --cflags` src/game.c -o src/game.o
gcc src/main.o include/toolbox.o include/game.o `sdl-config --libs` -lSDL_ttf  -o bin/prog
bin/prog
```
### Console version
Can be compiled on any OS, as long as you have a C compiler (examples below use GCC)
#### With ***make***
```
make console
bin/console
```
#### Without ***make***
```
gcc -c -Wall console/src_b/main_b.c -o console/src_b/main_b.o
gcc -c -Wall console/src_b/toolbox_b.c -o console/src_b/toolbox_b.o
gcc -c -Wall console/src_b/game_b.c -o console/src_b/game_b.o
gcc console/src_b/main_b.o console/src_b/toolbox_b.o console/src_b/game_b.o -o bin/console
bin/console
```
