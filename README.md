# 2048 in C
2-person university project to code 2048 in C, using SDL
([instructions.pdf](https://github.com/draialexis/2048-c/files/7647069/TP_DM_subj.pdf))

## Compiling and executing
### Graphical version (main) with SDL
You will need to use **Linux**.

You will need to install SDL 1.2 on your system as well as the TTF library, as needed:

```
sudo apt-get install libsdl1.2debian
sudo apt-get install libsdl-ttf2.0-0
```

That should be enough for you to run the executable (`cd` to the `2048-c` folder, then run `bin/prog`)

To compile the program yourself, you'll need to install ***gcc*** and ***make*** as needed, and the *dev* versions of the appropriate SDL libraries:
```
sudo apt install gcc
sudo apt install make
sudo apt-get install libsdl1.2-dev
sudo apt-get install libsdl-ttf2.0-dev
```

#### With ***make***
```
make
bin/prog
```
#### Without ***make***
```
gcc -c -Wall `sdl-config --cflags` src/main.c -o src/main.o
gcc -c -Wall `sdl-config --cflags` src/toolbox.c -o src/toolbox.o
gcc -c -Wall `sdl-config --cflags` src/game.c -o src/game.o
gcc src/main.o src/toolbox.o src/game.o `sdl-config --libs` -lSDL_ttf  -o bin/prog
bin/prog
```
---
### Console version
Windows or Linux is fine.
#### With ***make***
```
make console
bin/console
```
Can be compiled on any OS, as long as you have a C compiler (example below uses GCC)
#### Without ***make***
```
gcc -c -Wall console/src_b/main_b.c -o console/src_b/main_b.o
gcc -c -Wall console/src_b/toolbox_b.c -o console/src_b/toolbox_b.o
gcc -c -Wall console/src_b/game_b.c -o console/src_b/game_b.o
gcc console/src_b/main_b.o console/src_b/toolbox_b.o console/src_b/game_b.o -o bin/prog
bin/prog
```
