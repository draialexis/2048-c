# 2048 in C
2-person university project to code 2048 in C, using SDL
([instructions.pdf](https://github.com/draialexis/2048-c/files/7647069/TP_DM_subj.pdf))
---
* With ***make***
```
make
bin/prog
```
---

* Without ***make***
```
gcc -c -Wall src/main.c -o src/main.o
gcc -c -Wall include/toolbox.c -o include/toolbox.o
gcc -c -Wall include/game.c -o include/game.o
gcc src/main.o include/toolbox.o include/game.o  -o bin/prog
bin/prog
```

