# 2048 in C
2-person university project to code 2048 in C, using SDL
([instructions.pdf](https://github.com/draialexis/2048-c/files/7647069/TP_DM_subj.pdf))

## Compiling and executing
You will need to install SDL 1.2 on you system first.
### Linux with ***make***
```
make
bin/prog
```
### Linux without ***make***
```
gcc -c -Wall `sdl-config --cflags` src/main.c -o src/main.o
gcc -c -Wall `sdl-config --cflags` include/toolbox.c -o include/toolbox.o
gcc -c -Wall `sdl-config --cflags` include/game.c -o include/game.o
gcc src/main.o include/toolbox.o include/game.o `sdl-config --libs` -lSDL_ttf  -o bin/prog
bin/prog
```
