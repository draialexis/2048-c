# 2048 in C
2-person university project to code 2048 in C, using SDL
([instructions.pdf](https://github.com/draialexis/2048-c/files/7647069/TP_DM_subj.pdf))
---
* Linux with ***make***
```
make
bin/prog
```
---

* Linux without ***make***
```
gcc -c -Wall `sdl-config --cflags` src/main.c -o src/main.o
gcc src/main.o `sdl-config --libs` -o bin/prog

```
---

* Windows (very well might not work, can't figure it out ^^')
```
gcc src/main.c -o bin/prog -I include -L lib -lSDLmain -lSDL
bin/prog
```
